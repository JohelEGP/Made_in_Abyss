#ifndef MIA_EXT_STD_CHRONO_HPP
#define MIA_EXT_STD_CHRONO_HPP

#include <chrono>
#include <type_traits>
#include <range/v3/utility/common_type.hpp>

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

#endif // MIA_EXT_STD_CHRONO_HPP
