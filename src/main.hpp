#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>

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

template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
void print_ip(const T &value) {
  std::cout << value << std::endl;
};
