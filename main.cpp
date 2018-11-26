#include <iostream>
#include "tour.cpp"
#include "map.cpp"
#include "city.cpp"
#include "geneticfitness.cpp"

using namespace std;

#define CITIES_IN_MAP 32
#define CITIES_IN_TOUR 32
#define POPULATION_SIZE 32
#define ITERATIONS 1000
#define MAP_BOUNDARIES 1000
#define MUTATION_RATE 25
#define PARENT_POOL_SIZE 8
#define NUMBER_OF_PARENTS 3
#define NUMBER_OF_ELITES 3



int main() {
    Map map{MAP_BOUNDARIES, MAP_BOUNDARIES, CITIES_IN_MAP};
    vector<Tour> population;

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        population.emplace_back(Tour(map, CITIES_IN_TOUR, true));
    }
    GeneticFitness geneticFun{population, CITIES_IN_TOUR, NUMBER_OF_ELITES, PARENT_POOL_SIZE, NUMBER_OF_PARENTS, MUTATION_RATE, ITERATIONS};
    geneticFun.run();
    return 0;
}
