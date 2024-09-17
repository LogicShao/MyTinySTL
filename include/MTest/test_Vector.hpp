#ifndef TEST_TINY_VECTOR_HPP
#define TEST_TINY_VECTOR_HPP

#include "../Vector.hpp"
#include <iostream>

namespace Tiny {
namespace TestVector {
void test_Vector() {
  Tiny::Vector<int> vec;

  std::cout << "Size: " << vec.size() << std::endl;
  std::cout << "Capacity: " << vec.capacity() << std::endl;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  std::cout << "Size: " << vec.size() << std::endl;
  std::cout << "Capacity: " << vec.capacity() << std::endl;

  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }

  vec.pop_back();

  std::cout << "Size: " << vec.size() << std::endl;
  std::cout << "Capacity: " << vec.capacity() << std::endl;

  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }

  Tiny::Vector<int> vec2 = std::move(vec);
  Tiny::Vector<int> vec3 = vec2;

  std::cout << "Size: " << vec2.size() << std::endl;
  std::cout << "Capacity: " << vec2.capacity() << std::endl;

  for (int i = 0; i < vec2.size(); i++) {
    std::cout << vec2[i] << std::endl;
  }

  std::cout << "Size: " << vec3.size() << std::endl;
  std::cout << "Capacity: " << vec3.capacity() << std::endl;

  for (int i = 0; i < vec3.size(); i++) {
    std::cout << vec3[i] << std::endl;
  }
}
} // namespace TestVector
} // namespace Tiny

#endif // TEST_TINY_VECTOR_HPP