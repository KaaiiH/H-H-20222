#include "wheel.h"

// returns a random value from the values vector held in wheel
auto Roulette::Wheel::spin() -> std::int32_t {
    return this->values[std::rand() % this->values.size()];
};