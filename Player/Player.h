#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Territory;

class Player{

    private:
        vector<Territory*> owned_territories;
        int player_ID;


    
    public:
        Player();

        Player(int id);

};


