#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Territory;

class Player: public Continent; public Territory{

        Player();
        ~Player();
        
        Player(const Player &p); // copy constructor
        Player& operator=(const Player &p); // assignment operator
        friend std::ostream& operator<<(std::ostream &os, const Player &p); // stream insertion operator
        
        Continent toDefend(){
            return owned_territories;
        }

        toAttack(continent){
            return continent;
        }

        issueOrder(order){
            return order;
        }


 private:
     vector<Territory*> owned_territories;
        int player_ID;
    Continent continent;
    Order order;   
 
};


