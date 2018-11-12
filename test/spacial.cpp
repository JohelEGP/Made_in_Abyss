#include <cassert>
#include <type_traits>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/none_of.hpp>
#include <boost/hana/type.hpp>
#include <range/v3/utility/concepts.hpp>
#include <jegp/utility.hpp>
#include <mia/concepts.hpp>
#include <mia/spacial.hpp>

static_assert(jegp::underlying(mia::Axis::x) == 0);
static_assert(jegp::underlying(mia::Axis::y) == 1);
static_assert(jegp::underlying(mia::Axis::z) == 2);

static_assert(!std::is_constructible_v<mia::Abscissa<int>, mia::Ordinate<int>>);
static_assert(!mia::QuantityWith<mia::Abscissa<int>, mia::Ordinate<int>>{});

constexpr void test_point()
{
    static_assert(ranges::Regular<mia::Point2d<int>>{});

    static_assert(ranges::Common<mia::Point3d<int>, mia::Point3d<double>>{});
    static_assert(!ranges::Common<mia::Point2d<int>, mia::Point3d<double>>{});

    static_assert(ranges::Same<
                  mia::Point2d<int>, mia::Point<mia::Coordinates{2}, int>>{});
    static_assert(ranges::Same<
                  mia::Point3d<int>, mia::Point<mia::Coordinates{3}, int>>{});

    static_assert(mia::Point2d<int>::coordinates == mia::Coordinates{2});
    static_assert(mia::Point3d<int>::coordinates == mia::Coordinates{3});
    static_assert(ranges::Same<mia::Point2d<int>::quantity, int>{});
    static_assert(ranges::Same<mia::Point3d<double>::quantity, double>{});

    // Construction
    {
        const mia::Abscissa<int> x{0};
        const mia::Ordinate<int> y{0};
        const mia::Applicate<int> z{0};
        const mia::Coordinate<mia::Axis{3}, int> coord4d{0};

        const mia::Point pt1d{x};
        const mia::Point pt2d{x, y};
        const mia::Point pt3d{x, y, z};
        const mia::Point pt4d{x, y, z, coord4d};

        static_assert(
            ranges::Same<
                const mia::Point<mia::Coordinates{1}, int>, decltype(pt1d)>{});
        static_assert(ranges::Same<const mia::Point2d<int>, decltype(pt2d)>{});
        static_assert(ranges::Same<const mia::Point3d<int>, decltype(pt3d)>{});
        static_assert(
            ranges::Same<
                const mia::Point<mia::Coordinates{4}, int>, decltype(pt4d)>{});

        mia::Point<mia::Coordinates{1}, double>{x};
        mia::Point<mia::Coordinates{1}, double>{pt1d};
        mia::Point2d<double>{x, y};
        mia::Point2d<double>{pt2d};
        mia::Point3d<double>{x, y, z};
        mia::Point3d<double>{pt3d};
        mia::Point<mia::Coordinates{4}, double>{x, y, z, coord4d};
        mia::Point<mia::Coordinates{4}, double>{pt4d};

        constexpr auto is_constructible = [](auto point, auto... args) {
            return ranges::Constructible<decltype(point), decltype(args)...>{};
        };

        assert(!is_constructible(pt1d, y));
        assert(!is_constructible(pt1d, pt2d));
        assert(!is_constructible(pt2d, x));
        assert(!is_constructible(pt2d, y));
        assert(!is_constructible(pt2d, y, x));
        assert(!is_constructible(pt2d, pt1d));
        assert(!is_constructible(pt2d, pt1d, y));
        assert(!is_constructible(pt2d, pt3d));
        assert(!is_constructible(pt3d, x, y));
        assert(!is_constructible(pt3d, pt2d));
        assert(!is_constructible(pt3d, pt2d, z));
        assert(!is_constructible(pt3d, pt1d, y, z));
        assert(!is_constructible(pt3d, pt4d));
        assert(!is_constructible(pt4d, x, y, z));
        assert(!is_constructible(pt4d, pt3d));
        assert(!is_constructible(pt4d, pt3d, coord4d));
        assert(!is_constructible(pt4d, pt2d, z, coord4d));
        assert(!is_constructible(pt4d, pt1d, y, z, coord4d));

        constexpr auto is_ctad_constructible_with = boost::hana::is_valid(
            [](auto... coord) -> decltype(mia::Point{coord...}) {});

        static_assert(!is_ctad_constructible_with(
            mia::Abscissa<int>{}, mia::Ordinate<double>{}));
    }
    // Coordinate read access
    {
        constexpr auto same_and_equal = [](auto l, auto r) {
            return ranges::Same<decltype(l), decltype(r)>{} && l == r;
        };

        const mia::Point2d<int> pt2d;
        const auto [x0, y0]{pt2d};

        assert(same_and_equal(pt2d.x(), mia::Abscissa<int>{0}));
        assert(same_and_equal(pt2d.y(), mia::Ordinate<int>{0}));
        assert(same_and_equal(pt2d.x(), x0));
        assert(same_and_equal(pt2d.y(), y0));
        assert(same_and_equal(pt2d.x(), mia::get<0>(pt2d)));
        assert(same_and_equal(pt2d.y(), mia::get<1>(pt2d)));
        assert(same_and_equal(pt2d.x(), mia::get<mia::Axis::x>(pt2d)));
        assert(same_and_equal(pt2d.y(), mia::get<mia::Axis::y>(pt2d)));
        assert(same_and_equal(pt2d.x(), mia::get<mia::Abscissa<int>>(pt2d)));
        assert(same_and_equal(pt2d.y(), mia::get<mia::Ordinate<int>>(pt2d)));

        const mia::Point3d<int> pt3d;
        const auto [x1, y1, z0]{pt3d};

        assert(same_and_equal(pt2d.x(), pt3d.x()));
        assert(same_and_equal(pt2d.y(), pt3d.y()));
        assert(same_and_equal(pt3d.z(), mia::Applicate<int>{0}));
        assert(same_and_equal(pt2d.x(), x1));
        assert(same_and_equal(pt2d.y(), y1));
        assert(same_and_equal(pt3d.z(), z0));
        assert(same_and_equal(pt2d.x(), mia::get<0>(pt3d)));
        assert(same_and_equal(pt2d.y(), mia::get<1>(pt3d)));
        assert(same_and_equal(pt3d.z(), mia::get<2>(pt3d)));
        assert(same_and_equal(pt2d.x(), mia::get<mia::Axis::x>(pt3d)));
        assert(same_and_equal(pt2d.y(), mia::get<mia::Axis::y>(pt3d)));
        assert(same_and_equal(pt3d.z(), mia::get<mia::Axis::z>(pt3d)));
        assert(same_and_equal(pt2d.x(), mia::get<mia::Abscissa<int>>(pt3d)));
        assert(same_and_equal(pt2d.y(), mia::get<mia::Ordinate<int>>(pt3d)));
        assert(same_and_equal(pt3d.z(), mia::get<mia::Applicate<int>>(pt3d)));

        constexpr auto illformed_pt2d_reads{boost::hana::make_basic_tuple(
            [](auto pt) -> decltype(pt.z()) {},
            [](auto pt) -> decltype(mia::get<2>(pt)) {},
            [](auto pt) -> decltype(mia::get<mia::Axis::z>(pt)) {},
            [](auto pt) -> decltype(mia::get<mia::Ordinate<double>>(pt)) {},
            [](auto pt) -> decltype(mia::get<mia::Applicate<int>>(pt)) {})};

        assert(boost::hana::none_of(illformed_pt2d_reads, [=](auto read) {
            return boost::hana::is_valid(read, pt2d);
        }));
    }
#ifndef MIA_GCC_BUG_71504
    // Coordinate write access
    {
        mia::Point pt2d{mia::Abscissa<int>{2}, mia::Ordinate<int>{2}};
        auto& [x0, y0]{pt2d};

        assert(--pt2d.x() == mia::Abscissa<int>{1});
        assert(--pt2d.y() == mia::Ordinate<int>{1});
        assert(--x0 == mia::Abscissa<int>{0});
        assert(--y0 == mia::Ordinate<int>{0});

        mia::Point pt3d{mia::Abscissa<int>{2}, mia::Ordinate<int>{2},
                        mia::Applicate<int>{2}};
        auto& [x1, y1, z0]{pt3d};

        assert(--pt3d.x() == mia::Abscissa<int>{1});
        assert(--pt3d.y() == mia::Ordinate<int>{1});
        assert(--pt3d.z() == mia::Applicate<int>{1});
        assert(--x1 == mia::Abscissa<int>{0});
        assert(--y1 == mia::Ordinate<int>{0});
        assert(--z0 == mia::Applicate<int>{0});
    }
#endif // MIA_GCC_BUG_71504
    // Comparisons
    {
        assert(
            (mia::Point{mia::Abscissa<int>{0}, mia::Ordinate<int>{0}} ==
             mia::Point{mia::Abscissa<double>{0}, mia::Ordinate<double>{0}}));
        assert(
            (mia::Point{mia::Abscissa<int>{0}, mia::Ordinate<int>{0}} !=
             mia::Point{mia::Abscissa<double>{0}, mia::Ordinate<double>{1}}));
        assert(
            (mia::Point{mia::Abscissa<int>{0}, mia::Ordinate<int>{0}} !=
             mia::Point{mia::Abscissa<double>{1}, mia::Ordinate<double>{0}}));
        assert(
            (mia::Point{mia::Abscissa<int>{0}, mia::Ordinate<int>{0}} !=
             mia::Point{mia::Abscissa<double>{1}, mia::Ordinate<double>{1}}));

        static_assert(!ranges::EqualityComparable<
                      mia::Point2d<int>, mia::Point3d<int>>{});
    }
}

static_assert(!std::is_constructible_v<mia::Width<int>, mia::Height<int>>);
static_assert(!mia::QuantityWith<mia::Width<int>, mia::Height<int>>{});

constexpr void test_size()
{
    static_assert(ranges::Copyable<mia::Size2d<int>>{});
    static_assert(!ranges::SemiRegular<mia::Size2d<int>>{});

    static_assert(ranges::Common<mia::Size3d<int>, mia::Size3d<double>>{});
    static_assert(!ranges::Common<mia::Size2d<int>, mia::Size3d<double>>{});

    using namespace mia::dimensions_literals;

    static_assert(ranges::Same<mia::Size2d<int>, mia::Size<2_D, int>>{});
    static_assert(ranges::Same<mia::Size3d<int>, mia::Size<3_D, int>>{});

    static_assert(mia::Size2d<int>::dimensions == 2_D);
    static_assert(mia::Size3d<int>::dimensions == 3_D);
    static_assert(ranges::Same<mia::Size2d<int>::quantity, int>{});
    static_assert(ranges::Same<mia::Size3d<double>::quantity, double>{});

    // Construction
    {
        const mia::Width<int> w{1};
        const mia::Height<int> h{1};
        const mia::Depth<int> d{1};
        const mia::Dimension<mia::Axis{3}, int> dim4d{1};

        const mia::Size sz1d{w};
        const mia::Size sz2d{w, h};
        const mia::Size sz3d{w, h, d};
        const mia::Size sz4d{w, h, d, dim4d};

        static_assert(
            ranges::Same<const mia::Size<1_D, int>, decltype(sz1d)>{});
        static_assert(ranges::Same<const mia::Size2d<int>, decltype(sz2d)>{});
        static_assert(ranges::Same<const mia::Size3d<int>, decltype(sz3d)>{});
        static_assert(
            ranges::Same<const mia::Size<4_D, int>, decltype(sz4d)>{});

        mia::Size<1_D, double>{w};
        mia::Size<1_D, double>{sz1d};
        mia::Size2d<double>{w, h};
        mia::Size2d<double>{sz2d};
        mia::Size3d<double>{w, h, d};
        mia::Size3d<double>{sz3d};
        mia::Size<4_D, double>{w, h, d, dim4d};
        mia::Size<4_D, double>{sz4d};

        constexpr auto is_constructible = [](auto size, auto... args) {
            return ranges::Constructible<decltype(size), decltype(args)...>{};
        };

        assert(!is_constructible(sz1d, h));
        assert(!is_constructible(sz1d, sz2d));
        assert(!is_constructible(sz2d, w));
        assert(!is_constructible(sz2d, h));
        assert(!is_constructible(sz2d, h, w));
        assert(!is_constructible(sz2d, sz1d));
        assert(!is_constructible(sz2d, sz1d, h));
        assert(!is_constructible(sz2d, sz3d));
        assert(!is_constructible(sz3d, w, h));
        assert(!is_constructible(sz3d, sz2d));
        assert(!is_constructible(sz3d, sz2d, d));
        assert(!is_constructible(sz3d, sz1d, h, d));
        assert(!is_constructible(sz3d, sz4d));
        assert(!is_constructible(sz4d, w, h, d));
        assert(!is_constructible(sz4d, sz3d));
        assert(!is_constructible(sz4d, sz3d, dim4d));
        assert(!is_constructible(sz4d, sz2d, d, dim4d));
        assert(!is_constructible(sz4d, sz1d, h, d, dim4d));

        constexpr auto is_ctad_constructible_with = boost::hana::is_valid(
            [](auto... dim) -> decltype(mia::Size{dim...}) {});

        static_assert(!is_ctad_constructible_with(
            mia::Width<int>{}, mia::Height<double>{}));
    }
    // Dimension read access
    {
        constexpr auto same_and_equal = [](auto l, auto r) {
            return ranges::Same<decltype(l), decltype(r)>{} && l == r;
        };

        const mia::Size sz2d{mia::Width<int>{1}, mia::Height<int>{1}};
        const auto [w0, h0]{sz2d};

        assert(same_and_equal(sz2d.w(), mia::Width<int>{1}));
        assert(same_and_equal(sz2d.h(), mia::Height<int>{1}));
        assert(same_and_equal(sz2d.w(), w0));
        assert(same_and_equal(sz2d.h(), h0));
        assert(same_and_equal(sz2d.w(), mia::get<0>(sz2d)));
        assert(same_and_equal(sz2d.h(), mia::get<1>(sz2d)));
        assert(same_and_equal(sz2d.w(), mia::get<mia::Axis::x>(sz2d)));
        assert(same_and_equal(sz2d.h(), mia::get<mia::Axis::y>(sz2d)));
        assert(same_and_equal(sz2d.w(), mia::get<mia::Width<int>>(sz2d)));
        assert(same_and_equal(sz2d.h(), mia::get<mia::Height<int>>(sz2d)));

        const mia::Size3d<int> sz3d{w0, h0, mia::Depth<int>{1}};
        const auto [w1, h1, d0]{sz3d};

        assert(same_and_equal(sz2d.w(), sz3d.w()));
        assert(same_and_equal(sz2d.h(), sz3d.h()));
        assert(same_and_equal(sz3d.d(), mia::Depth<int>{1}));
        assert(same_and_equal(sz2d.w(), w1));
        assert(same_and_equal(sz2d.h(), h1));
        assert(same_and_equal(sz3d.d(), d0));
        assert(same_and_equal(sz2d.w(), mia::get<0>(sz3d)));
        assert(same_and_equal(sz2d.h(), mia::get<1>(sz3d)));
        assert(same_and_equal(sz3d.d(), mia::get<2>(sz3d)));
        assert(same_and_equal(sz2d.w(), mia::get<mia::Axis::x>(sz3d)));
        assert(same_and_equal(sz2d.h(), mia::get<mia::Axis::y>(sz3d)));
        assert(same_and_equal(sz3d.d(), mia::get<mia::Axis::z>(sz3d)));
        assert(same_and_equal(sz2d.w(), mia::get<mia::Width<int>>(sz3d)));
        assert(same_and_equal(sz2d.h(), mia::get<mia::Height<int>>(sz3d)));
        assert(same_and_equal(sz3d.d(), mia::get<mia::Depth<int>>(sz3d)));

        constexpr auto illformed_sz2d_reads{boost::hana::make_basic_tuple(
            [](auto sz) -> decltype(sz.z()) {},
            [](auto sz) -> decltype(mia::get<2>(sz)) {},
            [](auto sz) -> decltype(mia::get<mia::Axis::z>(sz)) {},
            [](auto sz) -> decltype(mia::get<mia::Height<double>>(sz)) {},
            [](auto sz) -> decltype(mia::get<mia::Applicate<int>>(sz)) {})};

        assert(boost::hana::none_of(illformed_sz2d_reads, [=](auto read) {
            return boost::hana::is_valid(read, sz2d);
        }));
    }
    // Dimension write access
    {
        mia::Size sz2d{mia::Width<int>{3}, mia::Height<int>{3}};

        sz2d.w(--sz2d.w());
        sz2d.h(--sz2d.h());
        assert(sz2d.w() == mia::Width<int>{2});
        assert(sz2d.h() == mia::Height<int>{2});

        sz2d.set(--sz2d.w());
        sz2d.set(--sz2d.h());
        assert(sz2d.w() == mia::Width<int>{1});
        assert(sz2d.h() == mia::Height<int>{1});

        mia::Size sz3d{mia::Width<int>{3}, mia::Height<int>{3},
                       mia::Depth<int>{3}};

        sz3d.w(--sz3d.w());
        sz3d.h(--sz3d.h());
        sz3d.d(--sz3d.d());
        assert(sz3d.w() == mia::Width<int>{2});
        assert(sz3d.h() == mia::Height<int>{2});
        assert(sz3d.d() == mia::Depth<int>{2});

        sz3d.set(--sz3d.w());
        sz3d.set(--sz3d.h());
        sz3d.set(--sz3d.d());
        assert(sz3d.w() == mia::Width<int>{1});
        assert(sz3d.h() == mia::Height<int>{1});
        assert(sz3d.d() == mia::Depth<int>{1});

        static_assert(!std::is_reference_v<decltype(sz3d.w())>);
        static_assert(!std::is_reference_v<decltype(sz3d.h())>);
        static_assert(!std::is_reference_v<decltype(sz3d.d())>);
        static_assert(!std::is_reference_v<decltype(mia::get<0>(sz2d))>);
        static_assert(
            !std::is_reference_v<decltype(mia::get<mia::Axis::x>(sz2d))>);
        static_assert(
            !std::is_reference_v<decltype(mia::get<mia::Width<int>>(sz2d))>);
    }
    // Comparisons
    {
        assert(
            (mia::Size{mia::Width<int>{1}, mia::Height<int>{1}} ==
             mia::Size{mia::Width<double>{1}, mia::Height<double>{1}}));
        assert(
            (mia::Size{mia::Width<int>{1}, mia::Height<int>{1}} !=
             mia::Size{mia::Width<double>{1}, mia::Height<double>{2}}));
        assert(
            (mia::Size{mia::Width<int>{1}, mia::Height<int>{1}} !=
             mia::Size{mia::Width<double>{2}, mia::Height<double>{1}}));
        assert(
            (mia::Size{mia::Width<int>{1}, mia::Height<int>{1}} !=
             mia::Size{mia::Width<double>{2}, mia::Height<double>{2}}));

        static_assert(
            !ranges::EqualityComparable<mia::Size2d<int>, mia::Size3d<int>>{});
    }
}

constexpr int test()
{
    test_point();
    test_size();

    return 0;
}

int main()
{
    constexpr int ret{test()};
    return ret;
}
