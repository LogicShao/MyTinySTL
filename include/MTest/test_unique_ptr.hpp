#include <iostream>
#include "../my_unique_ptr.hpp"

namespace MySTD
{
    namespace TEST
    {
        struct TestUniquePtr
        {
            TestUniquePtr()
            {
                std::cout << "TestClass constructor" << std::endl;
            }

            ~TestUniquePtr()
            {
                std::cout << "TestClass destructor" << std::endl;
            }
        };

        void test_unique_ptr()
        {
            MySTD::MyUniquePtr ptr(new int(5));
            std::cout << "Value: " << *ptr << std::endl;
            std::cout << "Pointer: " << ptr.get() << std::endl;

            ptr.reset(new int(10));
            std::cout << "Value: " << *ptr << std::endl;
            std::cout << "Pointer: " << ptr.get() << std::endl;

            MySTD::MyUniquePtr ptr2(std::move(ptr));
            std::cout << "Value: " << *ptr2 << std::endl;
            std::cout << "Pointer: " << ptr2.get() << std::endl;

            MySTD::MyUniquePtr ptr3(ptr2.release());
            std::cout << "Value: " << *ptr3 << std::endl;
            std::cout << "Pointer: " << ptr3.get() << std::endl;

            MySTD::MyUniquePtr ptr4(new TestUniquePtr);
            MySTD::MyUniquePtr ptr5(ptr4.release());
        }
    }
}