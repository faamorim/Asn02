//
// Created by HP User on 11/23/2018.
//

#include "citynamegenerator.hpp"

CityNameGenerator::CityNameGenerator(default_random_engine& eng, const string& fileName, int min, int max) : engine(eng){
    normalize(min, max);
    minSyllables = min;
    maxSyllables = max;
    minMaxDistribution = uniform_int_distribution<int>(min, max);
    ifstream file{fileName, ios_base::in};
    if(!file.is_open()) {
        file = ifstream{"../" + fileName, ios_base::in};
        if(!file.is_open()) {
            cout << "Unable to open file " << fileName << endl;
            return;
        }
    }
    string syllable;
    while (file >> syllable) {
        syllables.push_back(syllable);
    }
    syllableDistribution = uniform_int_distribution<int>(0, (int)syllables.size() - 1);
}

CityNameGenerator::CityNameGenerator(const CityNameGenerator &copy) : engine(copy.engine) {
    minMaxDistribution = copy.minMaxDistribution;
    syllableDistribution = copy.syllableDistribution;

    syllables = copy.syllables;
    minSyllables = copy.minSyllables;
    maxSyllables = copy.maxSyllables;
}

string CityNameGenerator::generateName(int min, int max){
    normalize(min, max);
    int numSyllables = 0;
    if(min == minSyllables && max == maxSyllables) {
        numSyllables = minMaxDistribution(engine);
    }
    else {
        cout << "dafuq" << endl;
        uniform_int_distribution<int> dist{min, max};
        numSyllables = dist(engine);
    }
    string name{};
    for(int s = 0; s < numSyllables; ++s){
        int syllable = syllableDistribution(engine);
        name += syllables.at((unsigned long long int)syllable);
    }
    name.replace(0, 1, 1, (char)toupper(name.at(0)));
    return name;
}

void normalize(int& min, int& max){
    min = min < 1 ? 1 : min;
    max = max < min ? min : max;
}