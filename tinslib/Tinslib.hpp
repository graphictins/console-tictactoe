// mylib.hpp

// it includes onceses
#pragma once  

#include <random>

// this means no copy thing
namespace tinslib 
{

    inline int rand_range(int min, int max)
    {
        std::random_device random_device; // obtain a random number from hardware
        std::mt19937 generator(random_device()); // seed the generator
        std::uniform_int_distribution<> range(min, max); // define the range

        return range(generator);
    }

}
