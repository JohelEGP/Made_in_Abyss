#ifndef MIA_EXT_UNITS_HPP
#define MIA_EXT_UNITS_HPP

#include <type_traits>
#include <range/v3/utility/common_type.hpp>
#include <units.h>

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

#endif // MIA_EXT_UNITS_HPP
