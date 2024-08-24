#include <iostream>
#include "my_shared_ptr.hpp"

struct TestClass
{
    TestClass()
    {
        std::cout << "TestClass constructor" << std::endl;
    }

    TestClass(const TestClass &other)
    {
        std::cout << "TestClass copy constructor" << std::endl;
    }

    TestClass(TestClass &&other)
    {
        std::cout << "TestClass move constructor" << std::endl;
    }

    ~TestClass()
    {
        std::cout << "TestClass destructor" << std::endl;
    }
};

void test1()
{
    MySTD::MySharedPtr ptr(new int(5));
    std::cout << "Value: " << *ptr << std::endl;
    std::cout << "Pointer: " << ptr.get() << std::endl;

    MySTD::MySharedPtr ptr2(ptr);
    std::cout << "Value: " << *ptr2 << std::endl;
    std::cout << "Pointer: " << ptr2.get() << std::endl;

    MySTD::MySharedPtr ptr3(std::move(ptr2));
    std::cout << "Value: " << *ptr3 << std::endl;
    std::cout << "Pointer: " << ptr3.get() << std::endl;

    MySTD::MySharedPtr ptr4(new int(10));
    ptr4 = ptr3;
    std::cout << "Value: " << *ptr4 << std::endl;
    std::cout << "Pointer: " << ptr4.get() << std::endl;

    MySTD::MySharedPtr ptr5(new int(15));
    ptr5 = std::move(ptr4);
    std::cout << "Value: " << *ptr5 << std::endl;
    std::cout << "Pointer: " << ptr5.get() << std::endl;
}

void test2()
{
    MySTD::MySharedPtr ptr(new TestClass);
    std::cout << "ptr(new TestClass)" << std::endl;

    MySTD::MySharedPtr ptr2(ptr);
    std::cout << "ptr2(ptr)" << std::endl;

    MySTD::MySharedPtr ptr3(std::move(ptr2));
    std::cout << "ptr3(std::move(ptr2))" << std::endl;

    MySTD::MySharedPtr ptr4(new TestClass);
    std::cout << "ptr4(new TestClass)" << std::endl;

    ptr4 = ptr3;
    std::cout << "ptr4 = ptr3" << std::endl;

    MySTD::MySharedPtr ptr5(new TestClass);
    std::cout << "ptr5(new TestClass)" << std::endl;

    ptr5 = std::move(ptr4);
    std::cout << "ptr5 = std::move(ptr4)" << std::endl;
}

int main()
{
    test2();
    return 0;
}