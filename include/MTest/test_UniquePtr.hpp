#ifndef TEST_TINY_UNIQUE_PTR_HPP
#define TEST_TINY_UNIQUE_PTR_HPP

#include "../UniquePtr.hpp"
#include <iostream>

namespace Tiny {
namespace TestUniquePtr {
struct TestUniquePtr {
  TestUniquePtr() { std::cout << "TestClass constructor" << std::endl; }

  ~TestUniquePtr() { std::cout << "TestClass destructor" << std::endl; }
};

inline void test_UniquePtr() {
  Tiny::UniquePtr ptr(new int(5));
  std::cout << "Value: " << *ptr << std::endl;
  std::cout << "Pointer: " << ptr.get() << std::endl;

  ptr.reset(new int(10));
  std::cout << "Value: " << *ptr << std::endl;
  std::cout << "Pointer: " << ptr.get() << std::endl;

  Tiny::UniquePtr ptr2(std::move(ptr));
  std::cout << "Value: " << *ptr2 << std::endl;
  std::cout << "Pointer: " << ptr2.get() << std::endl;

  Tiny::UniquePtr ptr3(ptr2.release());
  std::cout << "Value: " << *ptr3 << std::endl;
  std::cout << "Pointer: " << ptr3.get() << std::endl;

  Tiny::UniquePtr ptr4(new TestUniquePtr);
  Tiny::UniquePtr ptr5(ptr4.release());
}
} // namespace TestUniquePtr
} // namespace Tiny

#endif // TEST_TINY_UNIQUE_PTR_HPP