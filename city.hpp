//
// Created by HP User on 11/23/2018.
//

#ifndef ASN02_CITY_HPP
#define ASN02_CITY_HPP

#include <string>

using namespace std;

class City {
public:
    int longitude;
    int latitude;
    string name;
    City(int lon, int lat, string n);
    City(const City& c);
    friend void swap(City& lhs, City& rhs);
    bool operator==(const City& rhs);
};


#endif //ASN02_CITY_HPP
