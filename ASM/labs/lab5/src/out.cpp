//
// Created by dmitry on 23.04.2024.
//

#include <iostream>

extern "C"
{
    void print_result(const char *res)
    {
        std::cout << "results of the execution: " << res << std::endl;
    }
}