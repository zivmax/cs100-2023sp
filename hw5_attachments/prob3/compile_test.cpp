#include <iostream>
#include <type_traits>
#include <utility>

#include "dynarray.hpp"

#if __cplusplus < 201703L
#error At least C++17 is required.
#endif

static_assert(std::is_default_constructible_v<Dynarray>,
              "`Dynarray` should be default constructible.");

static_assert(std::is_constructible_v<Dynarray, std::size_t>,
              "The constructor `Dynarray(n)` should be supported.");

static_assert(!std::is_convertible_v<std::size_t, Dynarray>,
              "The constructor `Dynarray(n)` should be explicit.");

static_assert(std::is_constructible_v<Dynarray, std::size_t, int>,
              "The constructor `Dynarray(n, x)` should be supported.");

static_assert(std::is_constructible_v<Dynarray, const int *, const int *>,
              "The constructor `Dynarray(begin, end)` should be supported.");

static_assert(std::is_copy_constructible_v<Dynarray>,
              "`Dynarray` should be copy constructible.");

static_assert(std::is_copy_assignable_v<Dynarray>,
              "`Dynarray` should be copy assignable.");

static_assert(
    std::is_same_v<Dynarray &, decltype(std::declval<Dynarray>() =
                                            std::declval<Dynarray>())>,
    "Why doesn't your copy-assignment operator return reference to the "
    "left-hand side object?");

namespace detail {

#define DEFINE_DETECTER(LABEL, OBJECT, MEMFCN, RET, ...)                       \
  template <typename T = OBJECT,                                               \
            typename U = decltype(std::declval<T>().MEMFCN(__VA_ARGS__)),      \
            typename = std::enable_if_t<std::is_same_v<U, RET>>>               \
  std::true_type detect_##LABEL(int);                                          \
  std::false_type detect_##LABEL(...);                                         \
  inline constexpr auto LABEL##_correct = decltype(detect_##LABEL(0))::value;

DEFINE_DETECTER(size, const Dynarray, size, std::size_t, )

DEFINE_DETECTER(empty, const Dynarray, empty, bool, )

DEFINE_DETECTER(at, Dynarray, at, int &, std::size_t{})

DEFINE_DETECTER(const_at, const Dynarray, at, const int &, std::size_t{})

#undef DEFINE_DETECTER

} // namespace detail

static_assert(detail::size_correct,
              "`Dynarray::size` not defined or incorrect.");

static_assert(detail::empty_correct,
              "`Dynarray::empty` not defined or incorrect.");

static_assert(detail::at_correct && detail::const_at_correct,
              "`Dynarray::at` not defined or incorrect.");

namespace detail {

#define SINGLE_DEF_DETECTER(MEMFUN)                                            \
  template <typename T = Dynarray, typename = decltype(&T::MEMFUN)>            \
  std::true_type test_##MEMFUN##_def(int);                                     \
  std::false_type test_##MEMFUN##_def(...);                                    \
  inline constexpr auto MEMFUN##_def_correct =                                 \
      decltype(test_##MEMFUN##_def(0))::value;

SINGLE_DEF_DETECTER(size)

SINGLE_DEF_DETECTER(empty)

#undef SINGLE_DEF_DETECTER

} // namespace detail

static_assert(
    detail::size_def_correct,
    "`Dynarray::size` should not have `const vs non-const` overloading.");

static_assert(
    detail::empty_def_correct,
    "`Dynarray::empty` should not have `const vs non-const` overloading.");

namespace detail {

template <typename T, typename U>
U get_param_type_nonconst(T (Dynarray::*)(U));

template <typename T, typename U>
U get_param_type_const(T (Dynarray::*)(U) const);

inline constexpr auto at_param_type_correct =
    std::is_same_v<decltype(get_param_type_nonconst(&Dynarray::at)),
                   std::size_t>;

inline constexpr auto const_at_param_type_correct =
    std::is_same_v<decltype(get_param_type_const(&Dynarray::at)), std::size_t>;

} // namespace detail

static_assert(
    detail::at_param_type_correct && detail::const_at_param_type_correct,
    "What might be a better choice for the parameter type of `Dynarray::at?`");

int main() {
  std::cout << "Compile-time check passed." << std::endl;
  return 0;
}