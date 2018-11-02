# Extensions headers \[ext]

## General \[ext.general]

This clause describes headers
that adapt a library's interface to another's.
These headers are summarized in Table \[ext].

Table \[ext] -- Extensions headers summary

|               | Subclause                | Header(s)                   |
| ------------- | ------------------------ | --------------------------- |
| \[ext.chrono] | `std::chrono` extensions | `<jegp/ext/std/chrono.hpp>` |

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
