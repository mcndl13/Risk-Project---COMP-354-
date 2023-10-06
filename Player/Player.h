#pragma once
#include <iostream>
#include <vector>
#include "Territory.h"
#include "OrderList.h"


class Player {

        Player(const std::string& playername);
        ~Player();
        
        Player(const Player &p); // copy constructor
        Player& operator=(const Player &p); // assignment operator
        friend std::ostream& operator<<(std::ostream &os, const Player &p); // stream insertion operator
        
        void toDefend();
        void toAttack();
        void issueOrder(Order* order);


 private:
    std::string playername;
    std::vector<Territory*> owned_territories;
    std::vector<Territory*> enemy_territories;
    std::vector<OrderList*> order; 
 
};
