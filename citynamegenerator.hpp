//
// Created by HP User on 11/23/2018.
//

#ifndef ASN02_CITYGENERATOR_HPP
#define ASN02_CITYGENERATOR_HPP

#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

#define BASE_MIN_SYLLABLES 2
#define BASE_MAX_SYLLABLES 4
#define BASE_FILE_NAME "Syllables.txt"


class CityNameGenerator {
private:
    default_random_engine& engine;
    uniform_int_distribution<int> minMaxDistribution;
    uniform_int_distribution<int> syllableDistribution;

    vector<string> syllables;
    int minSyllables;
    int maxSyllables;
public:
    explicit CityNameGenerator(default_random_engine& eng, const string& fileName = BASE_FILE_NAME, int min = BASE_MIN_SYLLABLES, int max = BASE_MAX_SYLLABLES);
    CityNameGenerator(const CityNameGenerator& copy);
    string generateName() {return generateName(minSyllables, maxSyllables);}
    string generateName(int min, int max);
};

//

void normalize(int& min, int& max);


#endif //ASN02_CITYGENERATOR_HPP
