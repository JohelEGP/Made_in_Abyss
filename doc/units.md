# Units library \[units]

## General \[units.general]

This clause describes components
that C++ programs may use
to represent quantities.

The following subclauses describe
alias templates
that represent units of measurement
and their dimensions
using the `units` framework,
and a class template
to describe more specific quantities,
as summarized in Table \[units].

Table \[units] -- Units library summary

|                  | Subclause     | Header(s)         |
| ---------------- | ------------- | ----------------- |
| \[unit.dims]     | Dimensions    | `<mia/units.hpp>` |
| \[display.units] | Display units |
| \[unit.alias]    | Unit alias    |

## Header `<mia/units.hpp>` synopsis \[units.syn]

```C++
namespace mia {

namespace dimension {

    // \[unit.dims], dimensions
    struct Display_length_tag;

    using Display_length = units::make_dimension<Display_length_tag>;

} // namespace dimension

// \[display.units], display units

inline namespace display_length { //

    // \[display.units.aliases], aliases
    template <class Arithmetic>
    using Pixels = /*see below*/;

} // namespace display_length

inline namespace literals {
    inline namespace pixels_literals { //

        // \[display.units.literals], suffix for `Pixels` literals
        constexpr Pixels<int> operator""_px(unsigned long long px);
        constexpr Pixels<double> operator""_px(long double px);

    } // namespace pixels_literals
} // namespace literals

// \[unit.alias.template], class template `Unit_alias`
template <template <class> class Alias, class Aliased>
class Unit_alias;

// \[unit.alias.nonmember], non-member arithmetic
template <template <class> class Alias, class Aliased>
constexpr auto operator+(const Unit_alias<Alias, Aliased>& a) noexcept(
    /*see below*/);
template <template <class> class Alias, class Aliased>
constexpr auto operator-(const Unit_alias<Alias, Aliased>& a) noexcept(
    /*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator+(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator-(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator*(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator*(
    const One& l, const Unit_alias<Alias, Aliased>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator/(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator/(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator%(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator%(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);

// \[unit.alias.cmp], comparisons
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator==(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator!=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator<(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator<=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);

// \[unit.alias.io], I/O

template <class... T, template <class> class Alias, class Aliased>
std::basic_ostream<T...>& operator<<(
    std::basic_ostream<T...>& os, const Unit_alias<Alias, Aliased>& a);

} // namespace mia

// \[unit.alias.specs], specializations

namespace ranges {

template <template <class> class Alias, class Aliased1, class Aliased2>
struct common_type<
    mia::Unit_alias<Alias, Aliased1>, mia::Unit_alias<Alias, Aliased2>>;

} // namespace ranges

namespace std {

template <template <class> class Alias, class Aliased>
struct hash<mia::Unit_alias<Alias, Aliased>>;

} // namespace std
```

## Dimensions \[unit.dims]

This subclause describes
program-defined dimensions.

```C++
namespace mia::dimension {

struct Display_length_tag {
    static constexpr gsl::czstring<> name{"display length"};
    static constexpr gsl::czstring<> abbreviation{"px"};
};

} // namespace mia::dimension
```

_Display length_ is a base quantity
represented by `mia::dimension::Display_length`.
The pixel is its base unit.

## Display units \[display.units]

### Overview \[display.units.overview]

This subclause describes
units of display length
and derived units thereof.

### Aliases \[display.units.aliases]

```C++
template <class Arithmetic>
using Pixels = units::unit<
    units::unit_conversion<std::ratio<1>, mia::dimension::Display_length>,
    Arithmetic>;
```

A _pixel_ is
"the smallest addressable element
in an all points addressable display device"
([Wikipedia](https://en.wikipedia.org/wiki/Pixel))
"that contribute\[s] to the displayed or sensed color
when viewed at a distance"
([Wikipedia](https://en.wikipedia.org/wiki/Pixel#Subpixels)).
It is represented
by specializations of the template aliased by `Pixels`
and convertible specializations thereof.

### Suffix for `Pixels` literals \[display.units.literals]

```C++
constexpr Pixels<int> operator""_px(unsigned long long px);
```
_Returns:_ `Pixels<int>{gsl::narrow_cast<int>(px)}`.

```C++
constexpr Pixels<double> operator""_px(long double px);
```
_Returns:_ `Pixels<double>{gsl::narrow_cast<double>(px)}`.

## Unit alias \[unit.alias]

### Overview \[unit.alias.overview]

The following subclauses describe
`Unit_alias<Alias, Aliased>`,
a [strong type alias] of `Aliased`.
It holds an object of the aliased type
and wraps its `WeakQuantityWith` interface.
`Alias` is used to identify
the related strong type aliases.

[strong type alias]: https://arne-mertz.de/2016/11/stronger-types/

### Class template `Unit_alias` \[unit.alias.template]

```C++
namespace mia {

template <template <class> class Alias, class Aliased>
class Unit_alias {
public:
    using aliased = Aliased;
    using derived = Alias<aliased>;

    // \[unit.alias.cons], constructors
    Unit_alias() = default;
    template <class Aliased2>
    explicit constexpr Unit_alias(const Aliased2& a) noexcept(/*see below*/);
    template <class Aliased2>
    EXPLICIT constexpr Unit_alias(
        const Unit_alias<Alias, Aliased2>& a) noexcept(/*see below*/);
    ~Unit_alias()                 = default;
    Unit_alias(const Unit_alias&) = default;
    Unit_alias& operator=(const Unit_alias&) = default;

    // \[unit.alias.obs], observer
    constexpr aliased unaliased() const noexcept(/*see below*/);

    // \[unit.alias.arithmetic], arithmetic
    constexpr derived& operator++() noexcept(/*see below*/);
    constexpr derived& operator--() noexcept(/*see below*/);
    constexpr derived operator++(int) noexcept(/*see below*/);
    constexpr derived operator--(int) noexcept(/*see below*/);
    template <class Aliased2>
    constexpr derived& operator+=(
        const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
    template <class Aliased2>
    constexpr derived& operator-=(
        const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
    template <class One>
    constexpr derived& operator*=(const One& r) noexcept(/*see below*/);
    template <class One>
    constexpr derived& operator/=(const One& r) noexcept(/*see below*/);
    template <class One>
    constexpr derived& operator%=(const One& r) noexcept(/*see below*/);
    template <class Aliased2>
    constexpr derived& operator%=(
        const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);

private:
    aliased unaliased_; /*exposition only*/
};

} // namespace mia
```

`WeakQuantity<Aliased>()`
shall be `true`.

`ranges::DerivedFrom<Alias<Aliased>, Unit_alias<Alias, Aliased>>()`
shall be `true`,
no diagnostic required.

Let `Aliased1` and `Aliased2` be types
such that `WeakQuantityWith<Aliased1, Aliased2>()` is `true`.
`ranges::common_type_t<Alias<Aliased1>, Alias<Aliased2>>`
shall name
`Alias<ranges::common_type_t<Aliased1, Aliased2>>`,
no diagnostic required.

Members of `Unit_alias`
shall not throw exceptions
other than those thrown
by the indicated operations
on their aliased objects.

#### Constructors \[unit.alias.cons]

```C++
template <class Aliased2>
explicit constexpr Unit_alias(const Aliased2& a) noexcept(/*see below*/);
```
_Effects:_ Initializes `unaliased_` with `a`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`std::is_nothrow_constructible_v<aliased, const Aliased2&>`.
This constructor shall not participate in overload resolution
unless `ranges::Constructible<aliased, const Aliased2&>()` is `true`.

```C++
template <class Aliased2>
EXPLICIT constexpr Unit_alias(const Unit_alias<Alias, Aliased2>& a) noexcept(
    /*see below*/);
```
_Effects:_ Initializes `unaliased_` with `a.unaliased()`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(a.unaliased()) && std::is_nothrow_constructible_v<aliased, Aliased2>`.
This constructor shall not participate in overload resolution
unless `ranges::Constructible<aliased, Aliased2>()` is `true`.
The constructor is explicit if and only if
`ranges::ConvertibleTo<Aliased2, aliased>()` is `false`.

#### Observer \[unit.alias.obs]

```C++
constexpr aliased unaliased() const noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return unaliased_;`

_Remarks:_ The expression inside `noexcept` is equivalent to
`std::is_nothrow_copy_constructible_v<aliased>`.

#### Arithmetic \[unit.alias.arithmetic]

```C++
constexpr derived& operator++() noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `++unaliased_`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(++std::declval<aliased&>())`.

```C++
constexpr derived& operator--() noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `--unaliased_`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(--std::declval<aliased&>())`.

```C++
constexpr derived operator++(int) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return derived(unaliased_++);`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(derived(std::declval<aliased&>()++))`.

```C++
constexpr derived operator--(int) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return derived(unaliased_--);`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(derived(std::declval<aliased&>()--))`.

```C++
template <class Aliased2>
constexpr derived& operator+=(const Unit_alias<Alias, Aliased2>& r) noexcept(
    /*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ += r.unaliased()`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() += r.unaliased())`.
This function shall not participate in overload resolution
unless `WeakQuantityWith<aliased, Aliased2>()` is `true`.

```C++
template <class Aliased2>
constexpr derived& operator-=(const Unit_alias<Alias, Aliased2>& r) noexcept(
    /*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ -= r.unaliased()`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() -= r.unaliased())`.
This function shall not participate in overload resolution
unless `WeakQuantityWith<aliased, Aliased2>()` is `true`.

```C++
template <class One>
constexpr derived& operator*=(const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ *= r`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() *= r)`.
This function shall not participate in overload resolution
unless `QuantityOneWith<One, aliased>()` is `true`.

```C++
template <class One>
constexpr derived& operator/=(const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ /= r`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() /= r)`.
This function shall not participate in overload resolution
unless `QuantityOneWith<One, aliased>()` is `true`.

```C++
template <class One>
constexpr derived& operator%=(const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ %= r`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() %= r)`.
This function shall not participate in overload resolution
unless `QuantityOneWith<One, aliased>()` is `true`.

```C++
template <class Aliased2>
constexpr derived& operator%=(const Unit_alias<Alias, Aliased2>& r) noexcept(
    /*see below*/);
```
_Effects:_ Equivalent to: `unaliased_ %= r.unaliased()`.

_Returns:_ `jegp::static_downcast<derived&>(*this)`.

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(std::declval<aliased&>() %= r.unaliased())`.
This function shall not participate in overload resolution
unless `WeakQuantityWith<aliased, Aliased2>()` is `true`.

#### Non-member arithmetic \[unit.alias.nonmember]

```C++
template <template <class> class Alias, class Aliased>
constexpr auto operator+(const Unit_alias<Alias, Aliased>& a) noexcept(
    /*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(+a.unaliased())>(+a.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(+a.unaliased())>(+a.unaliased()))
```

```C++
template <template <class> class Alias, class Aliased>
constexpr auto operator-(const Unit_alias<Alias, Aliased>& a) noexcept(
    /*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(-a.unaliased())>(-a.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(-a.unaliased())>(-a.unaliased()))
```

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator+(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() + r.unaliased())>(
    l.unaliased() + r.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() + r.unaliased())>(
    l.unaliased() + r.unaliased()))
```
This function shall not participate in overload resolution
unless `WeakQuantityWith<Aliased1, Aliased2>()` is `true`.

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator-(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() - r.unaliased())>(
    l.unaliased() - r.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() - r.unaliased())>(
    l.unaliased() - r.unaliased()))
```
This function shall not participate in overload resolution
unless `WeakQuantityWith<Aliased1, Aliased2>()` is `true`.

```C++
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator*(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() * r)>(l.unaliased() * r);
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() * r)>(Alias(l.unaliased() * r))
```
This function shall not participate in overload resolution
unless `QuantityOneWith<One, Aliased>()` is `true`.

```C++
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator*(
    const One& l, const Unit_alias<Alias, Aliased>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l * r.unaliased())>(l * r.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l * r.unaliased())>(l * r.unaliased()))
```
This function shall not participate in overload resolution
unless `QuantityOneWith<One, Aliased>()` is `true`.

```C++
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator/(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() / r)>(l.unaliased() / r);
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() / r)>(l.unaliased() / r))
```
This function shall not participate in overload resolution
unless `QuantityOneWith<One, Aliased>()` is `true`.

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator/(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return l.unaliased() / r.unaliased();`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(l.unaliased() / r.unaliased())`.
This function shall not participate in overload resolution
unless `WeakQuantityWith<Aliased1, Aliased2>()` is `true`.

```C++
template <template <class> class Alias, class Aliased, class One>
constexpr auto operator%(
    const Unit_alias<Alias, Aliased>& l, const One& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() % r)>(l.unaliased() % r);
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() % r)>(l.unaliased() % r))
```
This function shall not participate in overload resolution
unless `QuantityOneWith<One, Aliased>()` is `true`.

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator%(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
return Alias<decltype(l.unaliased() % r.unaliased())>(
    l.unaliased() % r.unaliased());
```

_Remarks:_ The expression inside `noexcept` is equivalent to
```C++
noexcept(Alias<decltype(l.unaliased() % r.unaliased())>(
    l.unaliased() % r.unaliased()))
```
This function shall not participate in overload resolution
unless `WeakQuantityWith<Aliased1, Aliased2>()` is `true`.

#### Comparisons \[unit.alias.cmp]

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator==(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return l.unaliased() == r.unaliased();`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(l.unaliased() == r.unaliased())`.
This function shall not participate in overload resolution
unless `ranges::EqualityComparable<Aliased1, Aliased2>()` is `true`.

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator!=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return !(l == r);`

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator<(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return l.unaliased() < r.unaliased();`

_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept(l.unaliased() < r.unaliased())`.
This function shall not participate in overload resolution
unless `ranges::TotallyOrdered<Aliased1, Aliased2>()` is `true`.

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return r < l;`

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator<=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return !(r < l);`

```C++
template <template <class> class Alias, class Aliased1, class Aliased2>
constexpr auto operator>=(
    const Unit_alias<Alias, Aliased1>& l,
    const Unit_alias<Alias, Aliased2>& r) noexcept(/*see below*/);
```
_Effects:_ Equivalent to: `return !(l < r);`

#### I/O \[unit.alias.io]

```C++
template <class... T, template <class> class Alias, class Aliased>
std::basic_ostream<T...>& operator<<(
    std::basic_ostream<T...>& os, const Unit_alias<Alias, Aliased>& a);
```

_Effects:_ Equivalent to: `return os << a.unaliased();`

#### Specializations \[unit.alias.specs]

```C++
namespace ranges {

template <template <class> class Alias, class Aliased1, class Aliased2>
struct common_type<
    mia::Unit_alias<Alias, Aliased1>, mia::Unit_alias<Alias, Aliased2>> {
    using type =
        mia::Unit_alias<Alias, ranges::common_type_t<Aliased1, Aliased2>>;
};

} // namespace ranges
```

```C++
namespace std {

template <template <class> class Alias, class Aliased>
struct hash<mia::Unit_alias<Alias, Aliased>>;

} // namespace std
```

This specialization is enabled (C++ Standard's \[unord.hash])
if and only if `std::hash<Aliased>` is enabled.
The special member functions are `noexcept` and `constexpr`
if the corresponding special member functions of `std::hash<Aliased>`
are `noexcept` and `constexpr`, respectively.
The function call operator is `constexpr`,
and is `noexcept` if the function call operator
of `std::hash<Aliased>` is `noexcept`.
