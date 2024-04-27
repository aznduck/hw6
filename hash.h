#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int wIndex = 4;
        unsigned long long hk = 0;
        std::vector<unsigned long long> w(5, 0);
        std::vector<HASH_INDEX_T> a;
        for(int i = k.size() - 1; i >= 0; i--)
        {
            if(a.size() < 6)
            {
                a.push_back(letterDigitToNumber(k[i]));
            }
            else
            {
                w[wIndex] = baseToDecimal(36, a, 0);
                wIndex--;
                a.clear();
                a.push_back(letterDigitToNumber(k[i]));
            }
        }
        if(!a.empty())
        {
            for(unsigned int i = 0; i < 6 - a.size(); i++)
            {
                a.push_back(0);
            }
            w[wIndex] = baseToDecimal(36, a, 0);
        }
        for(unsigned int i = 0; i < w.size(); i++)
        {
            hk += w[i] * rValues[i];
        }
        // for(unsigned int i = 0; i < w.size(); i++)
        // {
        //     std::cout << i << " " << w[i] << std::endl;
        // }
        return hk;
    }

    unsigned long long baseToDecimal(unsigned long long base, std::vector<HASH_INDEX_T> a, unsigned int index) const
    {   
        if (index == a.size()) return 0; 
        return a[index] + base * baseToDecimal(base, a, index + 1);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
       if (isalpha(letter)) {
            letter = tolower(letter); 
            return letter - 'a'; 
        } else if (isdigit(letter)) {
            return 26 + (letter - '0'); 
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
