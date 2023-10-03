#include <iostream>
#include <string>
#include "Territory.h"
#include "Continent.h"

using namespace std;



Continent::Continent (){ // Default constructor
    continent_name = "";
}



Continent::Continent (const string& name){
    continent_name = name;
}


int main(){

    return 0;
}