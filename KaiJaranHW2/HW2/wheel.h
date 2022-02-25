#ifndef WHEEL_H
#define WHEEL_H

#include <vector>

namespace Roulette {
    class Wheel {
    public:
        /**
         * @brief generalizing the underlying vector type held in Wheel in the case the developer doesn't know the exact underlying type
         * @see https://en.cppreference.com/w/cpp/language/type_alias
         */
        using wheel_buffer = std::vector<std::int32_t>;
    
    protected:
        // std::vector<std::int32_t> for holding the values of the wheel
        wheel_buffer values;

    public:
        // no arg constructor with the default values of 1 - 10
        explicit Wheel(): values({1,2,3,4,5,6,7,8,9,10}) {
            std::srand(std::time(nullptr));
        }

        // one arg constructor to pass in the values of the wheel, using std::move to indicate ownership change
        explicit Wheel(wheel_buffer& values): values(values) {
            // setting the random seed to the current time
            std::srand(std::time(nullptr));
        }

        // getter for the reference to the underlying value buffer
        auto get_wheel_buffer() -> wheel_buffer {
            return this->values;
        }

        // declaration of spin
        auto spin() -> std::int32_t;
    };

    class HardWheel : public Wheel {
    public:
        explicit HardWheel(): Wheel() {}

        explicit HardWheel(wheel_buffer& w_values): Wheel(w_values) {
            // setting the random seed to the current time
            std::srand(std::time(nullptr));
        }
        
        // instead of making a dervied class for spin we decided to make new functions that add values to the wheel if the house loses in hardmode.
        void add_value_to_wheel(std::int32_t new_value) {
            this->values.emplace_back(new_value);
        }

        // if the house loses two times in a row we will use this function to remove sides from the house in hardmode.
        void remove_value_from_wheel() {
            this->values.pop_back();
        }
    };
}

#endif