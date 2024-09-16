#ifndef TEST_TINY_ARRAY_HPP
#define TEST_TINY_ARRAY_HPP

#include "../Array.hpp"
#include <iostream>

namespace Tiny {
namespace TEST {
template <typename T, std::size_t N>
void print_array(const Tiny::Array<T, N> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
}

void test_Array() {
  Tiny::Array<int, 5> arr;

  for (int i = 0; i < arr.size(); i++) {
    arr[i] = i + 1;
  }
  print_array(arr);

  Tiny::Array<int, 5> arr2 = arr;
  print_array(arr2);

  Tiny::Array<int, 5> arr3 = std::move(arr2);
  print_array(arr3);

  Tiny::Array<int, 5> arr4;
  arr4 = arr3;
  print_array(arr4);
}
} // namespace TEST
} // namespace Tiny

#endif // TEST_TINY_ARRAY_HPP