# Extensions headers \[ext]

## General \[ext.general]

This clause describes headers
that adapt a library's interface to another's.
These headers are summarized in Table \[ext].

Table \[ext] -- Extensions headers summary

|               | Subclause                | Header(s)                   |
| ------------- | ------------------------ | --------------------------- |
| \[ext.chrono] | `std::chrono` extensions | `<jegp/ext/std/chrono.hpp>` |
| \[ext.units]  | `units` extensions       | `<jegp/ext/units.hpp>`      |

## `std::chrono` extensions \[ext.chrono]

This subclause describes specializations of `ranges::common_type`
that are adapted from those of `std::common_type` in `std::chrono`.

### Header `<jegp/ext/std/chrono.hpp>` synopsis \[ext.chrono.syn]

```C++
#include <chrono>

namespace ranges {

// \[ext.chrono.specializations], specializations of `ranges::common_type`
template <class Rep1, class Period1, class Rep2, class Period2>
struct common_type<
    std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>;

template <class Clock, class Duration1, class Duration2>
struct common_type<
    std::chrono::time_point<Clock, Duration1>,
    std::chrono::time_point<Clock, Duration2>>;

} // namespace ranges
```

### Specializations of `ranges::common_type` \[ext.chrono.specializations]

```C++
namespace ranges {

template <class Rep1, class Period1, class Rep2, class Period2>
struct common_type<
    std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>
  : std::common_type<
        std::chrono::duration<Rep1, Period1>,
        std::chrono::duration<Rep2, Period2>> {
};

template <class Clock, class Duration1, class Duration2>
struct common_type<
    std::chrono::time_point<Clock, Duration1>,
    std::chrono::time_point<Clock, Duration2>>
  : std::common_type<
        std::chrono::time_point<Clock, Duration1>,
        std::chrono::time_point<Clock, Duration2>> {
};

} // namespace ranges
```

## `units` extensions \[ext.units]

This subclause describes a specialization of `ranges::common_type`
that is adapted from those of `std::common_type` in `units`.

### Header `<jegp/ext/units.hpp>` synopsis \[ext.units.syn]

```C++
#include <units.h>

namespace ranges {

// \[ext.units.specialization], specialization of `ranges::common_type`
template <
    class UnitType1, class T1, template <class> class NonLinearScale1,
    class UnitType2, class T2, template <class> class NonLinearScale2>
struct common_type<
    units::unit<UnitType1, T1, NonLinearScale1>,
    units::unit<UnitType2, T2, NonLinearScale2>>;

} // namespace ranges
```

### Specialization of `ranges::common_type` \[ext.units.specialization]

```C++
namespace ranges {

template <
    class UnitType1, class T1, template <class> class NonLinearScale1,
    class UnitType2, class T2, template <class> class NonLinearScale2>
struct common_type<
    units::unit<UnitType1, T1, NonLinearScale1>,
    units::unit<UnitType2, T2, NonLinearScale2>>
  : std::common_type<
        units::unit<UnitType1, T1, NonLinearScale1>,
        units::unit<UnitType2, T2, NonLinearScale2>> {
};

} // namespace ranges
```
