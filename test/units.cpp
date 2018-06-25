#include <cassert>
#include <functional>
#include <range/v3/utility/concepts.hpp>
#include <fmt/ostream.h>
#include <mia/concepts.hpp>
#include <mia/units.hpp>

namespace {

constexpr void test_pixels()
{
    static_assert(ranges::Regular<mia::Pixels<int>>());
    static_assert(mia::WeakQuantity<mia::Pixels<double>>());
    static_assert(
        mia::WeakQuantityWith<mia::Pixels<int>, mia::Pixels<double>>());
    static_assert(mia::QuantityOneWith<double, mia::Pixels<int>>());

    using namespace mia::pixels_literals;

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
}

void runtime_test_pixels()
{
    using namespace mia::pixels_literals;
    assert((fmt::format("{}", +20_px)) == "20 px");
}

constexpr int test()
{
    test_pixels();
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
