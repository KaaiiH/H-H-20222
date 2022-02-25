#ifndef CHOICE_H
#define CHOICE_H

namespace Roulette {
    // Enum for the player's choice on whether or not to half, double, or leave their bet the same.
    enum struct Choice {
        None = 1,
        Half = 2,
        Double = 3,
    };
}

#endif