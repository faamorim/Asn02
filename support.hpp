//
// Created by HP User on 11/25/2018.
//

#ifndef ASN02_SUPPORT_HPP
#define ASN02_SUPPORT_HPP

#include <random>
#include <chrono>

using namespace std;

random_device rd{};
default_random_engine engine{rd.entropy() != 0 ? rd() : (unsigned int) chrono::steady_clock::now().time_since_epoch().count()};

#endif //ASN02_SUPPORT_HPP
