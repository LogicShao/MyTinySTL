#include "test_shared_ptr.hpp"
#include "test_unique_ptr.hpp"
#include "test_vector.hpp"

int main()
{
    test_vector();
    test_shared_ptr_1();
    test_shared_ptr_2();
    test_unique_ptr();

    return 0;
}