#pragma once
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

/**
 * @brief Print an integral value as an IP-like dotted byte sequence.
 *
 * Bytes are printed from the most significant to the least significant.
 *
 * @tparam T Integral type.
 * @param value Value to print.
 */
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
void print_ip(const T &value) {
  const unsigned char *ptr = reinterpret_cast<const unsigned char *>(&value);
  for (int i = sizeof(T) - 1; i >= 0; --i) {
    std::cout << static_cast<int>(ptr[i]);
    if (i > 0)
      std::cout << ".";
  }
  std::cout << std::endl;
}

/**
 * @brief Print a floating-point value as-is.
 *
 * @tparam T Floating-point type.
 * @param value Value to print.
 */
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
};

// for containers

/**
 * @brief Type trait that detects whether a type can be streamed to std::ostream.
 *
 * @tparam T Type to check.
 */
template <typename T, typename = std::void_t<>>
struct is_streamable : std::false_type {};

/**
 * @brief Specialization for streamable types.
 *
 * @tparam T Type to check.
 */
template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream &>() << std::declval<T>())>>
    : std::true_type {};

/**
 * @brief Type trait that detects whether a type has begin()/end().
 *
 * @tparam T Type to check.
 */
template <typename T, typename = std::void_t<>>
struct is_container : std::false_type {};

/**
 * @brief Specialization for container-like types.
 *
 * @tparam T Type to check.
 */
template <typename T>
struct is_container<
    T,
    std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>>
    : std::true_type {};

// template <typename T, std::enable_if_t<is_container<T>::value &&
//                                            !std::is_same_v<T, std::string>,
//                                        int> = 0>
/**
 * @brief Print a non-streamable container as a dotted sequence.
 *
 * Elements are printed in iteration order and separated by dots.
 *
 * @tparam T Container type whose elements are streamable.
 * @param value Container to print.
 */
template <typename T, std::enable_if_t<is_container<T>::value && !is_streamable<T>::value, int> = 0>
void print_ip(const T &value) {
  auto it = value.begin();
  auto end = value.end();

  if (it != end) {
    std::cout << *it;
    ++it;
  }
  for (; it != end; ++it) {
    std::cout << "." << *it;
  }
  std::cout << std::endl;
}

// for string

// template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, int> =
// 0> void print_ip(const T &value) {
//   std::cout << value << std::endl;
// };

/**
 * @brief Print a character sequence as-is.
 *
 * This overload is intended for string-like types with char value_type.
 *
 * @tparam T String-like type.
 * @param value String value to print.
 */
template <typename T, std::enable_if_t<std::is_same_v<typename T::value_type, char>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
}

//  for Tuple

/**
 * @brief Compile-time check that all types in a parameter pack are the same.
 *
 * @tparam First First type in the pack.
 * @tparam Args Remaining types.
 */
template <typename First, typename... Args>
inline constexpr bool is_all_same_v = (std::is_same_v<First, Args> && ...);

/**
 * @brief Type trait that detects std::tuple types.
 *
 * @tparam T Type to check.
 */
template <typename T>
struct is_tuple : std::false_type {};

/**
 * @brief Specialization for std::tuple.
 *
 * @tparam Args Tuple element types.
 */
template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

/**
 * @brief Convenience variable template for is_tuple.
 *
 * @tparam T Type to check.
 */
template <typename T>
inline constexpr bool is_tuple_v = is_tuple<T>::value;

/**
 * @brief Print a tuple as a dotted sequence.
 *
 * All tuple elements must be of the same type.
 *
 * @tparam T Tuple type.
 * @param value Tuple to print.
 */
template <typename T, std::enable_if_t<is_tuple_v<T>, int> = 0>
void print_ip(const T &value) {
  std::apply(
      [](const auto &first, const auto &...args) {
        static_assert(is_all_same_v<decltype(first), decltype(args)...>,
                      "All tuple elements must be of the same type");
        std::cout << first;
        ((std::cout << "." << args), ...);
      },
      value);
  std::cout << std::endl;
}