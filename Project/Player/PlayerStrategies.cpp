#include <iostream>
#include <random>
#include <map>
#include <vector>
#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

using namespace std;




//=================== PlayerStrategy class =======================

    // Consstructor
    PlayerStrategy::PlayerStrategy(){}

    // Destructor
    PlayerStrategy::~PlayerStrategy(){}

    // Helpers
    void PlayerStrategy::setStrategyType(string name){this->strategyName = name;}
    void PlayerStrategy::setCallingPlayer(Player* p){this->callingPlayer = p;}
    string PlayerStrategy::getStrategyType() const {return this->strategyName;}
    Player* PlayerStrategy::getCallingPlayer() const {return this->callingPlayer;}


    PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy &playerStrategy){
        this->strategyName = playerStrategy.strategyName;
        return *this;
    }

    ostream& operator<<(ostream& out, const PlayerStrategy &strategy){
        cout << "This player strategy is " << strategy << "\n";
    }

    PlayerStrategy::PlayerStrategy(const PlayerStrategy &playerStrategy) {
        this->setStrategyType(playerStrategy.strategyName);
    }





//=================== HumanPlayerStrategy class =======================

    // Default Constructor
    HumanPlayerStrategy::HumanPlayerStrategy(){this->setStrategyType("Human");}

    // Consstructor
    HumanPlayerStrategy::HumanPlayerStrategy(Player* p){
        this->setStrategyType("Human");

    }

    // Destructor
    HumanPlayerStrategy::~HumanPlayerStrategy(){}


    /**
     * Player can only attack adjancent territories that are not theirs. 
     * Hence find the adjancent territories of all territories owned by the calling player.
    */
    vector<Territory*> HumanPlayerStrategy::toAttack(Player* player) {

        vector<Territory*> territoriesToAttack = vector<Territory*>();

        // Loop through all player territories
        for(Territory* t : player->getPlayerTerritories()){

            // Find every adjacent territory
            for(Territory* adj : t->getAdjacencies()){

                // If the players doesn't own territory
                if(adj->get_owning_player() != player)
                    territoriesToAttack.push_back(adj);
            }
        }
        return territoriesToAttack;
    }




    vector<Territory*> HumanPlayerStrategy::toDefend(Player* player) {
        return player->getPlayerTerritories();
    }






    bool HumanPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap, const vector<Player*> gamePlayers) {

    int nbOfPossibleActions = 4;
    int choiceNumber = -1;

    cout << player->getName() << ", which order would you like to issue?\nList of possible orders:" << endl;


    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(player->hasReinforcements()){
        // Deploy
        cout << "0: Deploy " << endl;
        cout << "(You have " << player->getReinforcementPool() << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

        // Validate input.
        cout << "Enter 0: ";
        while(choiceNumber != 0)
            cin >> choiceNumber;
    }

    else{
        vector<int> possible_actions = vector<int>();

        bool canAdvance = false;

        // Checking if an advance can be done
        for(Territory* t : player->getPlayerTerritories()){
            if(t->get_number_of_armies() > 0)
                canAdvance = true;
        }

        if(canAdvance) {
            possible_actions.push_back(1);
            cout << "1: Advance" << endl;
        }

        if(player->hasCards()){
            possible_actions.push_back(2);
            cout << "2: Play a card" << endl;
        }

        // End turn
        possible_actions.push_back(3);
        cout << "3: End your turn." << endl;

        // Validate input.
        while(choiceNumber < 0 ||choiceNumber >= nbOfPossibleActions ||(find(possible_actions.begin(), possible_actions.end(), choiceNumber) == possible_actions.end())){
            cout << "Invalid entry, try gain: ";
            cin >> choiceNumber;
        }
    }

    switch(choiceNumber){

        // Deploy
        case 1:{
            
            // List the territories the player can choose
            cout << "In which territory would you like to deploy your troops?"<< endl;
            int counter = 0;


            cout << "Possible territories of deployment:\n";
            for(Territory* t: player->toDefend()){
                cout<< counter << ". "  << t->getName() << " (" << t->get_number_of_armies() << " troops stationed)" << endl;
                counter++;
            }

            // Read input and validate it.
            int territoryChoice = -1;
            while(territoryChoice < 0 || territoryChoice > this->toDefend(player).size()){
                cout << "Enter the index of the target territory: ";
                cin >> territoryChoice;
            }

            cout << "How many troops would you like to deploy? (" << player->getReinforcementPool() << " remaining in your reinforcement pool.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > player->getReinforcementPool()){
                cout << "Enter the number of reinforcements: ";
                cin >> troopNumber;
            }

            Deploy* deployOrder = new Deploy(player, "deploy", this->toDefend(player).at(territoryChoice - 1), troopNumber);
            player->addOrder(deployOrder);

            cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool
            player->setReinforcementPool(player->getReinforcementPool() - troopNumber);
            break;
        }

        case 2:{

            // Advance
            cout << "From which territory would you like to select troops from?"<< endl;
            int counter, index = 0;
            for(Territory* t : this->toDefend(player))
            {
                // We can choose a starting point only if there are armies in it.
                if(t->get_number_of_armies() > 0){
                    cout << counter << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
                    counter++;
                }
            }

            // Read input and validate it.
            int index_of_target_territory = -1;

            while(index_of_target_territory<0 || index_of_target_territory > this->toDefend(player).size()){
                cout << "Enter the index of the target territory: ";
                cin >> index_of_target_territory;
            }

            Territory* sourceTerritory = this->toDefend(player).at(index_of_target_territory);

            cout << "How many troops would you like to move? (" << sourceTerritory->get_number_of_armies() << " remaining in your territory.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > sourceTerritory->get_number_of_armies()){
                cout << "Enter the number of reinforcements: ";
                cin >> troopNumber;
            }

            // List the territories the player can choose to advance to
            cout << "To which territory would you like to advance your troops to?"<< endl;
            map<int, Territory*> possible_Territories = map<int, Territory*>();
            vector<Territory*> allDestinations;
            int counter2 = 0;

            cout << "Territories to attack: " << endl;
            for(Territory* t : this->toAttack(player))
            {
                if(sourceTerritory->borders_territory(t))
                {
                    cout << counter2 << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
                    counter2++;
                    allDestinations.push_back(t);
                }
            }

            cout << "Territories to defend: " << endl;
            for(Territory* t : this->toDefend(player))
            {
                if(sourceTerritory->borders_territory(t))
                {
                    cout << counter2 << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
                    counter2++;
                    allDestinations.push_back(t);
                }
            }

            int destinationIndex = -1;
            while(destinationIndex < 0 || destinationIndex > allDestinations.size())
                cin >> destinationIndex;

            Advance* advanceOrder = new Advance(player, "Advance", troopNumber, sourceTerritory, allDestinations.at(destinationIndex - 1));
            player->addOrder(advanceOrder);

            cout << "Advance order issued." << endl;
            break;

        }

        case 3:{

            // Play a card
            cout << "Which card would you like to play?" << endl;

            int counter = 1;

            for(Card* c : player->getHand()->getPlayerHand()){
                cout << "Card #" << counter  << ": "<< c->getCardType() << endl;
                counter++;
            }


            // Read input and validate.
            int cardChoice = -1;
            while(cardChoice < 0 || cardChoice > player->getHand()->getSize()){
                cout << "Enter the number of the card to play: ";
                cin >> cardChoice;
            }

            // Playing the card.
            Card* card = player->getHand()->getCardInHand(cardChoice - 1);

            cout << "Playing a card: " + card->getCardType() << endl;

            card->play(player->getHand(), cardChoice - 1, deck, player);

            break;
        }

        case 4:
            cout << "Ending turn." << endl;
            return false;

        default:
            cout << "Invalid action chosen for a player's turn.";
    }
    return true;
}





    HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy &HumanPlayerStrategy){
        this->setStrategyType(HumanPlayerStrategy.getStrategyType());
        return *this;
    }

    ostream& operator<<(ostream& out, const HumanPlayerStrategy &strategy){
        cout << "This player strategy is " << strategy << "\n";
    }

    HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &HumanPlayerStrategy) {
        this->setStrategyType(HumanPlayerStrategy.getStrategyType());
    }

    
    HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &strategy) {
        this->setStrategyType(strategy.getStrategyType());
    }

    ostream &operator<<(ostream &out, const HumanPlayerStrategy &strategy) {
        return out << strategy.getStrategyType();
    }

    HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &strategy) {

            this->setStrategyType(strategy.getStrategyType());
        
        return *this;
    }






//=================== PlayerStrategy class =======================
    AggressivePlayerStrategy::AggressivePlayerStrategy() {
        setStrategyType("Aggressive");
        strongest_territory = nullptr;
        canAdvance = true;
    }

    AggressivePlayerStrategy::~AggressivePlayerStrategy() {
        strongest_territory = nullptr;
    }


    Territory* AggressivePlayerStrategy::get_strongest_territory() {
        return strongest_territory;
    }


    void AggressivePlayerStrategy::set_strongest_territory(Player* player) {
        
        this->strongest_territory = player->getPlayerTerritories().at(0);

        for (int i = 0; i < player->getPlayerTerritories().size(); i++) {
            if (this->strongest_territory->get_number_of_armies() < player->getPlayerTerritories().at(1)->get_number_of_armies())
                this->strongest_territory = player->getPlayerTerritories().at(i);
        }
    }



    vector<Territory*> AggressivePlayerStrategy::toDefend(Player *player) {
        return player->getPlayerTerritories();
    }

    vector<Territory*> AggressivePlayerStrategy::toAttack(Player *player) {

        vector<Territory*> territoriesToAttack = vector<Territory*>();

        // Loop through all player territories
        for(Territory* t : player->getPlayerTerritories()){

            // Find every adjacent territory
            for(Territory* adj : t->getAdjacencies()){

                // If the players doesn't own territory
                if(adj->get_owning_player() != player)
                    territoriesToAttack.push_back(adj);
            }
        }
        return territoriesToAttack;
    }

    
    
    
    bool AggressivePlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap,const vector<Player*> gamePlayers) {
        
        int actionNumber = -1;


        // Seed the random number generator
        random_device rd;
        mt19937 generator(rd());

  
        
        set_strongest_territory(player);


        if (player->getReinforcementPool() > 0) {
            canAdvance = true;
            cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
            // Deploy
            actionNumber = 0;
        } 
        
        
        else {
            vector<int> possible_actions = vector<int>();

            // Advance
            if (canAdvance) {
                possible_actions.push_back(1);
            }

            // Play a card
            if(player->getHand()->getSize() > 0)
                possible_actions.push_back(2);

            // End turn
            possible_actions.push_back(3);

            // Generate a random input
            uniform_int_distribution<int> distribution(0, possible_actions.size() - 1);

            int random_number = distribution(generator);
        }

        // Depending on which action was chosen, create an appropriate order.
        switch (actionNumber) {

            // Deploy
            case 0: {


                // Generate a random input
                uniform_int_distribution<int> distributionTroops(1, player->getReinforcementPool());
                int troopNumber = distributionTroops(generator);

                Deploy *deployOrder = new Deploy(player, "Deploy", strongest_territory, troopNumber);
                player->addOrder(deployOrder);

                cout << "Deploy order issued." << endl;

                // Adjust the uncommitted reinforcement pool.
                player->setReinforcementPool(player->getReinforcementPool() - troopNumber);
                break;
            }

            // Advance
            case 1: {


                // Choosing a starting point. Advances to enemy territories until it cannot do so anymore
                for (int i = 0; i < toDefend(player).size(); i++) {
                    int sourceTerritoryIndex = i;

                    Territory* sourceTerr = toDefend(player).at(sourceTerritoryIndex);
                    Territory* target = nullptr;


                    int troopNumber = sourceTerr->get_number_of_armies();

                    if (troopNumber > 0) {
                        
                        // Choose a territory for the player to advance to.
                        vector <Territory*> possible_Territories;
                        vector<int> possible_index = vector<int>();
                        int counter2 = 0;

                        for (int j = 0; j < sourceTerr->getAdjacencies().size(); j++) {
                            target = sourceTerr->getAdjacencies().at(j);
                            
                            // Check if adjance territory is neutral or owned by another player
                            if (target->get_owning_player() == nullptr || player->getName() != target->getName()){

                                possible_Territories[counter2] = target;
                                // possible_index.push_back(counter2);
                                counter2++;
                            }
                        }


                        // If the adjacent territories of the sourceTerr territory are already owned by the current player
                        if (possible_Territories.size() == 0) {

                            if (sourceTerr->getName() == strongest_territory->getName()) {

                                uniform_int_distribution<int> distributionDestination(0,strongest_territory->getAdjacencies().size() -1);
                                int targetIndex = distributionDestination(generator);
                                
                                Advance *advanceOrder = new Advance(player, "Advance" ,troopNumber, sourceTerr,strongest_territory->getAdjacencies()[targetIndex]);
                                player->addOrder(advanceOrder);
                            }
                            else{
                                Advance *advanceOrder = new Advance(player, "Advance" ,troopNumber, sourceTerr,strongest_territory);
                                player->addOrder(advanceOrder);
                            }

                        } else {
                            uniform_int_distribution<int> distributionDestination(0, possible_Territories.size() - 1);
                            int targetIndex = distributionDestination(generator);

                            Advance *advanceOrder = new Advance(player, "Advance" ,troopNumber, sourceTerr,possible_Territories[targetIndex]);
                            player->addOrder(advanceOrder);
                        }
                    }
                }
                canAdvance = false;
                break;
            }

            // Play a card
            case 2: {

                int counter = 1;
                map<int, Card *> cardsToNumbers = map<int, Card *>();


                for(Card* c : player->getHand()->getPlayerHand()){
                    cout << "Card #" << counter  << ": "<< c->getCardType() << endl;
                    counter++;
                }

                // Generate a random input
                if (counter > 0) {
                    uniform_int_distribution<int> distribution(0, player->getHand()->getSize() - 1);
                    int cardChoice = distribution(generator);

                    // Playing the card.
                    Card *card = player->getHand()->getCardInHand(cardChoice);

                    cout << "Playing a card: " + card->getCardType()<< endl;
                    card->play(player->getHand(), cardChoice,  deck, player);
                }
                break;
            }
            case 3:
                // End Turn
                cout << "Ending turn.\n" << endl;
                return false;

            default:
                cout << "Invalid action chosen for a player's turn.";
        }

                return true;
        }

    AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &strategy) {
        strongest_territory = strategy.strongest_territory;
        canAdvance = strategy.canAdvance;
    }

    ostream &operator<<(ostream &out, const AggressivePlayerStrategy &strategy) {
        return out << strategy.getStrategyType() << " canAdvance: " << strategy.canAdvance << " strongest_territory: " << strategy.strongest_territory->getName();
    }

    AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &strategy) {

        strongest_territory = nullptr;
        strongest_territory = strategy.strongest_territory;
        canAdvance = strategy.canAdvance;
        setStrategyType(strategy.getStrategyType());
        
        return *this;
    }
