#pragma once
#include <vector>
#include <deque>
#include <string>
#include "../Map/Map.h"

class Hand;
class Orders;
class OrdersList;
class PlayerStrategy;

class GameEngine;


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
        void issueOrder(GameEngine*);

        bool ownsTerritory(Territory *territory);

        std::deque<Orders*>& getOrders();
        Hand* getHand();
        std::string getName();
        int getReinforcementPool();
        std::vector<Territory*> getPlayerTerritories();

        void setReinforcementPool(int);

        void add_new_player_territory(Territory *territory);
        std::vector<std::string> getDiplomacyNames();
        void addDiplomacy(std::string name);
        void resetDiplomacy();
        Orders* getNextOrder();
        bool isDoneIssuingOrders();
        bool hasCards();
        bool hasReinforcements();
        void AddReinforcementPool(int);
        bool ownsAllTerritoriesInContinent(Continent*);
        void resetForNextTurn();

        void addOrder(Orders*);
        void changeStrategy();
        PlayerStrategy* getPlayerStartegy();

        void setStrategy (PlayerStrategy*);


        bool getConquer();
        void setConquer(bool has_conquer);

    private:
        std::string player_Name;
        std::vector<Territory*> owned_territories; // Collection of territories owned by a player
        std::vector<std::string> diplomacyPlayersName;

        bool hasConquered;
        int reinforcementPool;
        Hand* player_hand;  // player hand
        OrdersList* player_orders; // List of orders
        PlayerStrategy* player_strategy; // Determines if the player will be Human, Aggressive, Benevolent, Neutral, Cheater

};
