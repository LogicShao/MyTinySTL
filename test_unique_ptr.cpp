#include <iostream>
#include "my_unique_ptr.hpp"

struct TestClass
{
    TestClass()
    {
        std::cout << "TestClass constructor" << std::endl;
    }

    ~TestClass()
    {
        std::cout << "TestClass destructor" << std::endl;
    }
};

int main()
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

    MySTD::MyUniquePtr ptr4(new TestClass);
    MySTD::MyUniquePtr ptr5(ptr4.release());

    return 0;
}