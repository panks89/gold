// Shared Pointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "shared_ptr.h"

int main()
{
    std::cout << "Hello World!\n";

    local::shared_ptr<int> sptr{ new int(10) };
    {
        local::shared_ptr<int> sptr_copy{ sptr };
        local::shared_ptr<int> ptr{ new int(20) };
        local::shared_ptr<int> ptr1{ ptr };
        std::cout << " sptr_copy use_count = " << sptr_copy.use_count() << std::endl;
        sptr = std::move(ptr);
        std::cout << *ptr1 << std::endl;
        std::cout << " sptr_copy use_count = " << sptr_copy.use_count() << std::endl;
        std::cout << " sptr_copy : " << *sptr_copy << std::endl;
        std::cout << " sptr use_count = " << sptr.use_count() << std::endl;
    }
    std::cout << " sptr : " << *sptr << std::endl;
    std::cout << " sptr use_count = " << sptr.use_count() << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
