#ifndef TEST_THREAD_HPP
#define TEST_THREAD_HPP

#include "../Thread.hpp"
#include <iostream>

namespace Tiny {
namespace TestThread {
namespace ThreadTest {
inline void foo() { std::cout << "foo" << std::endl; }

inline void add(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
} // namespace ThreadTest

inline void test_Thread() {
  std::cout << "Thread test" << std::endl;

  std::cout << "This Thread:" << Tiny::This_Thread::get_id() << std::endl;

  std::cout << "Thread t1(ThreadTest::foo);" << std::endl;
  Tiny::Thread t1(ThreadTest::foo);
  t1.join();

  std::cout << "Thread t2(ThreadTest::add, 1, 2);" << std::endl;
  Tiny::Thread t2(ThreadTest::add, 1, 2);
  t2.join();
}
} // namespace TestThread
} // namespace Tiny

#endif // TEST_THREAD_HPP