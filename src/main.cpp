#include "../include/MTest/test_vector.hpp"
#include "../include/MTest/test_shared_ptr.hpp"
#include "../include/MTest/test_unique_ptr.hpp"

int main()
{
    MySTD::TEST::test_vector();
    MySTD::TEST::test_shared_ptr_1();
    MySTD::TEST::test_shared_ptr_2();
    MySTD::TEST::test_unique_ptr();

    return 0;
}