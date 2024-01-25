#pragma once

namespace templated_struct {

template <typename T>
struct extract {};

template <template <typename...> class U, typename... Args>
struct extract<U<Args...>> {
    template <template <typename...> class V>
    using rebind = V<Args...>;
};

template <template <typename...> class U, typename T>
struct builder {
    using type = typename extract<T>::template rebind<U>;
};

template <typename ...Args>
struct special_type {};

}