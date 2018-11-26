//
// Created by HP User on 11/23/2018.
//

#include "tour.hpp"

double Tour::getTourDistance() const {return sqrt(totalDistanceSquare);}
vector<City> Tour::getTour() const {
    vector<City> lc{tour};
    return lc;
};

Tour::Tour(const vector<City>& cities, int length, bool randomize) : tour(cities){
    if(randomize)
        shuffleCities();
    if(length < tour.size() && length > 0){
        tour = vector<City>(tour.begin(), tour.begin() + length);
    }
    totalDistanceSquare = 0;
    auto it = tour.begin();
    City startingCity = *(it);
    for(City lastCity = *(it++); it != tour.end(); ++it){
        totalDistanceSquare += distanceBetween(lastCity, *it);
    }
}

Tour::Tour(const Tour& copy) : tour(copy.tour), totalDistanceSquare(copy.totalDistanceSquare){
}

Tour::Tour(const vector<City>& cities, bool randomize) : Tour(cities, (int)cities.size(), randomize){
}

Tour::Tour(const Map& map, int length, bool randomize) : Tour(map.getCities(), length, randomize){
}

void Tour::shuffleCities(int nShuffles) {
    uniform_int_distribution<int> indexDistribution(0, (int) tour.size() - 1);
    while(nShuffles > 0) {
        int i1 = indexDistribution(engine);
        int i2 = indexDistribution(engine);
        swap(tour[i1], tour[i2]);
        --nShuffles;
    }
}

string Tour::toString(){
    stringstream ss;
    for(auto it = tour.begin(); it != tour.end(); ++it){
        ss << it->name << " < ";
    }
    ss << tour.begin()->name;
    return ss.str();
}

double distanceBetween(City from, City to){
    return pow(from.longitude - to.longitude, 2) + pow(from.latitude - to.latitude, 2);
}