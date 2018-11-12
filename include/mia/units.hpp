#ifndef MIA_UNITS_HPP
#define MIA_UNITS_HPP

#include <functional>
#include <ostream>
#include <ratio>
#include <type_traits>
#include <utility>
#include <gsl/gsl_util>
#include <gsl/string_span>
#include <range/v3/utility/common_type.hpp>
#include <range/v3/utility/concepts.hpp>
#include <units/core.h>
#include <jegp/utility.hpp>
#include <mia/concepts.hpp>

namespace mia {

namespace dimension {

    struct Display_length_tag {
        static constexpr gsl::czstring<> name{"display length"};
        static constexpr gsl::czstring<> abbreviation{"px"};
    };

    using Display_length = units::make_dimension<Display_length_tag>;

} // namespace dimension

inline namespace display_length { //

    template <class Arithmetic>
    using Pixels = units::unit<
        units::conversion_factor<std::ratio<1>, dimension::Display_length>,
        Arithmetic>;

} // namespace display_length

inline namespace literals {
    inline namespace pixels_literals { //

        constexpr Pixels<int> operator""_px(unsigned long long px) noexcept
        {
            return Pixels<int>{gsl::narrow_cast<int>(px)};
        }

        constexpr Pixels<double> operator""_px(long double px) noexcept
        {
            return Pixels<double>{gsl::narrow_cast<double>(px)};
        }

    } // namespace pixels_literals
} // namespace literals

template <template <class> class Alias, class Aliased>
class Unit_alias {
public:
    static_assert(Quantity<Aliased>());

    using aliased = Aliased;
    using derived = Alias<aliased>;

    Unit_alias()                  = default;
    ~Unit_alias()                 = default;
    Unit_alias(const Unit_alias&) = default;
    Unit_alias& operator=(const Unit_alias&) = default;

    template <
        class Aliased2,
        CONCEPT_REQUIRES_(ranges::Constructible<aliased, const Aliased2&>())>
    explicit constexpr Unit_alias(const Aliased2& a) noexcept(
        std::is_nothrow_constructible_v<aliased, const Aliased2&>)
      : unaliased_(a)
    {
    }

    template <
        class Aliased2, CONCEPT_REQUIRES_(
                            ranges::Constructible<aliased, Aliased2>() &&
                            !std::is_convertible_v<Aliased2, aliased>)>
    explicit constexpr Unit_alias(const Unit_alias<Alias, Aliased2>& a) noexcept(
        noexcept(a.unaliased()) &&
        std::is_nothrow_constructible_v<aliased, Aliased2>)
      : unaliased_(a.unaliased())
    {
    }

    template <
        class Aliased2, CONCEPT_REQUIRES_(
                            ranges::Constructible<aliased, Aliased2>() &&
                            std::is_convertible_v<Aliased2, aliased>)>
    constexpr Unit_alias(const Unit_alias<Alias, Aliased2>& a) noexcept(
        noexcept(a.unaliased()) &&
        std::is_nothrow_constructible_v<aliased, Aliased2>)
      : unaliased_(a.unaliased())
    {
    }

    constexpr aliased unaliased() const
        noexcept(std::is_nothrow_copy_constructible_v<aliased>)
    {
        return unaliased_;
    }

    constexpr derived& operator++() noexcept(
        noexcept(++std::declval<aliased&>()))
    {
        ++unaliased_;
        return derived_();
    }

    constexpr derived& operator--() noexcept(
        noexcept(--std::declval<aliased&>()))
    {
        --unaliased_;
        return derived_();
    }

    constexpr derived operator++(int) noexcept(
        noexcept(derived(std::declval<aliased&>()++)))
    {
        return derived(unaliased_++);
    }

    constexpr derived operator--(int) noexcept(
        noexcept(derived(std::declval<aliased&>()--)))
    {
        return derived(unaliased_--);
    }

    template <
        class Aliased2, CONCEPT_REQUIRES_(QuantityWith<aliased, Aliased2>())>
    constexpr derived& operator+=(
        const Unit_alias<Alias, Aliased2>&
            r) noexcept(noexcept(std::declval<aliased&>() += r.unaliased()))
    {
        unaliased_ += r.unaliased();
        return derived_();
    }

    template <
        class Aliased2, CONCEPT_REQUIRES_(QuantityWith<aliased, Aliased2>())>
    constexpr derived& operator-=(
        const Unit_alias<Alias, Aliased2>&
            r) noexcept(noexcept(std::declval<aliased&>() -= r.unaliased()))
    {
        unaliased_ -= r.unaliased();
        return derived_();
    }

    template <class One, CONCEPT_REQUIRES_(QuantityOneWith<One, aliased>())>
    constexpr derived& operator*=(const One& r) noexcept(
        noexcept(std::declval<aliased&>() *= r))
    {
        unaliased_ *= r;
        return derived_();
    }

    template <class One, CONCEPT_REQUIRES_(QuantityOneWith<One, aliased>())>
    constexpr derived& operator/=(const One& r) noexcept(
        noexcept(std::declval<aliased&>() /= r))
    {
        unaliased_ /= r;
        return derived_();
    }

    template <class One, CONCEPT_REQUIRES_(QuantityOneWith<One, aliased>())>
    constexpr derived& operator%=(const One& r) noexcept(
        noexcept(std::declval<aliased&>() %= r))
    {
        unaliased_ %= r;
        return derived_();
    }

    template <
        class Aliased2, CONCEPT_REQUIRES_(QuantityWith<aliased, Aliased2>())>
    constexpr derived& operator%=(
        const Unit_alias<Alias, Aliased2>&
            r) noexcept(noexcept(std::declval<aliased&>() %= r.unaliased()))
    {
        unaliased_ %= r.unaliased();
        return derived_();
    }

private:
    constexpr derived& derived_() noexcept
    {
        return jegp::static_downcast<derived&>(*this);
    }

    aliased unaliased_;
};

template <template <class> class Alias, class Aliased>
constexpr auto operator+(const Unit_alias<Alias, Aliased>& a) noexcept(
    noexcept(Alias<decltype(+a.unaliased())>(+a.unaliased())))
{
    return Alias<decltype(+a.unaliased())>(+a.unaliased());
}

template <template <class> class Alias, class Aliased>
constexpr auto operator-(const Unit_alias<Alias, Aliased>& a) noexcept(
    noexcept(Alias<decltype(-a.unaliased())>(-a.unaliased())))
{
    return Alias<decltype(-a.unaliased())>(-a.unaliased());
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(QuantityWith<Aliased1, Aliased2>())>
constexpr auto
operator+(const Unit_alias<Alias, Aliased1>& l, const Unit_alias<Alias, Aliased2>& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() + r.unaliased())>(
        l.unaliased() + r.unaliased())))
{
    return Alias<decltype(l.unaliased() + r.unaliased())>(
        l.unaliased() + r.unaliased());
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(QuantityWith<Aliased1, Aliased2>())>
constexpr auto
operator-(const Unit_alias<Alias, Aliased1>& l, const Unit_alias<Alias, Aliased2>& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() - r.unaliased())>(
        l.unaliased() - r.unaliased())))
{
    return Alias<decltype(l.unaliased() - r.unaliased())>(
        l.unaliased() - r.unaliased());
}

template <
    template <class> class Alias, class Aliased, class One,
    CONCEPT_REQUIRES_(QuantityOneWith<One, Aliased>())>
constexpr auto
operator*(const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() * r)>(l.unaliased() * r)))
{
    return Alias<decltype(l.unaliased() * r)>(l.unaliased() * r);
}

template <
    template <class> class Alias, class Aliased, class One,
    CONCEPT_REQUIRES_(QuantityOneWith<One, Aliased>())>
constexpr auto
operator*(const One& l, const Unit_alias<Alias, Aliased>& r) noexcept(
    noexcept(Alias<decltype(l * r.unaliased())>(l* r.unaliased())))
{
    return Alias<decltype(l * r.unaliased())>(l * r.unaliased());
}

template <
    template <class> class Alias, class Aliased, class One,
    CONCEPT_REQUIRES_(QuantityOneWith<One, Aliased>())>
constexpr auto
operator/(const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() / r)>(l.unaliased() / r)))
{
    return Alias<decltype(l.unaliased() / r)>(l.unaliased() / r);
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(QuantityWith<Aliased1, Aliased2>())>
constexpr auto operator/(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>&
        r) noexcept(noexcept(l.unaliased() / r.unaliased()))
{
    return l.unaliased() / r.unaliased();
}

template <
    template <class> class Alias, class Aliased, class One,
    CONCEPT_REQUIRES_(QuantityOneWith<One, Aliased>())>
constexpr auto
operator%(const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() % r)>(l.unaliased() % r)))
{
    return Alias<decltype(l.unaliased() % r)>(l.unaliased() % r);
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(QuantityWith<Aliased1, Aliased2>())>
constexpr auto
operator%(const Unit_alias<Alias, Aliased1>& l, const Unit_alias<Alias, Aliased2>& r) noexcept(
    noexcept(Alias<decltype(l.unaliased() % r.unaliased())>(
        l.unaliased() % r.unaliased())))
{
    return Alias<decltype(l.unaliased() % r.unaliased())>(
        l.unaliased() % r.unaliased());
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Aliased1, Aliased2>())>
constexpr auto operator==(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>&
        r) noexcept(noexcept(l.unaliased() == r.unaliased()))
{
    return l.unaliased() == r.unaliased();
}

template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator!=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(noexcept(!(l == r)))
    -> decltype(!(l == r))
{
    return !(l == r);
}

template <
    template <class> class Alias, class Aliased1, class Aliased2,
    CONCEPT_REQUIRES_(ranges::TotallyOrdered<Aliased1, Aliased2>())>
constexpr auto operator<(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>&
        r) noexcept(noexcept(l.unaliased() < r.unaliased()))
{
    return l.unaliased() < r.unaliased();
}

template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(noexcept(r < l))
    -> decltype(r < l)
{
    return r < l;
}

template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator<=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(noexcept(!(r < l)))
    -> decltype(!(r < l))
{
    return !(r < l);
}

template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(noexcept(!(l < r)))
    -> decltype(!(l < r))
{
    return !(l < r);
}

template <class... T, template <class> class Alias, class Aliased>
std::basic_ostream<T...>& operator<<(
    std::basic_ostream<T...>& os, const Unit_alias<Alias, Aliased>& a)
{
    return os << a.unaliased();
}

} // namespace mia

namespace ranges {

template <template <class> class Alias, class Aliased1, class Aliased2>
struct common_type<
    mia::Unit_alias<Alias, Aliased1>, mia::Unit_alias<Alias, Aliased2>> {
    using type = mia::Unit_alias<Alias, common_type_t<Aliased1, Aliased2>>;
};

} // namespace ranges

namespace std {

template <template <class> class Alias, class Aliased>
struct hash<mia::Unit_alias<Alias, Aliased>> : private hash<Aliased> {
    constexpr auto operator()(
        const mia::Unit_alias<Alias, Aliased>&
            a) noexcept(noexcept(hash<Aliased>{}(a.unaliased())))
        -> decltype(hash<Aliased>{}(a.unaliased()))
    {
        return hash<Aliased>{}(a.unaliased());
    }
};

} // namespace std

namespace mia::detail {

template <template <class> class Alias, class Aliased>
class Unit_alias_hash : std::hash<mia::Unit_alias<Alias, Aliased>> {
    using Base = std::hash<mia::Unit_alias<Alias, Aliased>>;

public:
    constexpr auto operator()(const Alias<Aliased>& a) noexcept(
        noexcept(Base{}(a))) -> decltype(Base{}(a))
    {
        return Base{}(a);
    }
};

} // namespace mia::detail

#endif // MIA_UNITS_HPP
