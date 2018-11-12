#ifndef MIA_SPACIAL_HPP
#define MIA_SPACIAL_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <gsl/gsl_assert>
#include <gsl/gsl_util>
#include <boost/hana/equal.hpp>
#include <boost/hana/ext/std/array.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/unpack.hpp>
#include <range/v3/utility/common_type.hpp>
#include <range/v3/utility/concepts.hpp>
#include <jegp/utility.hpp>
#include <mia/concepts.hpp>
#include <mia/units.hpp>

namespace mia {

enum class Axis { x, y, z };

template <Axis A, class Qty>
class Coordinate;

namespace detail {

    template <Axis A>
    struct Mp_coordinate {
        template <class Qty>
        using fn = Coordinate<A, Qty>;
    };

} // namespace detail

template <Axis A, class Qty>
class Coordinate
  : public Unit_alias<detail::Mp_coordinate<A>::template fn, Qty> {
public:
    static_assert(A >= Axis::x);

    static constexpr Axis axis{A};

    using Unit_alias<detail::Mp_coordinate<A>::template fn, Qty>::Unit_alias;
};

template <class Qty>
using Abscissa = Coordinate<Axis::x, Qty>;
template <class Qty>
using Ordinate = Coordinate<Axis::y, Qty>;
template <class Qty>
using Applicate = Coordinate<Axis::z, Qty>;

} // namespace mia

namespace ranges {

template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Coordinate<A, Qty1>, mia::Coordinate<A, Qty2>> {
    using type = mia::Coordinate<A, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Coordinate<A, Qty>>
  : mia::detail::Unit_alias_hash<
        mia::detail::Mp_coordinate<A>::template fn, Qty> {
};

} // namespace std

namespace mia {

enum class Coordinates;

template <Coordinates C, class Qty>
class Point {
public:
    static_assert(C >= Coordinates{1});
    static_assert(Quantity<Qty>{});

    static constexpr Coordinates coordinates{C};
    using quantity = Qty;

private:
    static constexpr boost::hana::range<int, 0, jegp::underlying(coordinates)>
        ints{};

    static constexpr std::array axes{boost::hana::unpack(
        ints, [](auto... int_c) { return std::array{Axis{int_c()}...}; })};

public:
    Point()             = default;
    Point(const Point&) = default;
    Point(Point&&)      = default;
    ~Point()            = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    template <
        Axis... A, class... Qty2,
        CONCEPT_REQUIRES_(
            std::conjunction_v<
                std::bool_constant<boost::hana::equal(axes, std::array{A...})>,
                ranges::Constructible<
                    Coordinate<A, quantity>, const Coordinate<A, Qty2>&>...>)>
    explicit constexpr Point(const Coordinate<A, Qty2>&... coord) noexcept(
        std::conjunction_v<std::is_nothrow_constructible<
            Coordinate<A, quantity>, const Coordinate<A, Qty2>&>...>)
      : coords{coord...}
    {
    }

    template <
        class Qty2, CONCEPT_REQUIRES_(ranges::Constructible<quantity, Qty2>{})>
    constexpr Point(const Point<coordinates, Qty2>& pt) noexcept(
        std::is_nothrow_copy_constructible_v<Qty2>&&
            std::is_nothrow_constructible_v<quantity, Qty2>)
      : coords{boost::hana::unpack(ints, [&](auto... int_c) {
            return Coords{pt.template get<int_c>()...};
        })}
    {
    }

    constexpr Abscissa<quantity>& x() noexcept
    {
        return std::get<jegp::underlying(Axis::x)>(coords);
    }
    constexpr const Abscissa<quantity>& x() const noexcept
    {
        return std::get<jegp::underlying(Axis::x)>(coords);
    }

    template <Axis A = Axis::y, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr Ordinate<quantity>& y() noexcept
    {
        return std::get<jegp::underlying(A)>(coords);
    }
    template <Axis A = Axis::y, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr const Ordinate<quantity>& y() const noexcept
    {
        return std::get<jegp::underlying(A)>(coords);
    }

    template <Axis A = Axis::z, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr Applicate<quantity>& z() noexcept
    {
        return std::get<jegp::underlying(A)>(coords);
    }
    template <Axis A = Axis::z, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr const Applicate<quantity>& z() const noexcept
    {
        return std::get<jegp::underlying(A)>(coords);
    }

    template <std::size_t I>
    constexpr Coordinate<Axis{I}, quantity>& get() noexcept
    {
        return std::get<I>(coords);
    }
    template <std::size_t I>
    constexpr const Coordinate<Axis{I}, quantity>& get() const noexcept
    {
        return std::get<I>(coords);
    }

private:
    static constexpr auto coords_tuple = [](auto... int_c) {
        return std::tuple<Coordinate<axes[int_c], quantity>...>{};
    };

    using Coords = decltype(boost::hana::unpack(ints, coords_tuple));

    Coords coords;
};

template <Axis... A, class Qty>
explicit Point(Coordinate<A, Qty>...)->Point<Coordinates{sizeof...(A)}, Qty>;

template <class Qty>
using Point2d = Point<Coordinates{2}, Qty>;
template <class Qty>
using Point3d = Point<Coordinates{3}, Qty>;

template <
    std::size_t I, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(I < jegp::underlying(C))>
constexpr Coordinate<Axis{I}, Qty>& get(Point<C, Qty>& pt) noexcept
{
    return pt.template get<I>();
}
template <
    std::size_t I, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(I < jegp::underlying(C))>
constexpr const Coordinate<Axis{I}, Qty>& get(const Point<C, Qty>& pt) noexcept
{
    return pt.template get<I>();
}

template <
    Axis A, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(Axis::x <= A && A < static_cast<Axis>(C))>
constexpr Coordinate<A, Qty>& get(Point<C, Qty>& pt) noexcept
{
    return pt.template get<jegp::underlying(A)>();
}
template <
    Axis A, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(Axis::x <= A && A < static_cast<Axis>(C))>
constexpr const Coordinate<A, Qty>& get(const Point<C, Qty>& pt) noexcept
{
    return pt.template get<jegp::underlying(A)>();
}

template <
    class Coord, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(
        std::is_same_v<Coord, Coordinate<Coord::axis, Qty>> &&
        (Axis::x <= Coord::axis && Coord::axis < static_cast<Axis>(C)))>
constexpr Coord& get(Point<C, Qty>& pt) noexcept
{
    return pt.template get<jegp::underlying(Coord::axis)>();
}
template <
    class Coord, Coordinates C, class Qty,
    CONCEPT_REQUIRES_(
        std::is_same_v<Coord, Coordinate<Coord::axis, Qty>> &&
        (Axis::x <= Coord::axis && Coord::axis < static_cast<Axis>(C)))>
constexpr const Coord& get(const Point<C, Qty>& pt) noexcept
{
    return pt.template get<jegp::underlying(Coord::axis)>();
}

template <
    Coordinates C, class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>{})>
constexpr auto operator==(
    const Point<C, Qty1>& l,
    const Point<C, Qty2>&
        r) noexcept(noexcept(std::declval<Qty1>() == std::declval<Qty2>()))
{
    return boost::hana::unpack(
        boost::hana::range_c<int, 0, jegp::underlying(C)>, [&](auto... int_c) {
            return (... && (get<int_c>(l) == get<int_c>(r)));
        });
}
template <Coordinates C, class Qty1, class Qty2>
constexpr auto operator!=(
    const Point<C, Qty1>& l,
    const Point<C, Qty2>& r) noexcept(noexcept(!(l == r)))
    -> decltype(!(l == r))
{
    return !(l == r);
}

} // namespace mia

namespace std {

template <mia::Coordinates C, class Qty>
struct tuple_size<mia::Point<C, Qty>>
  : integral_constant<size_t, jegp::underlying(C)> {
};

template <size_t I, mia::Coordinates C, class Qty>
struct tuple_element<I, mia::Point<C, Qty>> {
    static_assert(I < jegp::underlying(C));

    using type = mia::Coordinate<mia::Axis{I}, Qty>;
};

} // namespace std

namespace ranges {

template <mia::Coordinates C, class Qty1, class Qty2>
struct common_type<mia::Point<C, Qty1>, mia::Point<C, Qty2>> {
    using type = mia::Point<C, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace mia::detail {

template <class Tuple, class = void>
struct Tuple_hash
  : Tuple_hash<Tuple, std::make_index_sequence<std::tuple_size_v<Tuple>>> {
};

template <class Tuple, std::size_t... I>
struct Tuple_hash<Tuple, std::index_sequence<I...>>
  : private std::hash<std::tuple_element_t<I, Tuple>>... {
    constexpr auto operator()(const Tuple& t) const
        noexcept(noexcept(jegp::hash_combine(get<I>(t)...)))
            -> decltype(jegp::hash_combine(get<I>(t)...))
    {
        return jegp::hash_combine(get<I>(t)...);
    }
};

} // namespace mia::detail

namespace std {

template <mia::Coordinates C, class Qty>
struct hash<mia::Point<C, Qty>> : mia::detail::Tuple_hash<mia::Point<C, Qty>> {
};

} // namespace std

namespace mia {

template <Axis A, class Qty>
class Dimension;

namespace detail {

    template <Axis A>
    struct Mp_dimension {
        template <class Qty>
        using fn = Dimension<A, Qty>;
    };

} // namespace detail

template <Axis A, class Qty>
class Dimension : public Unit_alias<detail::Mp_dimension<A>::template fn, Qty> {
public:
    static_assert(A >= Axis::x);

    static constexpr Axis axis{A};

    using Unit_alias<detail::Mp_dimension<A>::template fn, Qty>::Unit_alias;
};

template <class Qty>
using Width = Dimension<Axis::x, Qty>;
template <class Qty>
using Height = Dimension<Axis::y, Qty>;
template <class Qty>
using Depth = Dimension<Axis::z, Qty>;

} // namespace mia

namespace ranges {

template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Dimension<A, Qty1>, mia::Dimension<A, Qty2>> {
    using type = mia::Dimension<A, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Dimension<A, Qty>>
  : mia::detail::Unit_alias_hash<
        mia::detail::Mp_dimension<A>::template fn, Qty> {
};

} // namespace std

namespace mia {

enum class Dimensions;

inline namespace literals {
    inline namespace dimensions_literals { //

        constexpr Dimensions operator""_D(unsigned long long d)
        {
            return gsl::narrow_cast<Dimensions>(d);
        }

    } // namespace dimensions_literals
} // namespace literals

template <Dimensions D, class Qty>
class Size {
public:
    static_assert(D >= 1_D);
    static_assert(Quantity<Qty>{});

    static constexpr Dimensions dimensions{D};
    using quantity = Qty;

private:
    static constexpr boost::hana::range<int, 0, jegp::underlying(dimensions)>
        ints{};

    static constexpr std::array axes{boost::hana::unpack(
        ints, [](auto... int_c) { return std::array{Axis{int_c()}...}; })};

public:
    Size(const Size&) = default;
    Size(Size&&)      = default;
    ~Size()           = default;
    Size& operator=(const Size&) = default;
    Size& operator=(Size&&) = default;

    template <
        Axis... A, class... Qty2,
        CONCEPT_REQUIRES_(
            std::conjunction_v<
                std::bool_constant<boost::hana::equal(axes, std::array{A...})>,
                ranges::Constructible<
                    Dimension<A, quantity>, const Dimension<A, Qty2>&>...>)>
    explicit constexpr Size(const Dimension<A, Qty2>&... dim)
      : dims{[&] {
            (..., Expects((dim > Dimension<A, Qty2>{})));
            return Dims{dim...};
        }()}
    {
    }

    template <
        class Qty2, CONCEPT_REQUIRES_(ranges::Constructible<quantity, Qty2>{})>
    constexpr Size(const Size<dimensions, Qty2>& sz) noexcept(
        std::is_nothrow_copy_constructible_v<Qty2>&&
            std::is_nothrow_constructible_v<quantity, Qty2>)
      : dims{boost::hana::unpack(ints, [&](auto... int_c) {
            return Dims{sz.template get<int_c>()...};
        })}
    {
    }

    constexpr void w(const Width<quantity>& w)
    {
        Expects(w > Width<quantity>{});
        std::get<jegp::underlying(Axis::x)>(dims) = w;
    }
    template <Axis A = Axis::y, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr void h(const Height<quantity>& h)
    {
        Expects(h > Height<quantity>{});
        std::get<jegp::underlying(A)>(dims) = h;
    }
    template <Axis A = Axis::z, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr void d(const Depth<quantity>& d)
    {
        Expects(d > Depth<quantity>{});
        std::get<jegp::underlying(A)>(dims) = d;
    }

    template <Axis A, CONCEPT_REQUIRES_(Axis::x <= A && A <= axes.back())>
    constexpr void set(const Dimension<A, quantity>& dim)
    {
        Expects((dim > Dimension<A, quantity>{}));
        std::get<jegp::underlying(A)>(dims) = dim;
    }

    constexpr Width<quantity> w() const
        noexcept(std::is_nothrow_copy_constructible_v<Width<quantity>>)
    {
        return std::get<jegp::underlying(Axis::x)>(dims);
    }
    template <Axis A = Axis::y, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr Height<quantity> h() const
        noexcept(std::is_nothrow_copy_constructible_v<Height<quantity>>)
    {
        return std::get<jegp::underlying(A)>(dims);
    }
    template <Axis A = Axis::z, CONCEPT_REQUIRES_(A <= axes.back())>
    constexpr Depth<quantity> d() const
        noexcept(std::is_nothrow_copy_constructible_v<Depth<quantity>>)
    {
        return std::get<jegp::underlying(A)>(dims);
    }

    template <std::size_t I>
    constexpr Dimension<Axis{I}, quantity> get() const noexcept(
        std::is_nothrow_copy_constructible_v<Dimension<Axis{I}, quantity>>)
    {
        return std::get<I>(dims);
    }

private:
    static constexpr auto dims_tuple = [](auto... int_c) {
        return std::tuple<Dimension<axes[int_c], quantity>...>{};
    };

    using Dims = decltype(boost::hana::unpack(ints, dims_tuple));

    Dims dims;
};

template <Axis... A, class Qty>
explicit Size(Dimension<A, Qty>...)->Size<Dimensions{sizeof...(A)}, Qty>;

template <class Qty>
using Size2d = Size<2_D, Qty>;
template <class Qty>
using Size3d = Size<3_D, Qty>;

template <
    std::size_t I, Dimensions D, class Qty,
    CONCEPT_REQUIRES_(I < jegp::underlying(D))>
constexpr Dimension<Axis{I}, Qty> get(const Size<D, Qty>& sz) noexcept(
    std::is_nothrow_copy_constructible_v<Dimension<Axis{I}, Qty>>)
{
    return sz.template get<I>();
}
template <
    Axis A, Dimensions D, class Qty,
    CONCEPT_REQUIRES_(Axis::x <= A && A < static_cast<Axis>(D))>
constexpr Dimension<A, Qty> get(const Size<D, Qty>& sz) noexcept(
    std::is_nothrow_copy_constructible_v<Dimension<A, Qty>>)
{
    return sz.template get<jegp::underlying(A)>();
}
template <
    class Dim, Dimensions D, class Qty,
    CONCEPT_REQUIRES_(
        std::is_same_v<Dim, Dimension<Dim::axis, Qty>> &&
        (Axis::x <= Dim::axis && Dim::axis < static_cast<Axis>(D)))>
constexpr Dim get(const Size<D, Qty>& sz) noexcept(
    std::is_nothrow_copy_constructible_v<Dim>)
{
    return sz.template get<jegp::underlying(Dim::axis)>();
}

template <
    Dimensions D, class Qty1, class Qty2,
    CONCEPT_REQUIRES_(ranges::EqualityComparable<Qty1, Qty2>{})>
constexpr auto operator==(
    const Size<D, Qty1>& l,
    const Size<D, Qty2>&
        r) noexcept(noexcept(std::declval<Qty1>() == std::declval<Qty2>()))
{
    return boost::hana::unpack(
        boost::hana::range_c<int, 0, jegp::underlying(D)>, [&](auto... int_c) {
            return (... && (get<int_c>(l) == get<int_c>(r)));
        });
}
template <Dimensions D, class Qty1, class Qty2>
constexpr auto operator!=(
    const Size<D, Qty1>& l,
    const Size<D, Qty2>& r) noexcept(noexcept(!(l == r))) -> decltype(!(l == r))
{
    return !(l == r);
}

} // namespace mia

namespace std {

template <mia::Dimensions D, class Qty>
struct tuple_size<mia::Size<D, Qty>>
  : integral_constant<size_t, jegp::underlying(D)> {
};

template <size_t I, mia::Dimensions D, class Qty>
struct tuple_element<I, mia::Size<D, Qty>> {
    static_assert(I < jegp::underlying(D));

    using type = mia::Dimension<mia::Axis{I}, Qty>;
};

} // namespace std

namespace ranges {

template <mia::Dimensions D, class Qty1, class Qty2>
struct common_type<mia::Size<D, Qty1>, mia::Size<D, Qty2>> {
    using type = mia::Size<D, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace std {

template <mia::Dimensions D, class Qty>
struct hash<mia::Size<D, Qty>> : mia::detail::Tuple_hash<mia::Size<D, Qty>> {
};

} // namespace std

#endif // MIA_SPACIAL_HPP
