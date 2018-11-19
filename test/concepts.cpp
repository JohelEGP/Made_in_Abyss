#include <ratio>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>
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
#if MIA_TEST_EXTENSIVELY
    constexpr boost::hana::basic_tuple<
        signed char, int, long long, unsigned char, unsigned,
        unsigned long long, float, double, long double>
        arithmetic_types;
#else
    constexpr boost::hana::basic_tuple<int, unsigned, double> arithmetic_types;
#endif

#if !MIA_TEST_EXTENSIVELY || MIA_TEST_STEP == 0
    static_assert_<mia::Quantity>(arithmetic_types);
    static_assert_<mia::QuantityWith>(arithmetic_types, arithmetic_types);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, arithmetic_types);
    static_assert_<mia::QuantityOne>(arithmetic_types);
#endif

#if MIA_TEST_EXTENSIVELY
    constexpr boost::hana::basic_tuple<
        std::milli, std::ratio<2, 2000>, std::ratio<1>, std::ratio<2, 2>,
        std::ratio<60>, std::ratio<120, 2>>
        periods;
#else
    constexpr boost::hana::basic_tuple<
        std::milli, std::ratio<1>, std::ratio<60>>
        periods;
#endif

    [[maybe_unused]] constexpr boost::hana::basic_tuple durations{[=] {
        constexpr auto make_durations = [=](auto period) {
            return boost::hana::transform(arithmetic_types, [](auto arith) {
                return std::chrono::duration<
                    decltype(arith), decltype(period)>{};
            });
        };

        return boost::hana::unpack(periods, [=](auto... periods) {
            return boost::hana::flatten(
                boost::hana::make_basic_tuple(make_durations(periods)...));
        });
    }()};

#if !MIA_TEST_EXTENSIVELY || MIA_TEST_STEP == 1
    static_assert_<mia::Quantity>(durations);
    static_assert_<mia::QuantityWith>(durations, durations);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, durations);
#endif

    [[maybe_unused]] constexpr boost::hana::basic_tuple time_units{[=] {
        constexpr auto make_units = [=](auto unit) {
            return boost::hana::transform(arithmetic_types, [](auto arith) {
                return units::traits::replace_underlying_t<
                    decltype(unit), decltype(arith)>{};
            });
        };

        constexpr auto time_unit = [](auto period) {
            return units::traits::strong_t<units::unit<units::conversion_factor<
                decltype(period), units::dimension::time>>>{};
        };

        return boost::hana::unpack(periods, [=](auto... periods) {
            return [=](auto... units) {
                return boost::hana::flatten(
                    boost::hana::make_basic_tuple(make_units(units)...));
            }(time_unit(periods)...);
        });
    }()};

#if !MIA_TEST_EXTENSIVELY || MIA_TEST_STEP == 2
    static_assert_<mia::Quantity>(time_units);
    static_assert_<mia::QuantityWith>(time_units, time_units);
    static_assert_<mia::QuantityOneWith>(arithmetic_types, time_units);
#endif

    [[maybe_unused]] constexpr boost::hana::basic_tuple dimensionless_units{
        boost::hana::transform(arithmetic_types, [](auto arith) {
            return units::dimensionless{arith};
        })};

#if !MIA_TEST_EXTENSIVELY || MIA_TEST_STEP == 3
    static_assert_<mia::Quantity>(dimensionless_units);
    static_assert_<mia::QuantityWith>(dimensionless_units, dimensionless_units);
    static_assert_<mia::QuantityOne>(dimensionless_units);
#endif

    return 0;
}

int main()
{
    constexpr int ret{test()};
    return ret;
}
