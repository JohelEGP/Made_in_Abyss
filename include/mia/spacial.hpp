#ifndef MIA_SPACIAL_HPP
#define MIA_SPACIAL_HPP

#include <array>
#include <functional> //
#include <tuple>
#include <type_traits> //
#include <utility>
#include <gsl/gsl_assert>
#include <boost/mp11/algorithm.hpp>
#include <range/v3/utility/common_type.hpp> //
#include <range/v3/utility/concepts.hpp>    //
#include <jegp/utility.hpp>
#include <mia/concepts.hpp>
#include <mia/units.hpp> //

namespace mia {

enum class Dimension { x, y, z };

template <Dimension dim, class Qty>
class Coordinate;

namespace detail {

    template <Dimension dim>
    struct Coordinate {
        template <class Qty>
        using type = mia::Coordinate<dim, Qty>;
    };

} // namespace detail

template <Dimension dim, class Qty>
class Coordinate
  : public Unit_alias<detail::Coordinate<dim>::template type, Qty> {
public:
    using Unit_alias<detail::Coordinate<dim>::template type, Qty>::Unit_alias;
};

template <class Qty>
class Abscissa : public Unit_alias<Abscissa, Qty> {
public:
    using Unit_alias<Abscissa, Qty>::Unit_alias;

    template <
        class Qty2, CONCEPT_REQUIRES_(ranges::Constructible<
                                      Unit_alias<Abscissa, Qty>, Qty2>())>
    constexpr Abscissa(const Coordinate<Dimension::x, Qty2>& x) noexcept(
        std::is_nothrow_constructible_v<
            Unit_alias<Abscissa, Qty>, Qty2>&& noexcept(x.unaliased()))
      : Unit_alias<Abscissa, Qty>{x.unaliased()}
    {
    }

    template <
        class Qty2, CONCEPT_REQUIRES_(ranges::Constructible<
                                      Coordinate<Dimension::x, Qty2>, Qty>())>
    constexpr operator Coordinate<Dimension::x, Qty2>() noexcept(
        std::is_nothrow_constructible_v<
            Coordinate<Dimension::x, Qty2>,
            Qty>&& noexcept(std::declval<Abscissa>().unalised()))
    {
        return Coordinate<Dimension::x, Qty2>{
            Unit_alias<Abscissa, Qty>::unaliased()};
    }
};

template <class Qty>
class Ordinate : public Unit_alias<Ordinate, Qty> {
public:
    using Unit_alias<Abscissa, Qty>::Unit_alias;
};

template <class Qty>
class Applicate : public Unit_alias<Applicate, Qty> {
public:
    using Unit_alias<Applicate, Qty>::Unit_alias;
};

template <class Qty>
explicit Abscissa(const Qty&)->Abscissa<Qty>;

template <class Qty>
explicit Ordinate(const Qty&)->Ordinate<Qty>;

template <class Qty>
explicit Applicate(const Qty&)->Applicate<Qty>;

} // namespace mia

namespace ranges {

template <mia::Dimension dim, class Qty1, class Qty2>
struct common_type<mia::Coordinate<dim, Qty1>, mia::Coordinate<dim, Qty2>> {
    using type = mia::Coordinate<dim, common_type_t<Qty1, Qty2>>;
};

template <class Qty1, class Qty2>
struct common_type<mia::Abscissa<Qty1>, mia::Abscissa<Qty2>> {
    using type = mia::Abscissa<common_type_t<Qty1, Qty2>>;
};

template <class Qty1, class Qty2>
struct common_type<mia::Ordinate<Qty1>, mia::Ordinate<Qty2>> {
    using type = mia::Ordinate<common_type_t<Qty1, Qty2>>;
};

template <class Qty1, class Qty2>
struct common_type<mia::Applicate<Qty1>, mia::Applicate<Qty2>> {
    using type = mia::Applicate<common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace std {

template <Dimension dim, class Qty>
struct hash<mia::Coordinate<dim, Qty>>
  : mia::detail::Unit_alias_hash<
        mia::detail::Coordinate<dim>::template type, Qty> {
};

template <class Qty>
struct hash<mia::Abscissa<Qty>>
  : mia::detail::Unit_alias_hash<mia::Abscissa, Qty> {
};

template <class Qty>
struct hash<mia::Ordinate<Qty>>
  : mia::detail::Unit_alias_hash<mia::Ordinate, Qty> {
};

template <class Qty>
struct hash<mia::Applicate<Qty>>
  : mia::detail::Unit_alias_hash<mia::Applicate, Qty> {
};

} // namespace std

namespace mia {

// Point class template specializations.

template <int Dims, class Qty>
class Point {
public:
    static_assert(Dims >= 1);
    static_assert(WeakQuantity<Qty>());

    Point()             = default;
    Point(const Point&) = default;
    Point(Point&&)      = default;
    ~Point()            = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    template <
        int... Dim, class... Qty2,
        CONCEPT_REQUIRES_(
            std::is_same_v<
                std::integer_sequence<int, Dim...>,
                std::make_integer_sequence<int, Dims>> &&
            (... && ranges::Constructible<
                        Coordinate<Dim, Qty>, const Coordinate<Dim, Qty2>&>()))>
    explicit constexpr Point(const Coordinate<Dim, Qty2>&... coords) noexcept(
        (... && std::is_nothrow_constructible_v<
                    Coordinate<Dim, Qty>, const Coordinate<Dim, Qty2>&>))
      : coords{coords.unaliased()...}
    {
    }

    template <class Qty2, CONCEPT_REQUIRES_(ranges::Constructible<Qty, Qty2>())>
    constexpr Point(const Point<Dims, Qty2>& pt) noexcept(
        std::is_nothrow_constructible_v<Qty, Qty2>&&
            std::is_nothrow_copy_constructible_v<Qty2>)
      : coords{pt.coords}
    {
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 1)>
    constexpr void x(const Abscissa<Qty>& x) noexcept(
        std::is_nothrow_copy_constructible_v<Abscissa<Qty>>)
    {
        coords[0] = x.unaliased();
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 2)>
    constexpr void y(const Ordinate<Qty>& y) noexcept(
        std::is_nothrow_copy_constructible_v<Ordinate<Qty>>)
    {
        coords[1] = y.unaliased();
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 3)>
    constexpr void z(const Applicate<Qty>& z) noexcept(
        std::is_nothrow_copy_constructible_v<Applicate<Qty>>)
    {
        coords[2] = z.unaliased();
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 1)>
    constexpr Abscissa<Qty> x() const
        noexcept(std::is_nothrow_copy_constructible_v<Abscissa<Qty>>)
    {
        return Abscissa{coords[0]};
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 2)>
    constexpr Ordinate<Qty> y() const
        noexcept(std::is_nothrow_copy_constructible_v<Ordinate<Qty>>)
    {
        return Ordinate{coords[1]};
    }

    template <int Dims_ = Dims, CONCEPT_REQUIRES_(Dims_ >= 3)>
    constexpr Applicate<Qty> z() const
        noexcept(std::is_nothrow_copy_constructible_v<Applicate<Qty>>)
    {
        return Applicate{coords[2]};
    }

private:
    std::array<Qty, Dims> coords;
};

template <int... Dim, class... Qty>
explicit Point(Coordinate<Dim, Qty>...)
    ->Point<sizeof...(Dim), ranges::common_type_t<Qty...>>;

} // namespace mia

namespace std {

template <int Dims, class Qty>
struct tuple_size<mia::Point<Dims, Qty>> : integral_constant<size_t, Dims> {
};

template <size_t I, int Dims, class Qty>
struct tuple_element<I, mia::Point<Dims, Qty>> {
    static_assert(I < Dims);

    using type = boost::mp11::mp_at_c<
        tuple<mia::Abscissa<Qty>, mia::Ordinate<Qty>, mia::Applicate<Qty>>, I>;
};

} // namespace std

namespace mia {

// An (x, y) ordered pair of coordinates representing a point in a plane.
template <class Qty>
struct Point<2, Qty> {
    template <class Qty2, CONCEPT_REQUIRES_(ranges::ConvertibleTo<Qty, Qty2>())>
    constexpr operator Point<2, Qty2>() const
        noexcept(std::is_nothrow_constructible_v<Qty, Qty2>)
    {
        return {x, y};
    }

    Abscissa<Qty> x;
    Ordinate<Qty> y;
};

// An (x, y, z) ordered triplet of coordinates representing a point in a space.
template <class Qty>
struct Point<3, Qty> {
    template <class Qty2, CONCEPT_REQUIRES_(ranges::ConvertibleTo<Qty, Qty2>())>
    constexpr operator Point<3, Qty2>() const
        noexcept(std::is_nothrow_constructible_v<Qty, Qty2>)
    {
        return {x, y, z};
    }

    Abscissa<Qty> x;
    Ordinate<Qty> y;
    Applicate<Qty> z;
};

template <class Qty1, class Qty2>
Point(Abscissa<Qty1>, Ordinate<Qty2>)
    ->Point<2, ranges::common_type_t<Qty1, Qty2>>;

template <class Qty1, class Qty2, class Qty3>
Point(Abscissa<Qty1>, Ordinate<Qty2>, Applicate<Qty3>)
    ->Point<3, ranges::common_type_t<Qty1, Qty2, Qty3>>;

template <
    class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto operator==(
    const Point<2, Qty1>& l,
    const Point<2, Qty2>& r) noexcept(noexcept(l.x == r.x && l.y == r.y))
{
    return l.x == r.x && l.y == r.y;
}

template <
    class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto operator==(
    const Point<3, Qty1>& l,
    const Point<3, Qty2>&
        r) noexcept(noexcept(l.x == r.x && l.y == r.y && l.z == r.z))
{
    return l.x == r.x && l.y == r.y && l.z == r.z;
}

template <
    int Dims, class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto operator!=(
    const Point<Dims, Qty1>& l,
    const Point<Dims, Qty2>& r) noexcept(noexcept(!(l == r)))
{
    return !(l == r);
}

template <int Dims, class Qty>
std::ostream& operator<<(std::ostream& os, const Point<Dims, Qty>& pt)
{
    if constexpr (Dims == 2)
        return os << '{' << pt.x << ", " << pt.y << '}';
    else
        return os << '{' << pt.x << ", " << pt.y << ", " << pt.z << '}';
}

} // namespace mia

namespace std {

template <class Qty>
struct hash<mia::Point<2, Qty>>
  : private hash<mia::Abscissa<Qty>>
  , private hash<mia::Ordinate<Qty>> {
    constexpr auto operator()(const mia::Point<2, Qty>& pt) noexcept(
        noexcept(jegp::hash_combine(pt.x, pt.y)))
        -> decltype(jegp::hash_combine(pt.x, pt.y))
    {
        return jegp::hash_combine(pt.x, pt.y);
    }
};

template <class Qty>
struct hash<mia::Point<3, Qty>>
  : private hash<mia::Abscissa<Qty>>
  , private hash<mia::Ordinate<Qty>>
  , private hash<mia::Applicate<Qty>> {
    constexpr auto operator()(const mia::Point<3, Qty>& pt) noexcept(
        noexcept(jegp::hash_combine(pt.x, pt.y, pt.z)))
        -> decltype(jegp::hash_combine(pt.x, pt.y, pt.z))
    {
        return jegp::hash_combine(pt.x, pt.y, pt.z);
    }
};

} // namespace std

namespace ranges {

template <int Dims, class Qty1, class Qty2>
struct common_type<mia::Point<Dims, Qty1>, mia::Point<Dims, Qty2>> {
    using type = mia::Point<Dims, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace mia {

// Dimension class templates.

// Represents a distance to an x-axis or a yz-plane.
template <class Qty>
class Width : public Unit_alias<Width, Qty> {
public:
    using Unit_alias<Width, Qty>::Unit_alias;
};

// Represents a distance to a y-axis or an xz-plane.
template <class Qty>
class Height : public Unit_alias<Height, Qty> {
public:
    using Unit_alias<Height, Qty>::Unit_alias;
};

// Represents a distance to an xy-plane.
template <class Qty>
class Depth : public Unit_alias<Depth, Qty> {
public:
    using Unit_alias<Depth, Qty>::Unit_alias;
};

template <class Qty>
explicit Width(const Qty&)->Width<Qty>;

template <class Qty>
explicit Height(const Qty&)->Height<Qty>;

template <class Qty>
explicit Depth(const Qty&)->Depth<Qty>;

} // namespace mia

namespace ranges {

template <class Qty1, class Qty2>
struct common_type<mia::Width<Qty1>, mia::Width<Qty2>> {
    using type = mia::Width<common_type_t<Qty1, Qty2>>;
};

template <class Qty1, class Qty2>
struct common_type<mia::Height<Qty1>, mia::Height<Qty2>> {
    using type = mia::Height<common_type_t<Qty1, Qty2>>;
};

template <class Qty1, class Qty2>
struct common_type<mia::Depth<Qty1>, mia::Depth<Qty2>> {
    using type = mia::Depth<common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace std {

template <class Qty>
struct hash<mia::Width<Qty>> : mia::detail::Unit_alias_hash<mia::Width, Qty> {
};

template <class Qty>
struct hash<mia::Height<Qty>> : mia::detail::Unit_alias_hash<mia::Height, Qty> {
};

template <class Qty>
struct hash<mia::Depth<Qty>> : mia::detail::Unit_alias_hash<mia::Depth, Qty> {
};

} // namespace std

namespace mia {

// Size class template specializations.

template <int Dims, class Qty>
class Size;

// A (width, height) ordered pair representing an area.
template <class Qty>
class Size<2, Qty> {
public:
    static_assert(WeakQuantity<Qty>());

    constexpr Size(const Width<Qty>& w, const Height<Qty>& h) : w_{w}, h_{h}
    {
        Expects(w_ > Width<Qty>{0} && h_ > Height<Qty>{0});
    }

    constexpr void w(const Width<Qty>& w)
    {
        Expects(w > Width<Qty>{0});
        w_ = w;
    }

    constexpr void h(const Height<Qty>& h)
    {
        Expects(h > Height<Qty>{0});
        h_ = h;
    }

    constexpr const Width<Qty>& w() const noexcept
    {
        return w_;
    }

    constexpr const Height<Qty>& h() const noexcept
    {
        return h_;
    }

    template <class Qty2, CONCEPT_REQUIRES_(ranges::ConvertibleTo<Qty, Qty2>())>
    constexpr operator Size<2, Qty2>() const
        noexcept(std::is_nothrow_constructible_v<Qty, Qty2>)
    {
        return {w(), h()};
    }

private:
    Width<Qty> w_;
    Height<Qty> h_;
};

// A (width, height, depth) ordered triplet representing a volume.
template <class Qty>
class Size<3, Qty> : Size<2, Qty> {
public:
    static_assert(WeakQuantity<Qty>());

    constexpr Size(
        const Width<Qty>& w, const Height<Qty>& h, const Depth<Qty>& d)
      : Size<2, Qty>{w, h}, d_{d}
    {
        Expects(d_ > Depth<Qty>{0});
    }

    using Size<2, Qty>::w;
    using Size<2, Qty>::h;

    constexpr void d(const Depth<Qty>& d)
    {
        Expects(d > Depth<Qty>{0});
        d_ = d;
    }

    constexpr const Depth<Qty>& d() const noexcept
    {
        return d_;
    }

    template <class Qty2, CONCEPT_REQUIRES_(ranges::ConvertibleTo<Qty, Qty2>())>
    constexpr operator Size<3, Qty2>() const
        noexcept(std::is_nothrow_constructible_v<Qty, Qty2>)
    {
        return {w(), h(), d()};
    }

private:
    Depth<Qty> d_;
};

template <class Qty1, class Qty2>
Size(Width<Qty1>, Height<Qty2>)->Size<2, ranges::common_type_t<Qty1, Qty2>>;

template <class Qty1, class Qty2, class Qty3>
Size(Width<Qty1>, Height<Qty2>, Depth<Qty3>)
    ->Size<3, ranges::common_type_t<Qty1, Qty2, Qty3>>;

} // namespace mia

namespace std {

template <int Dims, class Qty>
struct tuple_size<mia::Size<Dims, Qty>> : integral_constant<size_t, Dims> {
};

template <size_t I, int Dims, class Qty>
struct tuple_element<I, mia::Size<Dims, Qty>> {
    static_assert(I < Dims);

    using type = boost::mp11::mp_at_c<
        tuple<mia::Width<Qty>, mia::Height<Qty>, mia::Depth<Qty>>, I>;
};

} // namespace std

namespace mia {

template <std::size_t I, int Dims, class Qty>
constexpr const std::tuple_element_t<I, Size<Dims, Qty>>& get(
    const Size<Dims, Qty>& sz) noexcept
{
    if constexpr (I == 0)
        return sz.w();
    if constexpr (I == 1)
        return sz.h();
    if constexpr (I == 2)
        return sz.d();
}

template <
    class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto operator==(
    const Size<2, Qty1>& l,
    const Size<2, Qty2>& r) noexcept(noexcept(l.w() == r.w() && l.h() == r.h()))
{
    return l.w() == r.w() && l.h() == r.h();
}

template <
    class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto
operator==(const Size<3, Qty1>& l, const Size<3, Qty2>& r) noexcept(
    noexcept(l.w() == r.w() && l.h() == r.h() && l.d() == r.d()))
{
    return l.w() == r.w() && l.h() == r.h() && l.d() == r.d();
}

template <
    int Dims, class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>())>
constexpr auto operator!=(
    const Size<Dims, Qty1>& l,
    const Size<Dims, Qty2>& r) noexcept(noexcept(!(l == r)))
{
    return !(l == r);
}

template <int Dims, class Qty>
std::ostream& operator<<(std::ostream& os, const Size<Dims, Qty>& sz)
{
    if constexpr (Dims == 2)
        return os << '{' << sz.w() << ", " << sz.h() << '}';
    else
        return os << '{' << sz.w() << ", " << sz.h() << ", " << sz.d() << '}';
}

} // namespace mia

namespace std {

template <class Qty>
struct hash<mia::Size<2, Qty>>
  : private hash<mia::Width<Qty>>
  , private hash<mia::Height<Qty>> {
    constexpr auto operator()(const mia::Size<2, Qty>& sz) noexcept(
        noexcept(jegp::hash_combine(sz.w(), sz.h())))
        -> decltype(jegp::hash_combine(sz.w(), sz.h()))
    {
        return jegp::hash_combine(sz.w(), sz.h());
    }
};

template <class Qty>
struct hash<mia::Size<3, Qty>>
  : private hash<mia::Width<Qty>>
  , private hash<mia::Height<Qty>>
  , private hash<mia::Depth<Qty>> {
    constexpr auto operator()(const mia::Size<3, Qty>& sz) noexcept(
        noexcept(jegp::hash_combine(sz.w(), sz.h(), sz.d())))
        -> decltype(jegp::hash_combine(sz.w(), sz.h(), sz.d()))
    {
        return jegp::hash_combine(sz.w(), sz.h(), sz.d());
    }
};

} // namespace std

namespace ranges {

template <int Dims, class Qty1, class Qty2>
struct common_type<mia::Size<Dims, Qty1>, mia::Size<Dims, Qty2>> {
    using type = mia::Size<Dims, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

#endif // MIA_SPACIAL_HPP
