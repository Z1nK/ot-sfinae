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
    if (i > 0) std::cout << ".";
  }
  std::cout << std::endl;
}

template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
};

template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
};

template <typename T, typename = std::void_t<>>
struct is_container : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<decltype(std::declval<T>().begin()),
                                   decltype(std::declval<T>().end())>>
    : std::true_type {};

template <typename T, std::enable_if_t<is_container<T>::value &&
                                           !std::is_same_v<T, std::string>,
                                       int> = 0>
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
