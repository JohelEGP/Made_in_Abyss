# Spacial library \[spacial]

## General \[spacial.general]

This clause describes components
that C++ programs may use
to represent spaces.

The following subclauses describe
class templates that represent
coordinates, points, dimensions and sizes, and
helper enumerations,
as summarized in Table \[spacial].

Table \[spacial] -- Spacial library summary

|                  | Subclause    | Header(s)           |
| ---------------- | ------------ | ------------------- |
| \[spacial.enum]  | Enumerations | `<mia/spacial.hpp>` |
| \[spacial.coord] | Coordinates  |
| \[spacial.point] | Points       |
| \[spacial.dim]   | Dimensions   |
| \[spacial.size]  | Sizes        |

## Header `<mia/spacial.hpp>` synopsis \[spacial.syn]

```C++
namespace mia {

// \[spacial.enum], enumerations
enum class Axis;
enum class Coordinates;
enum class Dimensions;

inline namespace literals {
    inline namespace dimensions_literals { //

        // \[spacial.enum.dims], enum class `Dimensions`
        constexpr Dimensions operator""_D(unsigned long long d);

    } // namespace dimensions_literals
} // namespace literals

// \[spacial.coord.cart], Cartesian coordinate
template <Axis A, class Qty>
class Coordinate;

// \[spacial.coord.cart.alias], conventional Cartesian coordinate alias templates
template <class Qty>
using Abscissa = Coordinate</*see below*/, Qty>;
template <class Qty>
using Ordinate = Coordinate</*see below*/, Qty>;
template <class Qty>
using Applicate = Coordinate</*see below*/, Qty>;

} // namespace mia

namespace ranges {

// \[spacial.coord.spec], coordinates specializations
template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Coordinate<A, Qty1>, mia::Coordinate<A, Qty2>>;

} // namespace ranges

namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Coordinate<A, Qty>>;

} // namespace std

namespace mia {

// \[spacial.point.cart], Cartesian point
template <Coordinates C, class Qty>
class Point;

// \[spacial.point.cart.alias] conventional Cartesian point alias templates
template <class Qty>
using Point2d = Point</*see below*/, Qty>;
template <class Qty>
using Point3d = Point</*see below*/, Qty>;

// \[spacial.point.cart.cmp], Cartesian point comparisons
template <Coordinates C, class Qty1, class Qty2>
constexpr auto operator==(
    const Point<C, Qty1>& l, const Point<C, Qty2>& r) noexcept(/*see below*/);
template <Coordinates C, class Qty1, class Qty2>
constexpr auto operator!=(
    const Point<C, Qty1>& l, const Point<C, Qty2>& r) noexcept(/*see below*/);

// \[spacial.point.cart.tuple], Tuple interface to Cartesian point
template <std::size_t I, Coordinates C, class Qty>
constexpr Coordinate</*see below*/, Qty>& get(Point<C, Qty>& pt) noexcept;
template <std::size_t I, Coordinates C, class Qty>
constexpr const Coordinate</*see below*/, Qty>& get(
    const Point<C, Qty>& pt) noexcept;

template <Axis A, Coordinates C, class Qty>
constexpr Coordinate<A, Qty>& get(Point<C, Qty>& pt) noexcept;
template <Axis A, Coordinates C, class Qty>
constexpr const Coordinate<A, Qty>& get(const Point<C, Qty>& pt) noexcept;

template <class Coord, Coordinates C, class Qty>
constexpr Coord& get(Point<C, Qty>& pt) noexcept;
template <class Coord, Coordinates C, class Qty>
constexpr const Coord& get(const Point<C, Qty>& pt) noexcept;

} // namespace mia

namespace std {

template <mia::Coordinates C, class Qty>
struct tuple_size<mia::Point<C, Qty>>;

template <size_t I, mia::Coordinates C, class Qty>
struct tuple_element<I, mia::Point<C, Qty>>;

} // namespace std

namespace ranges {

// \[spacial.point.cart.spec], Cartesian point specializations
template <mia::Coordinates C, class Qty1, class Qty2>
struct common_type<mia::Point<C, Qty1>, mia::Point<C, Qty2>>;

} // namespace ranges

namespace std {

template <mia::Coordinates C, class Qty>
struct hash<mia::Point<C, Qty>>;

} // namespace std

namespace mia {

// \[spacial.dim.cart], Cartesian dimension
template <Axis A, class Qty>
class Dimension;

// \[spacial.dim.cart.alias], conventional Cartesian dimension alias templates
template <class Qty>
using Width = Dimension</*see below*/, Qty>;
template <class Qty>
using Height = Dimension</*see below*/, Qty>;
template <class Qty>
using Depth = Dimension</*see below*/, Qty>;

} // namespace mia

namespace ranges {

// \[spacial.dim.spec], dimensions specializations
template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Dimension<A, Qty1>, mia::Dimension<A, Qty2>>;

} // namespace ranges

namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Dimension<A, Qty>>;

} // namespace std

namespace mia {

// \[spacial.size.cart.template], class template `Size`
template <Dimensions D, class Qty>
class Size;

// \[spacial.size.cart.alias] `Size` alias templates
template <class Qty>
using Size2d = Size</*see below*/, Qty>;
template <class Qty>
using Size3d = Size</*see below*/, Qty>;

// \[spacial.size.cart.cmp], `Size` comparisons
template <Dimensions D, class Qty1, class Qty2>
constexpr auto operator==(
    const Size<D, Qty1>& l, const Size<D, Qty2>& r) noexcept(/*see below*/);
template <Dimensions D, class Qty1, class Qty2>
constexpr auto operator!=(
    const Size<D, Qty1>& l, const Size<D, Qty2>& r) noexcept(/*see below*/);

// \[spacial.size.cart.obs], `Size` dimension observers
template <class Dim, Dimensions D, class Qty>
constexpr Dim get(const Size<D, Qty>& sz) noexcept(/*see below*/);
template <Axis A, Dimensions D, class Qty>
constexpr Dimension<A, Qty> get(const Size<D, Qty>& sz) noexcept(/*see below*/);

// \[spacial.size.cart.struct], `Size` structured bindings support
template <std::size_t I, Dimensions D, class Qty>
constexpr Dimension</*see below*/, Qty> get(const Size<D, Qty>& sz) noexcept(
    /*see below*/);

} // namespace mia

namespace std {

template <mia::Dimensions D, class Qty>
struct tuple_size<mia::Size<D, Qty>>;

template <size_t I, mia::Dimensions D, class Qty>
struct tuple_element<I, mia::Size<D, Qty>>;

} // namespace std

namespace ranges {

// \[spacial.size.cart.spec], `Size` specializations
template <mia::Dimensions D, class Qty1, class Qty2>
struct common_type<mia::Size<D, Qty1>, mia::Size<D, Qty2>>;

} // namespace ranges

namespace std {

template <mia::Dimensions D, class Qty>
struct hash<mia::Size<D, Qty>>;

} // namespace std
```

## Enumerations \[spacial.enum]

### Enum class `Axis` \[spacial.enum.axis]

Non-negative `Axis` values represent Cartesian axes.
Table \[spacial.enum.axis] describes conventional axes.

Table \[spacial.enum.axis] -- Enum class `Axis`

| Enumerator | Value | Meaning     |
| ---------- | ----- | ----------- |
| `x`        | `0`   | The x-axis. |
| `y`        | `1`   | The y-axis. |
| `z`        | `2`   | The z-axis. |

### Enum class `Coordinates` \[spacial.enum.coords]

`Coordinates` values represent a quantity of coordinates.

### Enum class `Dimensions` \[spacial.enum.dims]

`Dimensions` values represent the dimensions of a space.

```C++
constexpr Dimensions operator""_D(unsigned long long d);
```
_Returns:_ `gsl::narrow_cast<Dimensions>(d)`.

## Coordinates \[spacial.coord]

### Overview \[spacial.coord.overview]

This subclause describes class templates that represent coordinates.

### Cartesian \[spacial.coord.cart]

#### Class template `Coordinate` \[spacial.coord.cart.template]

This subclause describes class template `Coordinate`
that represents Cartesian coordinates.

```C++
namespace mia {

template <Axis A>
struct Mp_coordinate { /*exposition only*/
    template <class Qty>
    using fn = Coordinate<A, Qty>;
};

template <Axis A, class Qty>
class Coordinate : public Unit_alias<Mp_coordinate<A>::template fn, Qty> {
public:
    static constexpr Axis axis{A};

    using Unit_alias<Mp_coordinate<A>::template fn, Qty>::Unit_alias;
};

} // namespace mia
```
`A >= Axis::x` shall be `true`.

#### Conventional alias templates \[spacial.coord.cart.alias]

This subclause describes alias templates
for conventional Cartesian coordinates.

- `Abscissa`  describes x-coordinates.
- `Ordinate`  describes y-coordinates.
- `Applicate` describes z-coordinates.

```C++
template <class Qty>
using Abscissa = Coordinate<Axis::x, Qty>;
template <class Qty>
using Ordinate = Coordinate<Axis::y, Qty>;
template <class Qty>
using Applicate = Coordinate<Axis::z, Qty>;
```

### Specializations \[spacial.coord.spec]

```C++
namespace ranges {

template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Coordinate<A, Qty1>, mia::Coordinate<A, Qty2>> {
    using type = mia::Coordinate<A, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges
```

```C++
namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Coordinate<A, Qty>>;

} // namespace std
```
This specialization is enabled (C++ Standard's \[unord.hash])
if and only if `std::hash<Qty>` is enabled.
The special member functions are `noexcept` and `constexpr`
if the corresponding special member functions of `std::hash<Qty>`
are `noexcept` and `constexpr`, respectively.
The function call operator is `constexpr`,
and is `noexcept` if the function call operator
of `std::hash<Qty>` is `noexcept`.

## Points \[spacial.point]

### Overview \[spacial.point.overview]

This subclause describes class templates
that represent points in coordinate systems.

### Cartesian \[spacial.point.cart]

#### Overview \[spacial.point.cart.overview]

This subclause describes class template `Point`
that represents Cartesian points.

#### Class template `Point` \[spacial.point.cart.template]

```C++
namespace mia {

template <Coordinates C, class Qty>
class Point {
public:
    static constexpr Coordinates coordinates{C};
    using quantity = Qty;

    Point()             = default;
    Point(const Point&) = default;
    Point(Point&&)      = default;
    ~Point()            = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    // \[spacial.point.cart.cons], constructors
    template <Axis... A, class... Qty2>
    explicit constexpr Point(const Coordinate<A, Qty2>&... coord) noexcept(
        /*see below*/);
    template <class Qty2>
    constexpr Point(const Point<coordinates, Qty2>& pt) noexcept(/*see below*/);

    // \[spacial.point.cart.coord], conventional coordinate access
    constexpr Abscissa<quantity>& x() noexcept;
    constexpr Ordinate<quantity>& y() noexcept;
    constexpr Applicate<quantity>& z() noexcept;
    constexpr const Abscissa<quantity>& x() const noexcept;
    constexpr const Ordinate<quantity>& y() const noexcept;
    constexpr const Applicate<quantity>& z() const noexcept;

private:
    // \[spacial.point.cart.coords], exposition only member `coords`
    /*see below*/ coords; /*exposition only*/
};

template <Axis... A, class Qty>
explicit Point(Coordinate<A, Qty>...)->Point<Coordinates{sizeof...(A)}, Qty>;

} // namespace mia
```
`C >= Coordinates{1}` shall be `true`.

`Quantity<Qty>{}` shall be `true`.

#### Exposition only member `coords` \[spacial.point.cart.coords]

Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(coordinates)`) in order.
The type of `coords` shall be `std::tuple<Coordinate<A, quantity>...>`.

#### Constructors \[spacial.point.cart.cons]

```C++
template <Axis... A, class... Qty2>
explicit constexpr Point(const Coordinate<A, Qty2>&... coord) noexcept(
    /*see below*/);
```
_Effects:_ Initializes `coords` with `coord...`.

_Throws:_ Any exception thrown by the initialization of `coords`.

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
std::conjunction_v<std::is_nothrow_constructible<
    Coordinate<A, quantity>, const Coordinate<A, Qty2>&>...>
```
This constructor shall not participate in overload resolution unless
`A` represents the range \[`Axis::x`, `static_cast<Axis>(coordinates)`) in order
and
```C++
std::conjunction_v<ranges::Constructible<
    Coordinate<A, quantity>, const Coordinate<A, Qty2>&>...>
```
is `true`.

```C++
template <class Qty2>
constexpr Point(const Point<coordinates, Qty2>& pt) noexcept(/*see below*/);
```
Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(coordinates)`) in order.

_Effects:_ Equivalent to `Point{get<A>(pt)...}`.

#### Conventional coordinate access \[spacial.point.cart.coord]

```C++
constexpr Abscissa<quantity>& x() noexcept;
constexpr Ordinate<quantity>& y() noexcept;
constexpr Applicate<quantity>& z() noexcept;
constexpr const Abscissa<quantity>& x() const noexcept;
constexpr const Ordinate<quantity>& y() const noexcept;
constexpr const Applicate<quantity>& z() const noexcept;
```
Let `I` be `0`, `1`, and `2`
for the descriptions of `x`, `y`, and `z`, respectively.

_Returns:_ `std::get<I>(coords)`.

_Remarks:_ This function shall not participate in overload resolution unless
`I < jegp::underlying(coordinates)`.

#### Tuple interface \[spacial.point.cart.tuple]

```C++
template <std::size_t I, Coordinates C, class Qty>
constexpr Coordinate<Axis{I}, Qty>& get(Point<C, Qty>& pt) noexcept;
template <std::size_t I, Coordinates C, class Qty>
constexpr const Coordinate<Axis{I}, Qty>& get(const Point<C, Qty>& pt) noexcept;
```
_Returns:_ A reference to the coordinate of the `I`_th_ axis held by `pt`.

_Remarks:_ This function shall not participate in overload resolution unless
`I < jegp::underlying(C)`.

```C++
template <Axis A, Coordinates C, class Qty>
constexpr Coordinate<A, Qty>& get(Point<C, Qty>& pt) noexcept;
template <Axis A, Coordinates C, class Qty>
constexpr const Coordinate<A, Qty>& get(const Point<C, Qty>& pt) noexcept;
```
_Effects:_ Equivalent to: `return get<jegp::underlying(A)>(pt);`

_Remarks:_ This function shall not participate in overload resolution unless
`A` is the range \[`Axis::x`, `static_cast<Axis>(C)`).

```C++
template <class Coord, Coordinates C, class Qty>
constexpr Coord& get(Point<C, Qty>& pt) noexcept;
template <class Coord, Coordinates C, class Qty>
constexpr const Coord& get(const Point<C, Qty>& pt) noexcept;
```
_Effects:_ Equivalent to: `return get<Coord::axis>(pt);`

_Remarks:_ This function shall not participate in overload resolution unless
`Coord` is of the form `Coordinate<A, Qty>`.

```C++
namespace std {

template <mia::Coordinates C, class Qty>
struct tuple_size<mia::Point<C, Qty>>
  : integral_constant<size_t, jegp::underlying(C)> {
};

} // namespace std
```

```C++
namespace std {

template <size_t I, mia::Coordinates C, class Qty>
struct tuple_element<I, mia::Point<C, Qty>> {
    using type = mia::Coordinate<mia::Axis{I}, Qty>;
};

} // namespace std
```
`I < jegp::underlying(C)` shall be `true`.

#### Specializations \[spacial.point.cart.spec]

```C++
namespace ranges {

template <mia::Coordinates C, class Qty1, class Qty2>
struct common_type<mia::Point<C, Qty1>, mia::Point<C, Qty2>> {
    using type = mia::Point<C, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges
```

```C++
namespace std {

template <mia::Coordinates C, class Qty>
struct hash<mia::Point<C, Qty>>;

} // namespace std
```
Let `Coord` be a parameter pack
representing the well-formed instantiations of
`std::tuple_element_t<I, mia::Point<C, Qty>>`.

This specialization is enabled (C++ Standard's \[unord.hash])
if and only if `std::hash<Coord>...` are enabled.
The special member functions are `noexcept` and `constexpr`
if the corresponding special member functions of `std::hash<Coord>...`
are `noexcept` and `constexpr`, respectively.
The function call operator is `constexpr`,
and is `noexcept` if the function call operator
of `std::hash<Coord>...` are `noexcept`.

#### Comparisons \[spacial.point.cart.cmp]

```C++
template <Coordinates C, class Qty1, class Qty2>
constexpr auto operator==(
    const Point<C, Qty1>& l, const Point<C, Qty2>& r) noexcept(/*see below*/);
```
Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(C)`) in order.

_Effects:_ Equivalent to: `return (... && (get<A>(l) == get<A>(r)));`

_Throws:_ Any exception thrown by the operations in the _Effects:_ element.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept((... && (get<A>(l) == get<A>(r))))`.
This function shall not participate in overload resolution unless
```C++
std::conjunction_v<ranges::EqualityComparable<
    const Coordinate<A, Qty1>&, const Coordinate<A, Qty2>&>...>
```
is `true`.

```C++
template <Coordinates C, class Qty1, class Qty2>
constexpr auto operator!=(
    const Point<C, Qty1>& l, const Point<C, Qty2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return !(l == r);`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(!(l == r))`.

#### Conventional alias templates \[spacial.point.cart.alias]

- `Point2d` describes points in Cartesian planes.
- `Point3d` describes points in 3-dimensional Cartesian spaces.

```C++
template <class Qty>
using Point2d = Point<Coordinates{2}, Qty>;
template <class Qty>
using Point3d = Point<Coordinates{3}, Qty>;
```

## Dimensions \[spacial.dim]

### Overview \[spacial.dim.overview]

This subclause describes class templates that represent dimensions.

### Cartesian \[spacial.dim.cart]

#### Overview \[spacial.dim.cart.overview]

This subclause describes class template `Dimension`
that represents dimensions aligned to Cartesian axes.

#### Class template `Dimension` \[spacial.dim.cart.template]

```C++
namespace mia {

template <Axis A>
struct Mp_dimension { /*exposition only*/
    template <class Qty>
    using fn = Dimension<A, Qty>;
};

template <Axis A, class Qty>
class Dimension : public Unit_alias<Mp_dimension<A>::template fn, Qty> {
public:
    static constexpr Axis axis{A};

    using Unit_alias<Mp_dimension<A>::template fn, Qty>::Unit_alias;
};

} // namespace mia
```
`A >= Axis::x` shall be `true`.

#### Conventional alias templates \[spacial.dim.cart.alias]

This subclause describes alias templates
for conventional Cartesian dimensions.

- `Width`  describes dimensions aligned to x-axes.
- `Height` describes dimensions aligned to y-axes.
- `Depth`  describes dimensions aligned to z-axes.

```C++
template <class Qty>
using Width = Dimension<Axis::x, Qty>;
template <class Qty>
using Height = Dimension<Axis::y, Qty>;
template <class Qty>
using Depth = Dimension<Axis::z, Qty>;
```

### Specializations \[spacial.dim.spec]

```C++
namespace ranges {

template <mia::Axis A, class Qty1, class Qty2>
struct common_type<mia::Dimension<A, Qty1>, mia::Dimension<A, Qty2>> {
    using type = mia::Dimension<A, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges
```

```C++
namespace std {

template <mia::Axis A, class Qty>
struct hash<mia::Dimension<A, Qty>>;

} // namespace std
```
This specialization is enabled (C++ Standard's \[unord.hash])
if and only if `std::hash<Qty>` is enabled.
The special member functions are `noexcept` and `constexpr`
if the corresponding special member functions of `std::hash<Qty>`
are `noexcept` and `constexpr`, respectively.
The function call operator is `constexpr`,
and is `noexcept` if the function call operator
of `std::hash<Qty>` is `noexcept`.

## Sizes \[spacial.size]

### Overview \[spacial.size.overview]

This subclause describes class templates
that represent sizes in coordinate systems.

### Cartesian \[spacial.size.cart]

#### Overview \[spacial.size.cart.overview]

This subclause describes class template `Size`
that represents sizes with dimensions aligned to Cartesian axes.

#### Class template `Size` \[spacial.size.cart.template]

```C++
namespace mia {

template <Dimensions D, class Qty>
class Size {
public:
    static constexpr Dimensions dimensions{D};
    using quantity = Qty;

    Size(const Size&) = default;
    Size(Size&&)      = default;
    ~Size()           = default;
    Size& operator=(const Size&) = default;
    Size& operator=(Size&&) = default;

    // \[spacial.size.cart.cons], constructors
    template <Axis... A, class... Qty2>
    explicit constexpr Size(const Dimension<A, Qty2>&... dim);
    template <class Qty2>
    constexpr Size(const Size<dimensions, Qty2>& sz) noexcept(/*see below*/);

    // \[spacial.size.cart.mod], dimension modifiers
    constexpr void w(const Width<quantity>& dim);
    constexpr void h(const Height<quantity>& dim);
    constexpr void d(const Depth<quantity>& dim);

    template <Axis A>
    constexpr void set(const Dimension<A, quantity>& dim);

    // \[spacial.size.cart.obs], dimension observers
    constexpr Width<quantity> w() const noexcept(/*see below*/);
    constexpr Height<quantity> h() const noexcept(/*see below*/);
    constexpr Depth<quantity> d() const noexcept(/*see below*/);

private:
    // \[spacial.size.cart.dims], exposition only member `dims`
    /*see below*/ dims; /*exposition only*/
};

template <Axis... A, class Qty>
explicit Size(Dimension<A, Qty>...)->Size<Dimensions{sizeof...(A)}, Qty>;

} // namespace mia
```
`D >= 1_D` shall be `true`.

`Quantity<Qty>{}` shall be `true`.

The dimensions of a `Size` object are always greater than zero.

#### Exposition only member `dims` \[spacial.size.cart.dims]

Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(dimensions)`) in order.
The type of `dims` shall be `std::tuple<Dimension<A, quantity>...>`.

#### Constructors \[spacial.size.cart.cons]

```C++
template <Axis... A, class... Qty2>
explicit constexpr Size(const Dimension<A, Qty2>&... dim);
```
_Requires:_ The dimension arguments are greater than zero.

_Effects:_ Initializes `dims` with `dim...`.

_Throws:_ Any exception thrown by the initialization of `dims`.

_Remarks:_ This constructor shall not participate in overload resolution unless
`A` represents the range \[`Axis::x`, `static_cast<Axis>(dimensions)`) in order
and
```C++
std::conjunction_v<
    ranges::Constructible<Dimension<A, quantity>, const Dimension<A, Qty2>&>...>
```
is `true`.

```C++
template <class Qty2>
constexpr Size(const Size<dimensions, Qty2>& sz) noexcept(/*see below*/);
```
Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(dimensions)`) in order.

_Effects:_ Equivalent to `Size{get<A>(sz)...}`.

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
std::conjunction_v<
    std::is_nothrow_copy_constructible<Dimension<A, Qty2>>...,
    std::is_nothrow_constructible<
        Dimension<A, quantity>, Dimension<A, Qty2>>...>
```

#### Dimension modifiers \[spacial.size.cart.mod]

```C++
constexpr void w(const Width<quantity>& dim);
constexpr void h(const Height<quantity>& dim);
constexpr void d(const Depth<quantity>& dim);

template <Axis A>
constexpr void set(const Dimension<A, quantity>& dim);
```
Let `I` be `0`, `1`, `2`, and `jegp::underlying(A)`
for the descriptions of `w`, `h`, `d`, and `set`, respectively.

_Requires:_ `dim` is greater than zero.

_Effects:_ Equivalent to: `std::get<I>(dims) = dim;`

_Remarks:_ `set` shall not participate in overload resolution unless
`A` is the range \[`Axis::x`, `static_cast<Axis>(dimensions)`).

#### Dimension observers \[spacial.size.cart.obs]

```C++
constexpr Width<quantity> w() const noexcept(/*see below*/);
constexpr Height<quantity> h() const noexcept(/*see below*/);
constexpr Depth<quantity> d() const noexcept(/*see below*/);
```
Let `I` be `0`, `1`, and `2`
for the descriptions of `w`, `h`, and `d`, respectively.

_Effects:_ Equivalent to: `return std::get<I>(dims);`

_Remarks:_ The expression inside `noexcept` is equivalent to
`std::is_nothrow_copy_constructible_v<Dimension<Axis{I}, quantity>>`.

```C++
template <class Dim, Dimensions D, class Qty>
constexpr Dim get(const Size<D, Qty>& sz) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return get<Dim::axis>(sz);`

_Remarks:_ This function shall not participate in overload resolution unless
`Dim` is of the form `Dimension<A, Qty>`.

```C++
template <Axis A, Dimensions D, class Qty>
constexpr Dimension<A, Qty> get(const Size<D, Qty>& sz) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return get<jegp::underlying(A)>(sz);`

_Remarks:_ This function shall not participate in overload resolution unless
`A` is the range \[`Axis::x`, `static_cast<Axis>(D)`).

#### Structured bindings support \[spacial.size.cart.struct]

```C++
template <std::size_t I, Dimensions D, class Qty>
constexpr Dimension<Axis{I}, Qty> get(const Size<D, Qty>& sz) noexcept(
    /*see below*/);
```
_Returns:_ The dimension of the `I`_th_ axis held by `sz`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`std::is_nothrow_copy_constructible_v<Dimension<Axis{I}, Qty>>`.
This function shall not participate in overload resolution unless
`I < jegp::underlying(D)`.

```C++
namespace std {

template <mia::Dimensions D, class Qty>
struct tuple_size<mia::Size<D, Qty>>
  : integral_constant<size_t, jegp::underlying(D)> {
};

} // namespace std
```

```C++
namespace std {

template <size_t I, mia::Dimensions D, class Qty>
struct tuple_element<I, mia::Size<D, Qty>> {
    using type = mia::Dimension<mia::Axis{I}, Qty>;
};

} // namespace std
```
`I < jegp::underlying(D)` shall be `true`.

#### Specializations \[spacial.size.cart.spec]

```C++
namespace ranges {

template <mia::Dimensions D, class Qty1, class Qty2>
struct common_type<mia::Size<D, Qty1>, mia::Size<D, Qty2>> {
    using type = mia::Size<D, common_type_t<Qty1, Qty2>>;
};

} // namespace ranges
```

```C++
namespace std {

template <mia::Dimensions D, class Qty>
struct hash<mia::Size<D, Qty>>;

} // namespace std
```
Let `Dim` be a parameter pack
representing the well-formed instantiations of
`std::tuple_element_t<I, mia::Size<D, Qty>>`.

This specialization is enabled (C++ Standard's \[unord.hash])
if and only if `std::hash<Dim>...` are enabled.
The special member functions are `noexcept` and `constexpr`
if the corresponding special member functions of `std::hash<Dim>...`
are `noexcept` and `constexpr`, respectively.
The function call operator is `constexpr`,
and is `noexcept` if the function call operator
of `std::hash<Dim>...` are `noexcept`.

#### Comparisons \[spacial.size.cart.cmp]

```C++
template <Dimensions D, class Qty1, class Qty2>
constexpr auto operator==(
    const Size<D, Qty1>& l, const Size<D, Qty2>& r) noexcept(/*see below*/);
```
Let `A` be a parameter pack of `Axis` values
representing the range \[`Axis::x`, `static_cast<Axis>(D)`) in order.

_Effects:_ Equivalent to: `return (... && (get<A>(l) == get<A>(r)));`

_Throws:_ Any exception thrown by the operations in the _Effects:_ element.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept((... && (get<A>(l) == get<A>(r))))`.
This function shall not participate in overload resolution unless
```C++
std::conjunction_v<
    ranges::EqualityComparable<Dimension<A, Qty1>, Dimension<A, Qty2>>...>
```
is `true`.

```C++
template <Dimensions D, class Qty1, class Qty2>
constexpr auto operator!=(
    const Size<D, Qty1>& l, const Size<D, Qty2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return !(l == r);`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(!(l == r))`.

#### Conventional alias templates \[spacial.size.cart.alias]

- `Size2d` describes rectangular areas
with dimensions aligned to Cartesian axes.
- `Size3d` describes rectangular volumes
with dimensions aligned to Cartesian axes.

```C++
template <class Qty>
using Size2d = Size<2_D, Qty>;
template <class Qty>
using Size3d = Size<3_D, Qty>;
```
