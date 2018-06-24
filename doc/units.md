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
as summarized in Table \[units].

Table \[units] -- Units library summary

|                     | Subclause     | Header(s)         |
| ------------------- | ------------- | ----------------- |
| \[units.dimensions] | Dimensions    | `<mia/units.hpp>` |
| \[units.display]    | Display units |

## Header `<mia/units.hpp>` synopsis \[units.syn]

```C++
namespace mia {

namespace dimension {

    // \[units.dimensions], dimensions
    struct Display_length_tag;

    using Display_length = units::make_dimension<Display_length_tag>;

} // namespace dimension

// \[units.display], display units

inline namespace display_length { //

    // \[units.display.aliases], aliases
    template <class Arithmetic>
    using Pixels = /*see below*/

} // namespace display_length

inline namespace literals {
    inline namespace pixels_literals { //

        // \[units.display.literals], suffix for `Pixels` literals
        constexpr Pixels<double> operator""_px(long double px) noexcept;
        constexpr Pixels<int> operator""_px(unsigned long long px) noexcept;

    } // namespace pixels_literals
} // namespace literals

} // namespace mia
```

## Dimensions \[units.dimensions]

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

_Display length_ is a base quantity.
The pixel is its base unit.
It is represented by `mia::dimension::Display_length`.

## Display units \[units.display]

### Overview \[units.display.overview]

This subclause describes
units of display length
and derived units thereof.

### Aliases \[units.display.aliases]

```C++
template <class Arithmetic>
using Pixels = units::unit<
    units::unit_conversion<std::ratio<1>, mia::dimension::Display_length>,
    Arithmetic>;
```

A _Pixel_ is
"the smallest addressable element
in an all points addressable display device"
([Wikipedia](https://en.wikipedia.org/wiki/Pixel))
"that contribute\[s] to the displayed or sensed color
when viewed at a distance"
([Wikipedia](https://en.wikipedia.org/wiki/Pixel#Subpixels)).
It is represented
by instantiations of the type aliased by `Pixels`
and equivalent instantiations.

### Suffix for `Pixels` literals \[units.display.literals]

```C++
constexpr Pixels<double> operator""_px(long double px) noexcept;
```
_Returns:_ `Pixels<double>{gsl::narrow_cast<double>(px)}`.

```C++
constexpr Pixels<int> operator""_px(unsigned long long px) noexcept;
```
_Returns:_ `Pixels<int>{gsl::narrow_cast<int>(px)}`.
