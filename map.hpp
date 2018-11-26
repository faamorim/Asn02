//
// Created by HP User on 11/25/2018.
//

#ifndef ASN02_MAP_HPP
#define ASN02_MAP_HPP

#include <random>
#include <vector>
#include "city.hpp"
#include "citynamegenerator.cpp"
#include "support.hpp"

using namespace std;

class Map {
private:
    vector<City> cities;
public:
    vector<City> getCities() const;
    Map(int width, int height, int num);
};


#endif //ASN02_MAP_HPP
