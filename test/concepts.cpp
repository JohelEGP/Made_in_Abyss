#include <ratio>
#include <units.h>
#include <mia/concepts.hpp>
#include <mia/ext/std/chrono.hpp>

namespace {

using R22 = std::ratio<2, 2>;
using std::chrono::duration;

} // namespace

// clang-format off

static_assert(mia::WeakQuantity<signed char>());
static_assert(mia::WeakQuantity<int>());
static_assert(mia::WeakQuantity<long long>());

static_assert(mia::WeakQuantity<unsigned char>());
static_assert(mia::WeakQuantity<unsigned>());
static_assert(mia::WeakQuantity<unsigned long long>());

static_assert(mia::WeakQuantity<float>());
static_assert(mia::WeakQuantity<double>());
static_assert(mia::WeakQuantity<long double>());

static_assert(mia::WeakQuantity<duration<signed char>>());
static_assert(mia::WeakQuantity<duration<int>>());
static_assert(mia::WeakQuantity<duration<long long>>());

static_assert(mia::WeakQuantity<duration<unsigned char>>());
static_assert(mia::WeakQuantity<duration<unsigned>>());
static_assert(mia::WeakQuantity<duration<unsigned long long>>());

static_assert(mia::WeakQuantity<duration<float>>());
static_assert(mia::WeakQuantity<duration<double>>());
static_assert(mia::WeakQuantity<duration<long double>>());

static_assert(mia::WeakQuantity<duration<signed char, R22>>());
static_assert(mia::WeakQuantity<duration<int, R22>>());
static_assert(mia::WeakQuantity<duration<long long, R22>>());

static_assert(mia::WeakQuantity<duration<unsigned char, R22>>());
static_assert(mia::WeakQuantity<duration<unsigned, R22>>());
static_assert(mia::WeakQuantity<duration<unsigned long long, R22>>());

static_assert(mia::WeakQuantity<duration<float, R22>>());
static_assert(mia::WeakQuantity<duration<double, R22>>());
static_assert(mia::WeakQuantity<duration<long double, R22>>());

static_assert(mia::WeakQuantity<units::dimensionless<int>>());

static_assert(mia::WeakQuantity<units::millimeter_t<int>>());
static_assert(mia::WeakQuantity<units::meter_t<int>>());
static_assert(mia::WeakQuantity<units::kilometer_t<int>>());

static_assert(mia::WeakQuantityWith<signed char, signed char>());
static_assert(mia::WeakQuantityWith<signed char, int>());
static_assert(mia::WeakQuantityWith<int, int>());
static_assert(mia::WeakQuantityWith<int, long long>());
static_assert(mia::WeakQuantityWith<long long, long long>());
static_assert(mia::WeakQuantityWith<signed char, long long>());

static_assert(mia::WeakQuantityWith<unsigned char, unsigned char>());
static_assert(mia::WeakQuantityWith<unsigned char, unsigned>());
static_assert(mia::WeakQuantityWith<unsigned, unsigned>());
static_assert(mia::WeakQuantityWith<unsigned, unsigned long long>());
static_assert(mia::WeakQuantityWith<unsigned long long, unsigned long long>());
static_assert(mia::WeakQuantityWith<unsigned char, unsigned long long>());

static_assert(mia::WeakQuantityWith<float, float>());
static_assert(mia::WeakQuantityWith<float, double>());
static_assert(mia::WeakQuantityWith<double, double>());
static_assert(mia::WeakQuantityWith<double, long double>());
static_assert(mia::WeakQuantityWith<long double, long double>());
static_assert(mia::WeakQuantityWith<float, long double>());

static_assert(mia::WeakQuantityWith<signed char, unsigned char>());
static_assert(mia::WeakQuantityWith<signed char, unsigned>());
static_assert(mia::WeakQuantityWith<int, unsigned>());
static_assert(mia::WeakQuantityWith<int, unsigned long long>());
static_assert(mia::WeakQuantityWith<long long, unsigned long long>());
static_assert(mia::WeakQuantityWith<signed char, unsigned long long>());

static_assert(mia::WeakQuantityWith<unsigned char, signed char>());
static_assert(mia::WeakQuantityWith<unsigned char, int>());
static_assert(mia::WeakQuantityWith<unsigned, int>());
static_assert(mia::WeakQuantityWith<unsigned, long long>());
static_assert(mia::WeakQuantityWith<unsigned long long, long long>());
static_assert(mia::WeakQuantityWith<unsigned char, long long>());

static_assert(mia::WeakQuantityWith<signed char, float>());
static_assert(mia::WeakQuantityWith<signed char, double>());
static_assert(mia::WeakQuantityWith<int, double>());
static_assert(mia::WeakQuantityWith<int, long double>());
static_assert(mia::WeakQuantityWith<long long, long double>());
static_assert(mia::WeakQuantityWith<signed char, long double>());

static_assert(mia::WeakQuantityWith<unsigned char, float>());
static_assert(mia::WeakQuantityWith<unsigned char, double>());
static_assert(mia::WeakQuantityWith<unsigned, double>());
static_assert(mia::WeakQuantityWith<unsigned, long double>());
static_assert(mia::WeakQuantityWith<unsigned long long, long double>());
static_assert(mia::WeakQuantityWith<unsigned char, long double>());

static_assert(mia::WeakQuantityWith<duration<signed char>, duration<signed char>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<long long>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<long long>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<unsigned char>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<unsigned long long>>());

static_assert(mia::WeakQuantityWith<duration<float>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<float>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<double>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<double>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<long double>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<float>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<signed char>, duration<unsigned char>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<long long>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<unsigned long long>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<signed char>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<long long>>());

static_assert(mia::WeakQuantityWith<duration<signed char>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<int>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<long long>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<signed char>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<signed char>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<long long>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned char>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned long long>>());

static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<double, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<double, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<long double, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned char>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<unsigned>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<unsigned long long>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned long long>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<signed char>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<int>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<long long>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<long long>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<float>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<long double>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<long double>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<signed char, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<int, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<int, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<long long, R22>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned char, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<unsigned, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<unsigned long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<unsigned long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<unsigned long long, R22>>());

static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<float, R22>>());
static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<double, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<double, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<long double, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<float, R22>, duration<long double, R22>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned char, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<unsigned, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<unsigned long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<unsigned long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<unsigned long long, R22>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<signed char, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<int, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<int, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<long long, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<long long, R22>>());

static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<float, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<int, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<long long, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<signed char, R22>, duration<long double, R22>>());

static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<float, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<double, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned long long, R22>, duration<long double, R22>>());
static_assert(mia::WeakQuantityWith<duration<unsigned char, R22>, duration<long double, R22>>());

static_assert(mia::WeakQuantityWith<units::dimensionless<int>, units::dimensionless<int>>());

static_assert(mia::WeakQuantityWith<units::millimeter_t<int>, units::millimeter_t<int>>());
static_assert(mia::WeakQuantityWith<units::millimeter_t<int>, units::meter_t<int>>());
static_assert(mia::WeakQuantityWith<units::meter_t<int>, units::meter_t<int>>());
static_assert(mia::WeakQuantityWith<units::meter_t<int>, units::kilometer_t<int>>());
static_assert(mia::WeakQuantityWith<units::kilometer_t<int>, units::kilometer_t<int>>());
static_assert(mia::WeakQuantityWith<units::millimeter_t<int>, units::kilometer_t<int>>());

static_assert(mia::QuantityOneWith<signed char, signed char>());
static_assert(mia::QuantityOneWith<signed char, int>());
static_assert(mia::QuantityOneWith<signed char, long long>());
static_assert(mia::QuantityOneWith<int, signed char>());
static_assert(mia::QuantityOneWith<int, int>());
static_assert(mia::QuantityOneWith<int, long long>());
static_assert(mia::QuantityOneWith<long long, signed char>());
static_assert(mia::QuantityOneWith<long long, int>());
static_assert(mia::QuantityOneWith<long long, long long>());

static_assert(mia::QuantityOneWith<unsigned char, unsigned char>());
static_assert(mia::QuantityOneWith<unsigned char, unsigned>());
static_assert(mia::QuantityOneWith<unsigned char, unsigned long long>());
static_assert(mia::QuantityOneWith<unsigned, unsigned char>());
static_assert(mia::QuantityOneWith<unsigned, unsigned>());
static_assert(mia::QuantityOneWith<unsigned, unsigned long long>());
static_assert(mia::QuantityOneWith<unsigned long long, unsigned char>());
static_assert(mia::QuantityOneWith<unsigned long long, unsigned>());
static_assert(mia::QuantityOneWith<unsigned long long, unsigned long long>());

static_assert(mia::QuantityOneWith<float, float>());
static_assert(mia::QuantityOneWith<float, double>());
static_assert(mia::QuantityOneWith<float, long double>());
static_assert(mia::QuantityOneWith<double, float>());
static_assert(mia::QuantityOneWith<double, double>());
static_assert(mia::QuantityOneWith<double, long double>());
static_assert(mia::QuantityOneWith<long double, float>());
static_assert(mia::QuantityOneWith<long double, double>());
static_assert(mia::QuantityOneWith<long double, long double>());

static_assert(mia::QuantityOneWith<signed char, unsigned char>());
static_assert(mia::QuantityOneWith<signed char, unsigned>());
static_assert(mia::QuantityOneWith<signed char, unsigned long long>());
static_assert(mia::QuantityOneWith<int, unsigned char>());
static_assert(mia::QuantityOneWith<int, unsigned>());
static_assert(mia::QuantityOneWith<int, unsigned long long>());
static_assert(mia::QuantityOneWith<signed long long, unsigned char>());
static_assert(mia::QuantityOneWith<signed long long, unsigned>());
static_assert(mia::QuantityOneWith<signed long long, unsigned long long>());

static_assert(mia::QuantityOneWith<unsigned char, signed char>());
static_assert(mia::QuantityOneWith<unsigned char, int>());
static_assert(mia::QuantityOneWith<unsigned char, signed long long>());
static_assert(mia::QuantityOneWith<unsigned, signed char>());
static_assert(mia::QuantityOneWith<unsigned, int>());
static_assert(mia::QuantityOneWith<unsigned, signed long long>());
static_assert(mia::QuantityOneWith<unsigned long long, signed char>());
static_assert(mia::QuantityOneWith<unsigned long long, int>());
static_assert(mia::QuantityOneWith<unsigned long long, signed long long>());

static_assert(mia::QuantityOneWith<signed char, float>());
static_assert(mia::QuantityOneWith<signed char, double>());
static_assert(mia::QuantityOneWith<signed char, long double>());
static_assert(mia::QuantityOneWith<int, float>());
static_assert(mia::QuantityOneWith<int, double>());
static_assert(mia::QuantityOneWith<int, long double>());
static_assert(mia::QuantityOneWith<signed long long, float>());
static_assert(mia::QuantityOneWith<signed long long, double>());
static_assert(mia::QuantityOneWith<signed long long, long double>());

static_assert(mia::QuantityOneWith<float, signed char>());
static_assert(mia::QuantityOneWith<float, int>());
static_assert(mia::QuantityOneWith<float, signed long long>());
static_assert(mia::QuantityOneWith<double, signed char>());
static_assert(mia::QuantityOneWith<double, int>());
static_assert(mia::QuantityOneWith<double, signed long long>());
static_assert(mia::QuantityOneWith<long double, signed char>());
static_assert(mia::QuantityOneWith<long double, int>());
static_assert(mia::QuantityOneWith<long double, signed long long>());

static_assert(mia::QuantityOneWith<unsigned char, float>());
static_assert(mia::QuantityOneWith<unsigned char, double>());
static_assert(mia::QuantityOneWith<unsigned char, long double>());
static_assert(mia::QuantityOneWith<unsigned, float>());
static_assert(mia::QuantityOneWith<unsigned, double>());
static_assert(mia::QuantityOneWith<unsigned, long double>());
static_assert(mia::QuantityOneWith<unsigned long long, float>());
static_assert(mia::QuantityOneWith<unsigned long long, double>());
static_assert(mia::QuantityOneWith<unsigned long long, long double>());

static_assert(mia::QuantityOneWith<float, unsigned char>());
static_assert(mia::QuantityOneWith<float, unsigned>());
static_assert(mia::QuantityOneWith<float, unsigned long long>());
static_assert(mia::QuantityOneWith<double, unsigned char>());
static_assert(mia::QuantityOneWith<double, unsigned>());
static_assert(mia::QuantityOneWith<double, unsigned long long>());
static_assert(mia::QuantityOneWith<long double, unsigned char>());
static_assert(mia::QuantityOneWith<long double, unsigned>());
static_assert(mia::QuantityOneWith<long double, unsigned long long>());

static_assert(mia::QuantityOneWith<signed char, duration<signed char>>());
static_assert(mia::QuantityOneWith<signed char, duration<int>>());
static_assert(mia::QuantityOneWith<signed char, duration<long long>>());
static_assert(mia::QuantityOneWith<int, duration<signed char>>());
static_assert(mia::QuantityOneWith<int, duration<int>>());
static_assert(mia::QuantityOneWith<int, duration<long long>>());
static_assert(mia::QuantityOneWith<long long, duration<signed char>>());
static_assert(mia::QuantityOneWith<long long, duration<int>>());
static_assert(mia::QuantityOneWith<long long, duration<long long>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned long long>>());

static_assert(mia::QuantityOneWith<float, duration<float>>());
static_assert(mia::QuantityOneWith<float, duration<double>>());
static_assert(mia::QuantityOneWith<float, duration<long double>>());
static_assert(mia::QuantityOneWith<double, duration<float>>());
static_assert(mia::QuantityOneWith<double, duration<double>>());
static_assert(mia::QuantityOneWith<double, duration<long double>>());
static_assert(mia::QuantityOneWith<long double, duration<float>>());
static_assert(mia::QuantityOneWith<long double, duration<double>>());
static_assert(mia::QuantityOneWith<long double, duration<long double>>());

static_assert(mia::QuantityOneWith<signed char, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<signed char, duration<unsigned>>());
static_assert(mia::QuantityOneWith<signed char, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned long long>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<signed char>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<int>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<signed long long>>());
static_assert(mia::QuantityOneWith<unsigned, duration<signed char>>());
static_assert(mia::QuantityOneWith<unsigned, duration<int>>());
static_assert(mia::QuantityOneWith<unsigned, duration<signed long long>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<signed char>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<int>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<signed long long>>());

static_assert(mia::QuantityOneWith<signed char, duration<float>>());
static_assert(mia::QuantityOneWith<signed char, duration<double>>());
static_assert(mia::QuantityOneWith<signed char, duration<long double>>());
static_assert(mia::QuantityOneWith<int, duration<float>>());
static_assert(mia::QuantityOneWith<int, duration<double>>());
static_assert(mia::QuantityOneWith<int, duration<long double>>());
static_assert(mia::QuantityOneWith<signed long long, duration<float>>());
static_assert(mia::QuantityOneWith<signed long long, duration<double>>());
static_assert(mia::QuantityOneWith<signed long long, duration<long double>>());

static_assert(mia::QuantityOneWith<float, duration<signed char>>());
static_assert(mia::QuantityOneWith<float, duration<int>>());
static_assert(mia::QuantityOneWith<float, duration<signed long long>>());
static_assert(mia::QuantityOneWith<double, duration<signed char>>());
static_assert(mia::QuantityOneWith<double, duration<int>>());
static_assert(mia::QuantityOneWith<double, duration<signed long long>>());
static_assert(mia::QuantityOneWith<long double, duration<signed char>>());
static_assert(mia::QuantityOneWith<long double, duration<int>>());
static_assert(mia::QuantityOneWith<long double, duration<signed long long>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<float>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<double>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<long double>>());
static_assert(mia::QuantityOneWith<unsigned, duration<float>>());
static_assert(mia::QuantityOneWith<unsigned, duration<double>>());
static_assert(mia::QuantityOneWith<unsigned, duration<long double>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<float>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<double>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<long double>>());

static_assert(mia::QuantityOneWith<float, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<float, duration<unsigned>>());
static_assert(mia::QuantityOneWith<float, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned long long>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned char>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned long long>>());

static_assert(mia::QuantityOneWith<signed char, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<int, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<long long, R22>>());
static_assert(mia::QuantityOneWith<int, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<int, duration<int, R22>>());
static_assert(mia::QuantityOneWith<int, duration<long long, R22>>());
static_assert(mia::QuantityOneWith<long long, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<long long, duration<int, R22>>());
static_assert(mia::QuantityOneWith<long long, duration<long long, R22>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<unsigned long long, R22>>());

static_assert(mia::QuantityOneWith<float, duration<float, R22>>());
static_assert(mia::QuantityOneWith<float, duration<double, R22>>());
static_assert(mia::QuantityOneWith<float, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<double, duration<float, R22>>());
static_assert(mia::QuantityOneWith<double, duration<double, R22>>());
static_assert(mia::QuantityOneWith<double, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<float, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<double, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<long double, R22>>());

static_assert(mia::QuantityOneWith<signed char, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<int, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<unsigned long long, R22>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<int, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<signed long long, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<int, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<signed long long, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<int, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<signed long long, R22>>());

static_assert(mia::QuantityOneWith<signed char, duration<float, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<double, R22>>());
static_assert(mia::QuantityOneWith<signed char, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<int, duration<float, R22>>());
static_assert(mia::QuantityOneWith<int, duration<double, R22>>());
static_assert(mia::QuantityOneWith<int, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<float, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<double, R22>>());
static_assert(mia::QuantityOneWith<signed long long, duration<long double, R22>>());

static_assert(mia::QuantityOneWith<float, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<float, duration<int, R22>>());
static_assert(mia::QuantityOneWith<float, duration<signed long long, R22>>());
static_assert(mia::QuantityOneWith<double, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<double, duration<int, R22>>());
static_assert(mia::QuantityOneWith<double, duration<signed long long, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<signed char, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<int, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<signed long long, R22>>());

static_assert(mia::QuantityOneWith<unsigned char, duration<float, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<double, R22>>());
static_assert(mia::QuantityOneWith<unsigned char, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<float, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<double, R22>>());
static_assert(mia::QuantityOneWith<unsigned, duration<long double, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<float, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<double, R22>>());
static_assert(mia::QuantityOneWith<unsigned long long, duration<long double, R22>>());

static_assert(mia::QuantityOneWith<float, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<float, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<float, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<double, duration<unsigned long long, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned char, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned, R22>>());
static_assert(mia::QuantityOneWith<long double, duration<unsigned long long, R22>>());

static_assert(mia::QuantityOneWith<units::dimensionless<int>, units::dimensionless<int>>());
static_assert(mia::QuantityOneWith<units::dimensionless<int>, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<units::dimensionless<int>, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<units::dimensionless<int>, units::kilometer_t<int>>());

static_assert(mia::QuantityOneWith<signed char, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<signed char, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<signed char, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<int, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<int, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<int, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<long long, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<long long, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<long long, units::kilometer_t<int>>());

static_assert(mia::QuantityOneWith<unsigned char, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned char, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned char, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<unsigned, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<unsigned long long, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned long long, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<unsigned long long, units::kilometer_t<int>>());

static_assert(mia::QuantityOneWith<float, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<float, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<float, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<double, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<double, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<double, units::kilometer_t<int>>());
static_assert(mia::QuantityOneWith<long double, units::millimeter_t<int>>());
static_assert(mia::QuantityOneWith<long double, units::meter_t<int>>());
static_assert(mia::QuantityOneWith<long double, units::kilometer_t<int>>());

static_assert(mia::QuantityOne<signed char>());
static_assert(mia::QuantityOne<int>());
static_assert(mia::QuantityOne<long long>());

static_assert(mia::QuantityOne<unsigned char>());
static_assert(mia::QuantityOne<unsigned>());
static_assert(mia::QuantityOne<unsigned long long>());

static_assert(mia::QuantityOne<float>());
static_assert(mia::QuantityOne<double>());
static_assert(mia::QuantityOne<long double>());

static_assert(mia::QuantityOne<units::dimensionless<int>>());

// clang-format on

int main()
{
}
