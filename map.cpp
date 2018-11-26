//
// Created by HP User on 11/25/2018.
//

#include "map.hpp"
#include <iostream>


Map::Map(){
}

Map::Map(int width, int height, int num) : Map(){
    uniform_int_distribution<int> longitudeDistribution{0,height};
    uniform_int_distribution<int> latitudeDistribution{0,width};
    CityNameGenerator cityNameGenerator{engine};
    for(int i = 0; i < num; ++i) {
        City c{longitudeDistribution(engine), latitudeDistribution(engine), cityNameGenerator.generateName()};
        cities.push_back(c);
    }
};

vector<City> Map::getCities() const{
    vector<City> lc{cities};
    return lc;
}