#include <ratio>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>
#include <units/time.h>
#include <mia/concepts.hpp>
#include <mia/ext/std/chrono.hpp>

template <template <class...> class Concept, class... T>
constexpr void static_assert_f()
{
    static_assert(Concept<T...>{}); // O(1)
}

template <template <class...> class Concept, class... T, class... U>
constexpr void static_assert_f(boost::hana::basic_tuple<U...>)
{
    (..., static_assert_f<Concept, T..., U>()); // O(N)
}

template <template <class...> class Concept, class... T, class... U>
constexpr void static_assert_f(
    boost::hana::basic_tuple<T...>, boost::hana::basic_tuple<U...> u)
{
    (..., static_assert_f<Concept, T>(u)); // O(N*N)
}

template <template <class...> class Concept>
constexpr auto static_assert_ =
    [](auto... tuple) { static_assert_f<Concept>(tuple...); };

constexpr int test()
{
    constexpr boost::hana::basic_tuple<
        signed char, int, long long, unsigned char, unsigned,
        unsigned long long, float, double, long double>
        arithmetic_types;

    static_assert_<mia::WeakQuantity>(arithmetic_types);
    static_assert_<mia::WeakQuantityWith>(arithmetic_types, arithmetic_types);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, arithmetic_types);
    static_assert_<mia::QuantityOne>(arithmetic_types);

    constexpr boost::hana::basic_tuple durations{[=] {
        constexpr auto make_durations = [=](auto period) {
            return boost::hana::transform(arithmetic_types, [](auto arith) {
                return std::chrono::duration<
                    decltype(arith), decltype(period)>{};
            });
        };

        return [=](auto... periods) {
            return boost::hana::flatten(
                boost::hana::make_basic_tuple(make_durations(periods)...));
        }(std::milli{}, std::ratio<2, 2000>{}, std::ratio<1>{},
               std::ratio<2, 2>{}, std::chrono::minutes::period{},
               std::ratio<120, 2>{});
    }()};

    static_assert_<mia::WeakQuantity>(durations);
    static_assert_<mia::WeakQuantityWith>(durations, durations);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, durations);

    constexpr boost::hana::basic_tuple time_units{[=] {
        constexpr auto make_units = [=](auto unit) {
            return boost::hana::transform(arithmetic_types, [](auto arith) {
                return units::traits::replace_underlying_t<
                    decltype(unit), decltype(arith)>{};
            });
        };

        constexpr auto time_unit = [](auto period) {
            return units::unit<units::conversion_factor<
                decltype(period), units::dimension::time>>{};
        };

        return [=](auto... units) {
            return boost::hana::flatten(
                boost::hana::make_basic_tuple(make_units(units)...));
        }(units::millisecond_t{}, time_unit(std::ratio<2, 2000>{}),
               units::second_t{}, time_unit(std::ratio<2, 2>{}),
               units::minute_t{}, time_unit(std::ratio<120, 2>{}));
    }()};

    static_assert_<mia::WeakQuantity>(time_units);
    static_assert_<mia::WeakQuantityWith>(time_units, time_units);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, time_units);

    constexpr boost::hana::basic_tuple dimensionless_units{
        boost::hana::transform(arithmetic_types, [](auto arith) {
            return units::dimensionless{arith};
        })};

    static_assert_<mia::WeakQuantity>(dimensionless_units);
    static_assert_<mia::WeakQuantityWith>(
        dimensionless_units, dimensionless_units);
    static_assert_<mia::QuantityOne>(dimensionless_units);

    return 0;
}

int main()
{
    constexpr int ret{test()};
    return ret;
}
