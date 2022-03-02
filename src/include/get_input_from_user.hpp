#pragma once
#include <iostream>

template<typename T>
T get_input_from_user()
{
    T input;
    //executes loop if the input fails (e.g., no characters were read)
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.sync();
        std::cout << "Invalid input; please re-enter.\n";
    }
    return input;
}