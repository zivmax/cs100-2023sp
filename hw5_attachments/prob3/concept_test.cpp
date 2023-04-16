#if __cplusplus <= 201703L
#error At least C++20 is required. Use a modern compiler (g++ >= 10, clang++ >= 13) and set -std=c++20.
#endif
#if !defined(__cpp_concepts)
#error concepts not supported.
#endif

#include <concepts>
#include <iostream>

#include "dynarray.hpp"

namespace detail {

template <typename T>
concept correct_dynarray_ctors
  = std::default_initializable<T>
    && std::constructible_from<T, std::size_t>
    && !std::convertible_to<std::size_t, T>
    && std::constructible_from<T, std::size_t, int>
    && std::constructible_from<T, const int *, const int *>;

template <typename T>
concept correct_dynarray_copys
  = std::copyable<T>
  && requires(T a, T b) {
    { a = b } -> std::same_as<T &>;
  };

template <typename T, typename U>
U first_arg_type(T (Dynarray::*)(U));

template <typename T, typename U>
U first_arg_type_const(T (Dynarray::*)(U) const);

template <typename T>
concept correct_dynarray_memfcn
  = requires(T a, const T b, std::size_t n) {
    { b.size() } -> std::same_as<std::size_t>;
    { &T::size } -> std::same_as<std::size_t (T::*)() const>;
    { b.empty() } -> std::same_as<bool>;
    { &T::empty } -> std::same_as<bool (T::*)() const>;
    { a.at(n) } -> std::same_as<int &>;
    { b.at(n) } -> std::same_as<const int &>;
  } && std::is_same_v<
    decltype(first_arg_type(&T::at)),
    std::size_t
  > && std::is_same_v<
    decltype(first_arg_type_const(&T::at)),
    std::size_t
  >;

} // namespace detail

template <typename T>
concept correct_dynarray
  = detail::correct_dynarray_ctors<T>
    && detail::correct_dynarray_copys<T>
    && detail::correct_dynarray_memfcn<T>;

static_assert(correct_dynarray<Dynarray>);

int main() {
  std::cout << "Compile-time check passed.\n";
  return 0;
}