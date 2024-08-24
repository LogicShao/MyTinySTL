#include <iostream>
#include "my_shared_ptr.hpp"

int main()
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

    return 0;
}