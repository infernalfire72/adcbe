#pragma once

// https://stackoverflow.com/a/22883968
#include <iostream>
#include <random>
#include <limits>
namespace Random {
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
                               //and seed it with entropy.

    //Define the distribution, by default it goes from 0 to MAX(unsigned long long)
    //or what have you.
    std::uniform_int_distribution<unsigned long long> distr;

    static unsigned long long Long() {
        return distr(eng);
    }
}