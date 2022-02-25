#include <iostream>
#include "wheel.h"
#include "player.h"
#include "choice.h"
#include "utils.h"

/**
 * Use of auto keyword an trailing return types for syntactic sugar and ease of use
 * for auto keyword @see https://en.cppreference.com/w/cpp/language/auto 
 * for trailing return types @see https://en.cppreference.com/w/cpp/language/function
*/
auto main() -> int {
    bool cashed_out = false; // this booloen will turn true if they decide to cash out
    bool house_win_prev = false; // boolean flag to tell us if the house won the previous round, true if house won
    bool house_win_curr = false; // boolean flag to tell us if the house won the current round, true if house won

    char hard_mode_choice = Roulette::input<char>(std::cin, std::cout, "Would you like to play on hard mode? (y/n) ");
    bool hard_mode = hard_mode_choice == 'y' || hard_mode_choice == 'Y'; // if the player chose hardmode then true else false

    std::size_t num_of_values = 0;

    do {
        // See utils.cpp
        num_of_values = Roulette::input<std::size_t>(std::cin, std::cout, "Number of values on the roulette board, min of 6, max of 20:\n");
    } while(num_of_values < 6 || num_of_values > 20);

    Roulette::Wheel::wheel_buffer wheel_values{};
    for(std::size_t i = 0; i < num_of_values; i++) {
        wheel_values.emplace_back(Roulette::input<Roulette::Wheel::wheel_buffer::value_type>(std::cin, std::cout, "Enter value for the wheel: "));
    }

    // Creating a wheel based off of the inputted wheel values
    auto wheel = Roulette::HardWheel(wheel_values);
    
    // Giving wheel because player and house are both suppose to hold an instance of wheel
    auto player = Roulette::Player(wheel);
    auto house = Roulette::Player(wheel);


    
    std::cout << "-----Congratulation you have $1000 to spend on a roulette wheel!-----\n";
    
    while(player.get_earnings() > 0 && !cashed_out) {
        std::int32_t bet = 0;
        do {
            bet = Roulette::input<std::int32_t>(std::cin, std::cout, "\nPlace bet: ");
            if(bet > player.get_earnings()) {
                std::cout << "You do not have that much money, you currently have $" << player.get_earnings() << "\nPlease insert bet again\n";
            }
        } while(bet > player.get_earnings());

        auto player_spin = player.get_wheel().spin();
        
        std::cout << "Player spun for a value of " << player_spin << "\n";

        auto player_choice = Roulette::bet_choice(std::cin, std::cout);

        auto house_spin1 = house.get_wheel().spin();
        auto house_spin2 = house.get_wheel().spin();

        switch(player_choice) {
            // This code will execute if they player chooses None
            case Roulette::Choice::None: 
                std::cout << "House spun for a value of " << house_spin1 << "\n";
                if(player_spin > house_spin1) {
                    player.add_earnings(bet);
                    std::cout << "!!!!!YOU WON!!!!!\n";
                    house_win_curr = false;
                } else {
                    player.add_earnings(-bet);
                    std::cout << "-----YOU LOST :(-----\n";
                    house_win_curr = true;
                }
                break;
            // This code will execute if they player chooses Half
            case Roulette::Choice::Half:
                std::cout << "House spun for a value of " << house_spin1 << " and a value of " << house_spin2 << "\n";
                if(player_spin > house_spin1 && player_spin > house_spin2) {
                    player.add_earnings(bet / 2);
                    std::cout << "!!!!!YOU WON!!!!!\n";
                    house_win_curr = false;
                }
                else if((player_spin < house_spin1 && player_spin > house_spin2) && (player_spin > house_spin1 && player_spin < house_spin2)) {
                    // In this case the game is tied so the player nor the house get any earning.
                    std::cout << "!@#$% YOU TIED?!?! !@#$%\n";
                    house_win_curr = true;
                } else {
                    player.add_earnings(-bet);
                    std::cout << "-----YOU LOST :(-----\n";
                    house_win_curr = true;
                }
                break;
            // This code will execute if they player chooses Double
            case Roulette::Choice::Double:
                std::cout << "House spun for a value of " << house_spin1 << " and a value of " << house_spin2 << "\n";
                if(player_spin > house_spin1 && player_spin > house_spin2) {
                    player.add_earnings(bet * 2);
                    std::cout << "!!!!!YOU WON!!!!!\n";
                    house_win_curr = false;
                } else {
                    player.add_earnings(bet * -2);
                    std::cout << "-----YOU LOST :(-----\n";
                    house_win_curr = true;
                }
                break;
            default:
                // since the switch statement is exhaustive (checks all possible branches)
                // the default branch of the switch statement should be unreachable
                break;
        }

        if(hard_mode && house_win_curr && house_win_prev) {
            std::cout << "Removing value " << wheel.get_wheel_buffer().back() << " from the wheel\n";
            wheel.remove_value_from_wheel();
            house_win_curr = false;
            house_win_prev = false;
        } else if(hard_mode && !house_win_curr) {
            wheel.add_value_to_wheel(
                Roulette::input<Roulette::HardWheel::wheel_buffer::value_type>(std::cin, std::cout, "Enter a new value to be added to the wheel: ")
            );
        }

        std::cout << "Current earnings of Player: $" << player.get_earnings() << "\n";

        // break out of the loop if the player loses money and is in debt
        if(player.get_earnings() < 0) {
            std::cout << "You have lost all your money, HOUSE ALWAYS WINS\n";
            break;
        }
        
        // this char will return y and n indicating whether the player wants to cash out.
        // if the player wants to cash out the cashed_out bool will go true
        char cash_out_choice = Roulette::input<char>(std::cin, std::cout, "Would you like to cash out? (y/n) "); 

        if(cash_out_choice == 'y' || cash_out_choice == 'Y') {
            cashed_out = true;
            std::cout << "Player cashed out with $" << player.get_earnings() << "\n";
        }

        // updating previous with current as the current round will become the previous
        house_win_prev = house_win_curr;
    }

    return 0;
}