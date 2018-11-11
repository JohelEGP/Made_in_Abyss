# Concepts library \[concepts]

## General \[concepts.general]

This clause describes concepts.
These concepts are summarized in Table \[concepts].

Table \[concepts] -- Concepts library summary

|                    | Subclause       | Header(s)            |
| ------------------ | --------------- | -------------------- |
| \[concepts.object] | Object concepts | `<mia/concepts.hpp>` |

## Header `<mia/concepts.hpp>` synopsis \[concepts.syn]

```C++
namespace mia {

namespace concepts {

    template <class Concept, class... Ts, class... Prototype>
    auto model_of(Prototype&&...) -> meta::if_c<
        ranges::concepts::models<Concept, Prototype..., Ts...>::value, int>;

    // \[concepts.object], object concepts
    // \[concepts.object.qty], quantities
    struct QuantityOneWith;

    struct WeakQuantity;

    struct QuantityOne;

    struct WeakQuantityWith;

} // namespace concepts

// \[concepts.object], object concepts
// \[concepts.object.qty], quantities
template <class T, class U>
using QuantityOneWith =
    ranges::concepts::models<mia::concepts::QuantityOneWith, T, U>;

template <class T>
using WeakQuantity = ranges::concepts::models<mia::concepts::WeakQuantity, T>;

template <class T>
using QuantityOne = ranges::concepts::models<mia::concepts::QuantityOne, T>;

template <class T, class U>
using WeakQuantityWith =
    ranges::concepts::models<mia::concepts::WeakQuantityWith, T, U>;

} // namespace mia
```

## Object concepts \[concepts.object]

### Quantities \[concepts.object.qty]

This subclause describes concepts
to constrain types that should represent quantities.

```C++
namespace mia::concepts {

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

} // namespace mia::concepts
```
The `QuantityOneWith` concept
is satisfied by ordered pairs of types
where the first type behaves like a quantity of dimension one
with respect to the second type.

```C++
namespace mia::concepts {

struct WeakQuantity {
    template <class T>
    auto requires_(const T& c, T& l) -> decltype(ranges::concepts::valid_expr(
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

} // namespace mia::concepts
```
The `WeakQuantity` concept
is satisfied by types
that behave like quantities
with respect to operations
that result in the same unit.

```C++
namespace mia::concepts {

struct QuantityOne {
    template <class T>
    auto requires_() -> decltype(ranges::concepts::valid_expr(
        model_of<WeakQuantity, T>(), //
        model_of<QuantityOneWith, T, T>()));
};

} // namespace mia::concepts
```
The `QuantityOne` concept
is satisfied by types
that behave like quantities of dimension one.

```C++
namespace mia::concepts {

struct WeakQuantityWith {
    template <class T, class U, class C = ranges::common_reference_t<T, U>>
    auto requires_(const T& t, const U& u)
        -> decltype(ranges::concepts::valid_expr(
            model_of<WeakQuantity, T>(), //
            model_of<WeakQuantity, U>(),
            model_of<ranges::concepts::CommonReference, T, U>(),
            model_of<WeakQuantity, C>(),
            model_of<ranges::concepts::TotallyOrdered, T, U>(),
            model_of<ranges::concepts::ConvertibleTo, C>(t + u),
            model_of<ranges::concepts::ConvertibleTo, C>(u + t),
            model_of<ranges::concepts::ConvertibleTo, C>(t - u),
            model_of<ranges::concepts::ConvertibleTo, C>(u - t),
            model_of<QuantityOneWith, C>(t / u),
            model_of<QuantityOneWith, C>(u / t)));
};

} // namespace mia::concepts
```
Let `t` and `u` be lvalues
of types `const T` and `const U`,
respectively,
and `C` be `ranges::common_reference_t<T, U>`.
`WeakQuantityWith<T, U>` is satisfied only if:
- `t + u == C(t) + C(u)`.
- `u + t == C(u) + C(t)`.
- `t - u == C(t) - C(u)`.
- `u - t == C(u) - C(t)`.
- `t / u == C(t) / C(u)`.
- `u / t == C(u) / C(t)`.

The `WeakQuantityWith` concept
is satisfied by unordered pairs of types
that behave like quantities
with respect to operations
that result in the same dimension.
