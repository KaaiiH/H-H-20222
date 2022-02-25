#include "utils.h"

/**
 * @brief asks the player for their choice on changing their bet: don't change (None), half, or double
 * 
 * @param i reference to std::istream to access user input
 * @param o reference to std::ostream to print out choices to the user
 * @return Roulette::Choice enum of player's choice (None, Half, Double)
 */
auto Roulette::bet_choice(std::istream& i, std::ostream& o) -> Roulette::Choice {
    std::stringstream s{};
    s << "\n"
      << "Please choose your bet choice\n"
      << "1 - None\n"
      << "2 - Half\n"
      << "3 - Double\n";
    return static_cast<Roulette::Choice>(Roulette::input<std::int32_t>(i, o, s.str()));
}