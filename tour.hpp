//
// Created by HP User on 11/23/2018.
//

#ifndef ASN02_TOUR_HPP
#define ASN02_TOUR_HPP

#include <algorithm>
#include <sstream>
#include "map.hpp"
#include "support.hpp"

#define SHUFFLES 64

class Tour {
private:
    vector<City> tour;
    double totalDistance;
    void calculateDistance();
public:
    Tour(const vector<City>& cities, int length, bool randomize = false);
    explicit Tour(const vector<City>& cities, bool randomize = false);
    Tour(const Tour& copy);
    Tour(const Map& map, int length, bool randomize = false);
    vector<City> getTour() const;
    void shuffleCities(int nShuffles = SHUFFLES);
    double getTourDistance() const;
    string toString();
};
double distanceBetween(City from, City to);

#endif //ASN02_TOUR_HPP
