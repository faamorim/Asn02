//
// Created by HP User on 11/25/2018.
//

#ifndef ASN02_GENETICFITNESS_HPP
#define ASN02_GENETICFITNESS_HPP

#include <algorithm>
#include <set>
#include <list>
#include "tour.hpp"
#include "map.hpp"

class GeneticFitness {
    int citiesInTour;
    int numberOfElites;
    int parentsPoolSize;
    int numberOfParents;
    int mutationRate;
    int maxIterations;
public:
    GeneticFitness(vector<Tour> pop, int nCities, int nElites, int poolSize, int nParents, int mutRate, int iter);
    void run();
    vector<Tour> population;
    void nextGeneration();
    Tour crossOver(vector<Tour> parents);
    Tour mutate(Tour t);
    vector<Tour> getParents();
    void sortPop(vector<Tour>& pop);
};


#endif //ASN02_GENETICFITNESS_HPP
