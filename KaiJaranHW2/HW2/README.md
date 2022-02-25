### <div style="text-align: right"> Kai Hoenshell M13843808 <br> Jaran Chao M14040812</div>

# Homework 2
## How to compile
### **NOTE:** all commands seen below were ran on MacOS Monterey 12.1 with clang/clang++ being installed with Homebrew
To run the program, please ensure that clang++ is on your PATH and run the following command:
```
clang++ -std=c++20 wheel.cpp utils.cpp main.cpp -o main.out && ./main.out
```

In this homework Jaran worked on the function prototypes in the header files and how they all go into `main.cpp`.

While Kai worked on `main.cpp` and how all of the functions are implemented into the roulette game.

Overall they both worked on this Homework 50/50. We didn't know the hard mode implementation should be put into the game given the directions so we just decided to make a subclass of `Wheel` called `Hardwheel` and changed the type of the wheel instance in the `main` function to be a `HardWheel` since it has all the functionalities of the not hard mode `Wheel` while adding on the functionalities needed for the hard mode. The hard mode functions would only be called if the conditions were met and also the hard mode `bool` flag is true.