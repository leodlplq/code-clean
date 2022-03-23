#include "./include/play_guess_the_number.hpp"
#include <iostream>
#include "./include/get_input_from_user.hpp"
#include "./include/menu.hpp"
#include "./include/random.hpp"

void play_guess_the_number()
{
    constexpr int lower_number  = 0;
    constexpr int higher_number = 100;
    const int     random_number = rand(lower_number, higher_number);

    std::cout << "I picked a number between " << lower_number << " and " << higher_number << std::endl;
    bool finished = false;
    while (!finished) {
        auto user_guess_number = get_input_from_user<int>();
        // Ask for a number
        if (user_guess_number == random_number) {
            std::cout << "Congrats, you won!" << std::endl;
            finished = true;
        }
        else {
            if (user_guess_number > random_number) {
                std::cout << "Smaller" << std::endl;
            }
            else {
                std::cout << "Greater" << std::endl;
            }
        }
    }
    display_menu();
}