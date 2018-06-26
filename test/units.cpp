#include <cassert>
#include <functional>
#include <type_traits>
#include <range/v3/utility/common_type.hpp>
#include <range/v3/utility/concepts.hpp>
#include <fmt/ostream.h>
#include <mia/concepts.hpp>
#include <mia/ext/units.hpp>
#include <mia/units.hpp>

namespace {

// \[display.units]

constexpr void test_pixels()
{
    static_assert(std::is_trivial_v<mia::Pixels<int>>);
    static_assert(std::is_standard_layout_v<mia::Pixels<double>>);

    static_assert(ranges::Regular<mia::Pixels<int>>());
    static_assert(mia::WeakQuantity<mia::Pixels<double>>());
    static_assert(
        mia::WeakQuantityWith<mia::Pixels<int>, mia::Pixels<double>>());
    static_assert(mia::QuantityOneWith<double, mia::Pixels<int>>());

    using namespace mia::pixels_literals;

    // `mia::WeakQuantity` semantics.
    {
        int i{42};
        mia::Pixels<int> px{42_px};

        auto test_cmp = [=](auto op) {
            assert(op(0, i) == op(0_px, px));
            assert(op(i, i) == op(px, px));
            assert(op(i, 0) == op(px, 0_px));
        };

        test_cmp(std::less{});
        test_cmp(std::less_equal{});
        test_cmp(std::greater{});
        test_cmp(std::greater_equal{});

        assert(+i == (+px)());
        assert(-i == (-px)());
        assert(++i == (++px)());
        assert(--i == (--px)());
        assert(i++ == px++());
        assert(i-- == px--());
        assert(i + i == (px + px)());
        assert(i - i == (px - px)());
        assert(i * i == (px * i)());
        assert(i * i == (i * px)());
        assert(i / i == (px / i)());
        assert(i / i == px / px);
        assert(i % i == (px % i)());
        assert(i % i == (px % px)());
        assert((i += 42) == (px += 42_px)());
        assert((i -= 42) == (px -= 42_px)());
        assert((i *= 42) == (px *= 42)());
        assert((i /= 42) == (px /= 42)());
        assert((i %= 42) == (px %= 42)());
        assert((i %= 42) == (px %= 42_px)());

        assert(&px == &++px);
        assert(&px == &--px);
        assert(&px == &(px += 0_px));
        assert(&px == &(px -= 0_px));
        assert(&px == &(px *= 1));
        assert(&px == &(px /= 1));
        assert(&px == &(px %= 1));
        assert(&px == &(px %= 1_px));
    }
    // `mia::WeakQuantityWith` semantics.
    {
        mia::Pixels<short> s{42_px};
        mia::Pixels<int> i{s};
        s = i;
        i = s;

        auto test_cmp = [=](auto op) {
            assert(op(0, 42) == op(0_px, s));
            assert(op(42, 42) == op(s, i));
            assert(op(42, 0) == op(s, 0_px));
        };

        test_cmp(std::less{});
        test_cmp(std::less_equal{});
        test_cmp(std::greater{});
        test_cmp(std::greater_equal{});

        assert(42 + 42 == (s + i)());
        assert(42 + 42 == (i + s)());
        assert(42 - 42 == (s - i)());
        assert(42 - 42 == (i - s)());
        assert(42 / 42 == s / i);
        assert(42 / 42 == i / s);
    }
}

void runtime_test_pixels()
{
    using namespace mia::pixels_literals;
    assert((fmt::format("{}", +20_px)) == "20 px");
}

// \[unit.alias]

template <class Qty>
class Radius : public mia::Unit_alias<Radius<Qty>> {
public:
    using mia::Unit_alias<Radius<Qty>>::Unit_alias;
};

template <class Qty>
explicit Radius(const Qty&)->Radius<Qty>;

} // namespace

namespace ranges {

template <class Qty1, class Qty2>
struct common_type<Radius<Qty1>, Radius<Qty2>> {
    using type = Radius<common_type_t<Qty1, Qty2>>;
};

} // namespace ranges

namespace {

constexpr void test_radius()
{
    static_assert(std::is_trivial_v<Radius<mia::Pixels<int>>>);
    static_assert(std::is_standard_layout_v<Radius<mia::Pixels<double>>>);

    static_assert(ranges::Regular<Radius<mia::Pixels<int>>>());
    static_assert(mia::WeakQuantity<Radius<mia::Pixels<double>>>());
    static_assert(mia::WeakQuantityWith<
                  Radius<mia::Pixels<int>>, Radius<mia::Pixels<double>>>());
    static_assert(mia::QuantityOneWith<int, Radius<mia::Pixels<double>>>());
    static_assert(!mia::QuantityOne<Radius<mia::Pixels<double>>>());

    static_assert(ranges::Regular<Radius<int>>());
    static_assert(mia::WeakQuantity<Radius<double>>());
    static_assert(mia::WeakQuantityWith<Radius<int>, Radius<double>>());
    static_assert(mia::QuantityOneWith<double, Radius<int>>());
    static_assert(!mia::QuantityOne<Radius<int>>());

    using namespace mia::pixels_literals;

    static_assert(
        std::is_same_v<Radius<mia::Pixels<int>>, decltype(Radius{0_px})>);

    // `mia::WeakQuantity` semantics.
    {
        mia::Pixels<int> px{42};
        Radius r{42_px};

        auto test_cmp = [=](auto op) {
            assert(op(0_px, px) == op(Radius{0_px}, r));
            assert(op(px, px) == op(r, r));
            assert(op(px, 0_px) == op(r, Radius{0_px}));
        };

        test_cmp(std::less{});
        test_cmp(std::less_equal{});
        test_cmp(std::greater{});
        test_cmp(std::greater_equal{});

        assert(+px == (+r).unaliased());
        assert(-px == (-r).unaliased());
        assert(++px == (++r).unaliased());
        assert(--px == (--r).unaliased());
        assert(px++ == r++.unaliased());
        assert(px-- == r--.unaliased());
        assert(px + px == (r + r).unaliased());
        assert(px - px == (r - r).unaliased());
        assert(px * 42 == (r * 42).unaliased());
        assert(42 * px == (42 * r).unaliased());
        assert(px / 42 == (r / 42).unaliased());
        assert(px / px == r / r);
        assert(px % 42 == (r % 42).unaliased());
        assert(px % px == (r % r).unaliased());
        assert((px += 42_px) == (r += Radius{42_px}).unaliased());
        assert((px -= 42_px) == (r -= Radius{42_px}).unaliased());
        assert((px *= 42) == (r *= 42).unaliased());
        assert((px /= 42) == (r /= 42).unaliased());
        assert((px %= 42) == (r %= 42).unaliased());
        assert((px %= 42_px) == (r %= Radius{42_px}).unaliased());

        assert(&r == &++r);
        assert(&r == &--r);
        assert(&r == &(r += Radius{0_px}));
        assert(&r == &(r -= Radius{0_px}));
        assert(&r == &(r *= 1));
        assert(&r == &(r /= 1));
        assert(&r == &(r %= 1));
        assert(&r == &(r %= Radius{1_px}));
    }
    // `mia::WeakQuantityWith` semantics.
    {
        using namespace units::literals;

        Radius<units::length::millimeter_t> mm{42_m};
        Radius<units::length::meter_t> m{mm};
        mm = m;
        m  = mm;

        auto test_cmp = [=](auto op) {
            assert(op(0_m, 42_m) == op(Radius{0_m}, mm));
            assert(op(42_m, 42_m) == op(mm, m));
            assert(op(42_m, 0_m) == op(mm, Radius{0_m}));
        };

        test_cmp(std::less{});
        test_cmp(std::less_equal{});
        test_cmp(std::greater{});
        test_cmp(std::greater_equal{});

        assert(42_m + 42_m == (mm + m).unaliased());
        assert(42_m + 42_m == (m + mm).unaliased());
        assert(42_m - 42_m == (mm - m).unaliased());
        assert(42_m - 42_m == (m - mm).unaliased());
        assert(42_m / 42_m == mm / m);
        assert(42_m / 42_m == m / mm);
    }
}

constexpr auto test_unit_alias = test_radius;

constexpr int test()
{
    test_pixels();
    test_unit_alias();
    return 0;
}

void runtime_test()
{
    runtime_test_pixels();
}

} // namespace

int main()
{
    constexpr int ret{test()};
    runtime_test();
    return ret;
}
