//
// Created by HP User on 11/23/2018.
//

#include "tour.hpp"

void Tour::calculateDistance(){
    totalDistance = 0;
    for(int i = 0; i < tour.size() - 1; ++i){
        totalDistance += distanceBetween(tour[i], tour[i+1]);
    }
    totalDistance += distanceBetween(tour[tour.size()-1], tour[0]);
}
double Tour::getTourDistance() const{
    //const_cast<Tour*>(this)->calculateDistance();
    return totalDistance;
}
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
    calculateDistance();
}

Tour::Tour(const Tour& copy) = default;

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
    cout << toString() << endl;
}

string Tour::toString(){
    stringstream ss;
    for(auto it = tour.begin(); it != tour.end(); ++it){
        ss << it->name << " > ";
    }
    ss << tour.begin()->name << " (" << getTourDistance() << ")" << endl;
    return ss.str();
}

double distanceBetween(City from, City to){
    double distLon = from.longitude - to.longitude;
    double distLat = from.latitude - to.latitude;
    return sqrt(distLon * distLon + distLat * distLat);
}