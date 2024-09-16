#include "MTest/test_Array.hpp"
#include "MTest/test_SharedPtr.hpp"
#include "MTest/test_UniquePtr.hpp"
#include "MTest/test_Vector.hpp"

int main() {
  Tiny::TEST::test_array();
  Tiny::TEST::test_vector();
  Tiny::TEST::test_shared_ptr_1();
  Tiny::TEST::test_shared_ptr_2();
  Tiny::TEST::test_unique_ptr();

  return 0;
}