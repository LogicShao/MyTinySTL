#include "MTest/test_Array.hpp"
#include "MTest/test_SharedPtr.hpp"
#include "MTest/test_Thread.hpp"
#include "MTest/test_UniquePtr.hpp"
#include "MTest/test_Vector.hpp"

int main() {
  Tiny::TEST::test_Thread();
  Tiny::TEST::test_Array();
  Tiny::TEST::test_Vector();
  Tiny::TEST::test_SharedPtr_1();
  Tiny::TEST::test_SharedPtr_2();
  Tiny::TEST::test_UniquePtr();

  return 0;
}