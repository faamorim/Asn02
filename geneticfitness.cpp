//
// Created by HP User on 11/25/2018.
//

#include "geneticfitness.hpp"

GeneticFitness::GeneticFitness(vector<Tour> pop, int nCities, int nElites, int poolSize, int nParents, int mutRate, int iter) :
            population(move(pop)), citiesInTour(nCities), numberOfElites(nElites), parentsPoolSize(poolSize),
            numberOfParents(nParents), mutationRate(mutRate), maxIterations(iter){
    sortPop(population);
}

void GeneticFitness::run(){
    cout << "Starting!" << endl;
    cout << "Max iterations: " << maxIterations << endl;
    double currentBest = population[0].getTourDistance();
    cout << "Starting best: " << population[0].getTourDistance() << endl;
    int count = 0;
    for(int i = 0; i < maxIterations; ++i){
        count++;
        nextGeneration();
        if(population[0].getTourDistance() < currentBest || count > 500){
            currentBest = population[0].getTourDistance();
            cout << "Best as of iteration #" << (i+1) << ": " << population[0].getTourDistance() << endl;
            count = 0;
        }
    }
    cout << "All time best: " << population[0].getTourDistance() << endl;
    cout << population[0].toString() << endl;
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
        int index1 = indexDistribution(engine);
        int index2 = indexDistribution(engine);
        swap(cities[index1], cities[index2]);
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
        newPopulation.push_back(mutate(crossOver(getParents())));
    }
    population = newPopulation;
    sortPop(population);
}

vector<Tour> GeneticFitness::getParents(){
    int parentsSize = numberOfParents < population.size() ? numberOfParents : (int)population.size();
    vector<Tour> parents;
    for(int par = 0; par < parentsSize; ++par) {
        vector<int> popuIndexes;
        for(int i = 0; i < population.size(); ++i){
            popuIndexes.push_back(i);
        }
        vector<Tour> parentPool;
        for (int pool = 0; pool < parentsPoolSize; ++pool) {
            uniform_int_distribution<int> indexDist{0, (int) popuIndexes.size() - 1};
            int index = indexDist(engine);
            parentPool.push_back(population[popuIndexes[index]]);
            popuIndexes.erase(find(popuIndexes.begin(), popuIndexes.end(), popuIndexes[index]));
        }
        sortPop(parentPool);
        parents.push_back(parentPool[0]);
    }
    return parents;
}


void GeneticFitness::sortPop(vector<Tour>& pop){
    sort(pop.begin(), pop.end(),
         [](const Tour &t1, const Tour &t2) -> bool {
             return t1.getTourDistance() < t2.getTourDistance();
         });
}