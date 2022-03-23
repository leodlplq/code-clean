#include "./include/menu.hpp"
#include <iostream>
#include "./include/get_input_from_user.hpp"
#include "./include/play_guess_the_number.hpp"
#include "./include/play_hangman.hpp"

void initiate_menu()
{
    std::cout << "Choose your game" << std::endl;
    std::cout << "a - Guess the number" << std::endl;
    std::cout << "b - Hangman" << std::endl;
    std::cout << "q - Quit game." << std::endl;
}

void display_menu()
{
    bool in_menu = true;
    initiate_menu();
    auto choice = get_input_from_user<char>();
    while (in_menu) {
        switch (choice) {
        case 'a':
            in_menu = false;
            play_guess_the_number();
            break;

        case 'b':
            in_menu = false;
            play_hangman();
            break;

        case 'q':
            in_menu = false;
            break;

        default:
            std::cout << "No options " << choice << " existing, please retry." << std::endl;
            choice = get_input_from_user<char>();
            break;
        }
    }
}