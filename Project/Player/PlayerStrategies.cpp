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

    std::cout << player->getName() << ", which order would you like to issue?\nList of possible orders:" << endl;


    // If some reinforcements are left in the pool of the player, he can only take deploy actions.
    if(player->hasReinforcements()){
        // Deploy
        std::cout << "0: Deploy " << endl;
        std::cout << "(You have " << player->getReinforcementPool() << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

        // Validate input.
        std::cout << "Enter 0: ";
        while(choiceNumber != 0)
            cin >> choiceNumber;
    }

    else{
        vector<int> possibleActions = vector<int>();


        bool advanceAllowed = false;

        // Checking if an advance can be done
        for(Territory* t : player->getPlayerTerritories()){
            if(t->get_number_of_armies() > 0)
                advanceAllowed = true;
        }

        if(advanceAllowed) {
            possibleActions.push_back(1);
            std::cout << "1: Advance" << endl;
        }

        if(player->hasCards()){
            possibleActions.push_back(2);
            std::cout << "2: Play a card" << endl;
        }

        // End turn
        possibleActions.push_back(3);
        std::cout << "3: End your turn." << endl;

        // Validate input.
        while(choiceNumber < 0 ||choiceNumber >= nbOfPossibleActions ||(std::find(possibleActions.begin(), possibleActions.end(), choiceNumber) == possibleActions.end())){
            cout << "Invalid entry, try gain: ";
            cin >> choiceNumber;
        }
    }

    switch(choiceNumber){

        // Deploy
        case 1:{
            
            // List the territories the player can choose
            std::cout << "In which territory would you like to deploy your troops?"<< endl;
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

            std::cout << "How many troops would you like to deploy? (" << player->getReinforcementPool() << " remaining in your reinforcement pool.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > player->getReinforcementPool()){
                cout << "Enter the number of reinforcements: ";
                cin >> troopNumber;
            }

            Deploy* deployOrder = new Deploy(player, "deploy", this->toDefend(player).at(territoryChoice - 1), troopNumber);
            player->addOrder(deployOrder);

            std::cout << "Deploy order issued." << endl;

            // Adjust the uncommitted reinforcement pool
            player->setReinforcementPool(player->getReinforcementPool() - troopNumber);
            break;
        }

        case 2:{
            // Advance

            std::cout << "From which territory would you like to select troops from?"<< endl;
            int counter, index = 0;
            for(Territory* t : this->toDefend(player))
            {
                // We can choose a starting point only if there are armies in it.
                if(t->get_number_of_armies() > 0){
                    std::cout << counter << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
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

            std::cout << "How many troops would you like to move? (" << sourceTerritory->get_number_of_armies() << " remaining in your territory.)" << endl;

            // Read input and validate it.
            int troopNumber = -1;
            while(troopNumber<0 || troopNumber > sourceTerritory->get_number_of_armies()){
                cout << "Enter the number of reinforcements: ";
                cin >> troopNumber;
            }

            // List the territories the player can choose to advance to
            std::cout << "To which territory would you like to advance your troops to?"<< endl;
            std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
            vector<Territory*> allDestinations;
            int counter2 = 0;

            std::cout << "Territories to attack: " << endl;
            for(Territory* t : this->toAttack(player))
            {
                if(sourceTerritory->borders_territory(t))
                {
                    std::cout << counter2 << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
                    counter2++;
                    allDestinations.push_back(t);
                }
            }

            std::cout << "Territories to defend: " << endl;
            for(Territory* t : this->toDefend(player))
            {
                if(sourceTerritory->borders_territory(t))
                {
                    std::cout << counter2 << ": " << t->getName() << " (" << t->get_number_of_armies() << " troops)" << endl;
                    counter2++;
                    allDestinations.push_back(t);
                }
            }

            int destinationIndex = -1;
            while(destinationIndex < 0 || destinationIndex > allDestinations.size())
                cin >> destinationIndex;

            Advance* advanceOrder = new Advance(player, "Advance", troopNumber, sourceTerritory, allDestinations.at(destinationIndex - 1));
            player->addOrder(advanceOrder);

            std::cout << "Advance order issued." << endl;
            break;

        }

        case 3:{
            // Play a card

            std::cout << "Which card would you like to play?" << endl;

            int counter = 1;
            std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();


            for(Card* c : player->getHand()->getPlayerHand()){
                cout << "Card #" << counter  << ": "<< c->getCardType() << endl;
                counter++;
            }


            // Read input and validate it.
            int cardChoice = -1;
            while(cardChoice < 0 || cardChoice > player->getHand()->getSize()){
                cout << "Enter the number of the card to play: ";
                cin >> cardChoice;
            }

            // Playing the card.
            Card* card = player->getHand()->getCardInHand(cardChoice - 1);

            std::cout << "Playing a card: " + card->getCardType() << endl;

            card->play(player->getHand(), cardChoice - 1, deck, player);

            break;
        }

        case 4:
            std::cout << "Ending turn." << endl;
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
