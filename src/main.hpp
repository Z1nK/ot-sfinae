#pragma once
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

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

template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
};

// for containers

template <typename T, typename = std::void_t<>>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream &>() << std::declval<T>())>>
    : std::true_type {};

template <typename T, typename = std::void_t<>>
struct is_container : std::false_type {};

template <typename T>
struct is_container<
    T,
    std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>>
    : std::true_type {};

// template <typename T, std::enable_if_t<is_container<T>::value &&
//                                            !std::is_same_v<T, std::string>,
//                                        int> = 0>
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

template <typename T, std::enable_if_t<std::is_same_v<typename T::value_type, char>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
}

//  for Tuple

template <typename T>
struct is_tuple : std::false_type {};
template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};
template <typename T>
inline constexpr bool is_tuple_v = is_tuple<T>::value;

template <typename T, std::enable_if_t<is_tuple_v<T>, int> = 0>
void print_ip(const T &value) {
  std::apply(
      [](const auto &first, const auto &...args) {
        std::cout << first;
        ((std::cout << "." << args), ...);
      },
      value);
  std::cout << std::endl;
}