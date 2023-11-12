#pragma once
#include <vector>
#include <deque>
#include "../Map/Map.h"

class Hand;
class Orders;
class OrdersList;


class Player {

    public:
        Player(std::string playername, Hand* p_hand);
        Player(Hand* p_hand);
        ~Player();
        
        Player(const Player &p); // copy constructor
        Player& operator=(const Player &p); // assignment operator
        friend std::ostream& operator<<(std::ostream &out, const Player &p); // stream insertion operator
        
        
        std::vector<Territory*> toDefend(); // return owned territories
        std::vector<Territory*> toAttack(); // return Neutral and enemy territories

        void issueOrder(std::string);

        bool ownsTerritory(Territory *territory);

        std::deque<Orders*>& getOrders();
        Hand* getHand();
        std::string getName();

        int getReinforcementPool();
        void setReinforcementPool(int);

        void add_new_player_territory(Territory *territory);

        std::vector<std::string> getDiplomacyNames();
        void addDiplomacy(std::string name);
        void resetDiplomacy();
        
        bool getConquer();
        void setConquer(bool has_conquer);

    private:
        std::string player_Name;
        std::vector<Territory*> owned_territories; // Collection of territories owned by a player
        bool hasConquered;
        int reinforcementPool;
        std::vector<string> diplomacyPlayersName;
        Hand* player_hand;  // player hand
        OrdersList* player_orders; // List of orders
};
