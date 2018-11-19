#ifndef MIA_CONCEPTS_HPP
#define MIA_CONCEPTS_HPP

#include <range/v3/utility/common_type.hpp>
#include <range/v3/utility/concepts.hpp>
#include <meta/meta.hpp>

namespace mia {

namespace concepts {

    template <class Concept, class... Ts, class... Prototype>
    auto model_of(Prototype&&...) -> meta::if_c<
        ranges::concepts::models<Concept, Prototype..., Ts...>::value, int>;

    struct QuantityOneWith {
        template <class T, class U>
        auto requires_(const T& o, const U& c, U& l)
            -> decltype(ranges::concepts::valid_expr(
                model_of<ranges::concepts::ConvertibleTo, U, decltype(c * o)>(),
                model_of<ranges::concepts::ConvertibleTo, U, decltype(o * c)>(),
                model_of<ranges::concepts::ConvertibleTo, U, decltype(c / o)>(),
                model_of<ranges::concepts::ConvertibleTo, T>(c / c),
                model_of<ranges::concepts::Same, U&>(l *= o),
                model_of<ranges::concepts::Same, U&>(l /= o)));
    };

    struct Quantity {
        template <class T>
        auto requires_(const T& c, T& l)
            -> decltype(ranges::concepts::valid_expr(
                model_of<ranges::concepts::Regular, T>(),
                model_of<ranges::concepts::TotallyOrdered, T>(),
                model_of<ranges::concepts::ConvertibleTo, T>(+c),
                model_of<ranges::concepts::ConvertibleTo, T>(-c),
                model_of<ranges::concepts::Same, T&>(++l),
                model_of<ranges::concepts::Same, T&>(--l),
                model_of<ranges::concepts::Same, T>(l++),
                model_of<ranges::concepts::Same, T>(l--),
                model_of<ranges::concepts::ConvertibleTo, T>(c + c),
                model_of<ranges::concepts::ConvertibleTo, T>(c - c),
                model_of<ranges::concepts::Same, T&>(l += c),
                model_of<ranges::concepts::Same, T&>(l -= c),
                model_of<QuantityOneWith, T>(c / c)));
    };

    struct QuantityOne {
        template <class T>
        auto requires_() -> decltype(ranges::concepts::valid_expr(
            model_of<Quantity, T>(), //
            model_of<QuantityOneWith, T, T>()));
    };

    struct QuantityWith {
        template <class T, class U, class C = ranges::common_reference_t<T, U>>
        auto requires_(const T& t, const U& u)
            -> decltype(ranges::concepts::valid_expr(
                model_of<Quantity, T>(), //
                model_of<Quantity, U>(),
                model_of<ranges::concepts::CommonReference, T, U>(),
                model_of<Quantity, C>(),
                model_of<ranges::concepts::TotallyOrdered, T, U>(),
                model_of<ranges::concepts::ConvertibleTo, C>(t + u),
                model_of<ranges::concepts::ConvertibleTo, C>(u + t),
                model_of<ranges::concepts::ConvertibleTo, C>(t - u),
                model_of<ranges::concepts::ConvertibleTo, C>(u - t),
                model_of<QuantityOneWith, C>(t / u),
                model_of<QuantityOneWith, C>(u / t)));
    };

} // namespace concepts

template <class T, class U>
using QuantityOneWith =
    ranges::concepts::models<concepts::QuantityOneWith, T, U>;

template <class T>
using Quantity = ranges::concepts::models<concepts::Quantity, T>;

template <class T>
using QuantityOne = ranges::concepts::models<concepts::QuantityOne, T>;

template <class T, class U>
using QuantityWith = ranges::concepts::models<concepts::QuantityWith, T, U>;

} // namespace mia

#endif // MIA_CONCEPTS_HPP
