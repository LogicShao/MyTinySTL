#include "MTest/test_Array.hpp"
#include "MTest/test_SharedPtr.hpp"
#include "MTest/test_Thread.hpp"
#include "MTest/test_UniquePtr.hpp"
#include "MTest/test_Vector.hpp"

int main() {
  Tiny::TestThread::test_Thread();
  Tiny::TestArray::test_Array();
  Tiny::TestVector::test_Vector();
  Tiny::TestSharedPtr::test_SharedPtr_1();
  Tiny::TestSharedPtr::test_SharedPtr_2();
  Tiny::TestUniquePtr::test_UniquePtr();

  return 0;
}