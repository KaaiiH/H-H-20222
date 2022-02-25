#ifndef PLAYER_H
#define PLAYER_H

#include "wheel.h"

namespace Roulette {
    // Player struct for choices and earnings related strictly to the player not the house
    struct Player {
    private:
        std::int32_t earnings = 1000; // default earnings is $1000

        Roulette::Wheel wheel; // storage for the instance of wheel

    public:
        explicit Player(): wheel() {}

        explicit Player(Roulette::Wheel wheel): wheel(wheel) {}

        // getter for earnings
        auto get_earnings() -> std::int32_t {
            return this->earnings;
        }

        // setter for earnings
        void set_earnings(std::int32_t new_earnings) {
            this->earnings = new_earnings;
        }

        // add an amount to the player's earnings
        void add_earnings(std::int32_t amount) {
            this->earnings += amount;
        }

        // getter for wheel 
        auto get_wheel() -> Roulette::Wheel {
            return this->wheel;
        }

        // setter for wheel
        void set_wheel(Roulette::Wheel new_wheel) {
            this->wheel = new_wheel;
        }
    };
}

#endif