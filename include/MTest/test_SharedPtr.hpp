#ifndef TEST_TINY_SHARED_PTR_HPP
#define TEST_TINY_SHARED_PTR_HPP

#include "../SharedPtr.hpp"
#include <iostream>

namespace Tiny {
namespace TestSharedPtr {
struct SharedPtrTest {
  SharedPtrTest() { std::cout << "TestClass constructor" << std::endl; }

  SharedPtrTest(const SharedPtrTest &other) {
    std::cout << "TestClass copy constructor" << std::endl;
  }

  SharedPtrTest(SharedPtrTest &&other) {
    std::cout << "TestClass move constructor" << std::endl;
  }

  ~SharedPtrTest() { std::cout << "TestClass destructor" << std::endl; }
};

void test_SharedPtr_1() {
  Tiny::SharedPtr ptr(new int(5));
  std::cout << "Value: " << *ptr << std::endl;
  std::cout << "Pointer: " << ptr.get() << std::endl;

  Tiny::SharedPtr ptr2(ptr);
  std::cout << "Value: " << *ptr2 << std::endl;
  std::cout << "Pointer: " << ptr2.get() << std::endl;

  Tiny::SharedPtr ptr3(std::move(ptr2));
  std::cout << "Value: " << *ptr3 << std::endl;
  std::cout << "Pointer: " << ptr3.get() << std::endl;

  Tiny::SharedPtr ptr4(new int(10));
  ptr4 = ptr3;
  std::cout << "Value: " << *ptr4 << std::endl;
  std::cout << "Pointer: " << ptr4.get() << std::endl;

  Tiny::SharedPtr ptr5(new int(15));
  ptr5 = std::move(ptr4);
  std::cout << "Value: " << *ptr5 << std::endl;
  std::cout << "Pointer: " << ptr5.get() << std::endl;
}

void test_SharedPtr_2() {
  Tiny::SharedPtr ptr(new SharedPtrTest);
  std::cout << "ptr(new TestClass)" << std::endl;

  Tiny::SharedPtr ptr2(ptr);
  std::cout << "ptr2(ptr)" << std::endl;

  Tiny::SharedPtr ptr3(std::move(ptr2));
  std::cout << "ptr3(std::move(ptr2))" << std::endl;

  Tiny::SharedPtr ptr4(new SharedPtrTest);
  std::cout << "ptr4(new TestClass)" << std::endl;

  ptr4 = ptr3;
  std::cout << "ptr4 = ptr3" << std::endl;

  Tiny::SharedPtr ptr5(new SharedPtrTest);
  std::cout << "ptr5(new TestClass)" << std::endl;

  ptr5 = std::move(ptr4);
  std::cout << "ptr5 = std::move(ptr4)" << std::endl;
}
} // namespace TestSharedPtr
} // namespace Tiny

#endif // TEST_TINY_SHARED_PTR_HPP