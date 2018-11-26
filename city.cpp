//
// Created by HP User on 11/23/2018.
//

#include "city.hpp"

City::City(int lon, int lat, string n) : longitude(lon), latitude(lat), name(n) {};
City::City(const City& c) : City(c.longitude, c.latitude, c.name) {};
void swap(City& lhs, City& rhs){
    swap(lhs.longitude, rhs.longitude);
    swap(lhs.latitude, rhs.latitude);
    swap(lhs.name, rhs.name);
}
bool City::operator==(const City &rhs) {
    return name == rhs.name && longitude == rhs.longitude && latitude == rhs.latitude;
}