#include "./include/play_hangman.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include "./include/get_input_from_user.hpp"
#include "./include/menu.hpp"
#include "./include/random.hpp"

std::string get_random_word()
{
    static constexpr std::array word_list    = {"code", "miru", "thinker", "computer", "eggnog", "birds", "wrong", "green", "passenger", "aspiring", "bite", "sized", "succeed", "smelly", "push", "infamous", "account"};
    int                         random_index = rand(0, word_list.size());
    std::cout << random_index << " " << word_list[random_index] << std::endl;
    return word_list[random_index];
}

void show_number_of_lives(int nb_lives)
{
    std::cout << nb_lives << std::endl;
}

bool is_player_alive(int nb_lives)
{
    return nb_lives > 0;
}

bool has_player_won(const std::vector<bool>& letter_guessed)
{
    // all true
    return std::all_of(letter_guessed.begin(), letter_guessed.end(), [](bool v) { return v; });
}

void show_word_with_missing_letters(const std::string& word, std::vector<bool>& letter_guessed)
{
    std::string newWord(word);
    for (size_t i = 0; i < letter_guessed.size(); i++) {
        newWord[i] = letter_guessed[i] ? word[i] : '_';
    }
    std::cout << newWord << std::endl;
}

bool word_contains(char letter, std::string& word)
{
    return word.find(letter) != std::string::npos;
}

void mark_as_guessed(char guessed_letter, std::vector<bool>& letters_guessed, std::string_view word_to_guess)
{
    std::transform(letters_guessed.begin(), letters_guessed.end(), word_to_guess.begin(), letters_guessed.begin(), [&](bool b, char letter) {
        if (guessed_letter == letter) {
            return true;
        }
        else {
            return b;
        }
    });
}

void remove_one_life(int& nb_lives)
{
    nb_lives--;
}

void show_congrats_message(std::string_view word_to_guess)
{
    std::cout << "ggs the right word was : " << word_to_guess;
}

void show_defeat_message(std::string_view word_to_guess)
{
    std::cout << "you're so bad... ewww, the good word was : " << word_to_guess;
}

void play_hangman()
{
    // TODO: adapt the code below to make it work
    std::string       word_to_guess = get_random_word();
    std::vector<bool> guessed_letters(word_to_guess.size());
    int               nb_lives = 8;

    while (is_player_alive(nb_lives) && !has_player_won(guessed_letters)) {
        show_number_of_lives(nb_lives);
        show_word_with_missing_letters(word_to_guess, guessed_letters);
        const auto guess = get_input_from_user<char>();
        if (word_contains(guess, word_to_guess)) {
            mark_as_guessed(guess, guessed_letters, word_to_guess);
        }
        else {
            remove_one_life(nb_lives);
        }
    }
    if (has_player_won(guessed_letters)) {
        show_congrats_message(word_to_guess);
    }
    else {
        show_defeat_message(word_to_guess);
    }
    display_menu();
}