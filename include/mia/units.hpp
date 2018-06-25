#ifndef MIA_UNITS_HPP
#define MIA_UNITS_HPP

#include <ratio>
#include <gsl/gsl_util>
#include <gsl/string_span>
#include <mia/ext/units.hpp>

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
        units::unit_conversion<std::ratio<1>, dimension::Display_length>,
        Arithmetic>;

} // namespace display_length

inline namespace literals {
    inline namespace pixels_literals { //

        constexpr Pixels<double> operator""_px(long double px) noexcept
        {
            return Pixels<double>{gsl::narrow_cast<double>(px)};
        }

        constexpr Pixels<int> operator""_px(unsigned long long px) noexcept
        {
            return Pixels<int>{gsl::narrow_cast<int>(px)};
        }

    } // namespace pixels_literals
} // namespace literals

} // namespace mia

#endif // MIA_UNITS_HPP
