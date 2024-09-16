#pragma once

#include <iostream>
#include "../my_array.hpp"

namespace MySTD
{
    namespace TEST
    {
        template <typename T, std::size_t N>
        void print_array(const MySTD::MyArray<T, N> &arr)
        {
            for (int i = 0; i < arr.size(); i++)
            {
                std::cout << arr[i] << ' ';
            }
            std::cout << std::endl;
        }

        void test_array()
        {
            MySTD::MyArray<int, 5> arr;

            for (int i = 0; i < arr.size(); i++)
            {
                arr[i] = i + 1;
            }
            print_array(arr);

            MySTD::MyArray<int, 5> arr2 = arr;
            print_array(arr2);

            MySTD::MyArray<int, 5> arr3 = std::move(arr2);
            print_array(arr3);

            MySTD::MyArray<int, 5> arr4;
            arr4 = arr3;
            print_array(arr4);
        }
    }
}