//
// Created by HP User on 11/25/2018.
//

#include "geneticfitness.hpp"

GeneticFitness::GeneticFitness(vector<Tour> pop, int nCities, int nElites, int poolSize, int nParents, int mutRate, int iter) :
            population(move(pop)), citiesInTour(nCities), numberOfElites(nElites), parentsPoolSize(poolSize),
            numberOfParents(nParents), mutationRate(mutRate), maxIterations(iter){
    sort(population.begin(), population.end(),
         [](const Tour & t1, const Tour & t2) -> bool
         {
             return t1.getTourDistance() < t2.getTourDistance();
         });
}

Tour GeneticFitness::crossOver(vector<Tour> parents){
    uniform_int_distribution<int> indexDistribution(0, citiesInTour - 1);
    vector<int> indexWeights;
    int totalWeight = 0;
    for(int i = 0; i < parents.size(); ++i){
        int curWeight = indexDistribution(engine) + 1;
        indexWeights.push_back(curWeight);
        totalWeight += curWeight;
    }
    int curWeightedIndex = 0;
    vector<int> indexes;
    for(int i = 0; i < parents.size(); ++i){
        curWeightedIndex += indexWeights[i];
        int curIndex = (int)floor(citiesInTour * curWeightedIndex/totalWeight);
        indexes.push_back(curIndex);
    }
    vector<City> cities;
    int parent = 0;
    int currentIndex = 0;
    City currentCity = parents.at(0).getTour().at(indexDistribution(engine));
    while(currentIndex < citiesInTour){
        vector<City> curParent = parents.at(parent).getTour();
        int currentMaxIndex = indexes[parent];
        for(auto it = find(curParent.begin(), curParent.end(), currentCity); currentIndex < currentMaxIndex;){
            ++it;
            if(it == curParent.end()){
                it = curParent.begin();
            }
            if(find(cities.begin(), cities.end(), *it) == cities.end()){
                cities.push_back(*it);
                ++currentIndex;
                currentCity = *it;
            }
        }
        ++parent;
    }
    return Tour{cities, false};
}

Tour GeneticFitness::mutate(Tour t){
    vector<City> cities = t.getTour();
    uniform_int_distribution<int> indexDistribution(0, citiesInTour - 1);
    uniform_int_distribution<int> chance{0, 100};
    int mutations = 0;
    while(chance(engine) < mutationRate && mutations <= citiesInTour){
        mutations++;
    }
    while(mutations > 0){
        int index = indexDistribution(engine);
        if (index < citiesInTour - 1){
            swap(cities[index], cities[index+1]);
        } else {
            swap(cities[index], cities[0]);
        }
        mutations--;
    }
    return Tour{cities};
}

void GeneticFitness::nextGeneration(){
    vector<Tour> newPopulation;
    auto it = population.begin();
    int elites = 0;
    while(elites < numberOfElites && it != population.end()){
        newPopulation.push_back(*it++);
        elites++;
    }
    for(; it != population.end(); ++it){
        vector<int> popuIndexes;
        for(int i = 0; i < population.size(); ++i){
            popuIndexes.push_back(i);
        }
        vector<Tour> parentPool;
        for(int p = 0; p < parentsPoolSize; ++p){
            uniform_int_distribution<int> indexDist{0, (int)popuIndexes.size() - 1};
            int index = indexDist(engine);
        }
    }
}

