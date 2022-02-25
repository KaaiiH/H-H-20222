#ifndef UTILS_H
#define UTILS_H

#include "choice.h"
#include <iostream>
#include <string>
#include <sstream>

namespace Roulette {
    /**
     * @brief templated input function to make getting user input easier
     * @see python input function
     * 
     * @tparam O type of output
     * @param i reference to std::istream to access user input
     * @param o reference to std::ostream to print out the prompt to the user
     * @param prompt string of the prompt to print to the user before getting input
     * @return O 
     */
    template<typename O> auto input(std::istream& i, std::ostream& o, std::string prompt) -> O {
        O ret{};

        std::string line;

        o << prompt;
        std::getline(i, line);
        std::stringstream(line) >> ret;

        return ret;
    }

    // declaration of bet choice
    auto bet_choice(std::istream&, std::ostream&) -> Roulette::Choice;
}

#endif