#include <iostream>
#include <string>
#include <vector>
#include "Continent.h"
#include "Territory.h"

using namespace std;


Territory::Territory(int id, const string& name){
    territory_name = name;
    this->id = id;
    continent = nullptr;
}


void Territory::AddNeighbour (Territory * neighbour){ // Adding neighbouring territories

    neighbours.push_back(neighbour);
}




// Now you can use the Territory class in your Continent class or any other part of your code.
