#include "./include/play_guess_the_number.hpp"

int get_int_from_user()
{
    int int_from_user;
    //executes loop if the input fails (e.g., no characters were read)
    while (!(std::cin >> int_from_user)) {
        std::cin.clear();                                                   //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    return int_from_user;
}

void play_guess_the_number()
{
    const int lower_number  = 0;
    const int higher_number = 100;
    const int random_number = rand(lower_number, higher_number);

    int user_guess_number;
    std::cout << "I picked a number between " << lower_number << " and " << higher_number << std::endl;
    bool finished = false;
    while (!finished) {
        user_guess_number = get_int_from_user();
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
}