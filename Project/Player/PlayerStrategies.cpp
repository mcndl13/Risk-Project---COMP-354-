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






//=================== AggressivePlayerStrategy class =======================
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


//=================== CheaterPlayerStrategy class =======================
CheaterPlayerStrategy::CheaterPlayerStrategy(){
    setStrategyType("Cheater");
}

bool CheaterPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap, const std::vector<Player*> gamePlayers){
    CheckForBonusCard(player,deck );
    for(auto it : CheaterPlayerStrategy::toAttack(player)){
        player->add_new_player_territory(it);
        std::cout<<"\nCheater takes a territory "<<it->getName()<<std::endl;
    }
}
std::vector<Territory*> CheaterPlayerStrategy::toAttack(Player *player){//push every adjacent territory that does not belong to cheater in the list
    std::vector<Territory*> listToReturn;
    for(auto it : player->getPlayerTerritories()){//get all owned territory
        for(auto _it : it->getAdjacencies()){//for each owned territory, get its adjacent territories
            if(!(player->ownsTerritory(_it))){//if owns
                listToReturn.push_back(_it);//push in
            }
        }
    }
    return listToReturn;
}
void CheckForBonusCard(Player *player, Deck* deck){//could put in Player.h or playerStrategy.h, should be called every turn.
    if(player->getConquer()){//if player conquered a territory last turn, 
        player->getHand()->addCardToHand(deck->draw());//give him/her/they a new card
        player->setConquer(false);//reset conquer boolean
    }
}
std::vector<Territory*> CheaterPlayerStrategy::toDefend(Player *player){//put territories that are adjacent to enemy territory into list
    std::vector<Territory*> listToReturn;
    for(auto it : player->getPlayerTerritories()){
        for(auto _it : it->getAdjacencies()){
            if(!(player->ownsTerritory(_it))){
                listToReturn.push_back(it);
                break;
            }
        }
    }
    return listToReturn;
}
//=================== BenevolentPlayerStrategy class =======================
BenevolentPlayerStrategy::BenevolentPlayerStrategy(){
    setStrategyType("Benevolent");
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack(Player *player) {return;}//play defensive

std::vector<Territory*> BenevolentPlayerStrategy::toDefend(Player *player){//put territories that are adjacent to enemy territory into list
    std::vector<Territory*> listToReturn;
    for(auto it : player->getPlayerTerritories()){
        for(auto _it : it->getAdjacencies()){
            if(!(player->ownsTerritory(_it))){
                listToReturn.push_back(it);
                break;
            }
        }
    }
    return listToReturn;
}

bool BenevolentPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap, const std::vector<Player*> gamePlayers) {
    CheckForBonusCard(player,deck);//probably will not give card here
    weakest_territory = set_weakest_territory(player);
    //random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<int> dis(1, player->getReinforcementPool());
    int randomValue = dis(gen);
    //end of random number
    Orders* deploy = new Deploy(player, "deploy from Benevolent player", weakest_territory, randomValue);//deploy a random number of army units to the weakest
    player->issueOrder(deploy,player);
    //advance from strong to weak
    stress_list = set_List_of_weakest_territories(player);
    airlift(player, deck);//check if it is possible to play airlift
    for(auto it:  stress_list){
        Territory* currTerr = it.first;
        Territory* tarTerr;
        int maxStress =it.second;
        for(auto _it : currTerr->getAdjacencies()){
            if(player->ownsTerritory(_it)){
                auto __it = std::find_if(stress_list.begin(), stress_list.end(),
                           [&_it](const auto& pair) {
                               return pair.first == _it;
                           });//to find Territory* in a vector<std::pair<Territory*,int>>
                if (__it != stress_list.end()) {//if found
                    //std::cout << "Territory found in the  " << __it->first->getName() << std::endl;
                    if(maxStress<__it->second){//if the stress is bigger there, target will be it
                        maxStress = __it->second;
                        tarTerr = __it->first;
                    }
                } else {
                    std::cerr << "Territory not found in the weak list, this is in a loop inside issureOrder in PlayerStrategies." << std::endl;
                }
            }
        }
        //advance army and next loop
        if(maxStress!=it.second){//if self is the most stressed, do nothing.
            Orders* advance = new Advance(player, "advance from Benevolent Player", currTerr->get_number_of_armies(),currTerr,tarTerr);
            player->issueOrder(advance,player);
        }
        
    }
    stress_list = set_List_of_weakest_territories(player);//recheck the stress
    negotiate(player, deck);//check if negotiate is available
}



//Helpers 
// Territory* BenevolentPlayerStrategy::get_weakest_territory(){
//     return weakest_territory;
// }
void BenevolentPlayerStrategy::negotiate(Player *player, Deck *deck){
    std::cout<<"\nBenevolent player is checking his hand for a negotiate card.\n";
    vector<Card*> handOfCard = player->getHand()->getPlayerHand();//get the hand of cards
    for(int i =0; i<handOfCard.size()-1;i++){//loop through cards
        if(handOfCard[i]->getCardType() == "Diplomacy"){//check if we have airlift card
            if(stress_list.size()>0){//if yes, check if we have more than one
                handOfCard[i]->play(player->getHand(),i,deck,player);//if yes, play the card
                //play the airlift card, isuure a airlift order, below are the parameter that the order will need
                pair<Player*, int> playerWithPower = std::make_pair(nullptr, 0);//fisrt is player and second is power
                for (auto it : weakest_territory->getAdjacencies())//check the weakest's adjacencies
                {
                    if(playerWithPower.second<it->get_number_of_armies()){//to get the biggest army number territory and 
                        playerWithPower = std::make_pair(it->get_owning_player(), it->get_number_of_armies());
                    }
                }
                std::cout<<"\nBenevolent player is playering a negotiate card.\n";
                Orders* negotiateOrder = new Negotiate(player, "Negotiate from benevolent", playerWithPower.first);
                player->issueOrder(negotiateOrder,player);//still need to be excuted in main function with a loop
                return;
            }
        }
    }
    std::cout<<"\nBenevolent player has fiald to find the negotiate card.\n";
}
void BenevolentPlayerStrategy::airlift(Player *player, Deck *deck){
    std::cout<<"\nBenevolent player is checking his hand for an airlift card.\n";
    vector<Card*> handOfCard = player->getHand()->getPlayerHand();//get the hand of cards
    for(int i =0; i<handOfCard.size()-1;i++){//loop through cards
        if(handOfCard[i]->getCardType() == "Airlift"){//check if we have airlift card
            if(stress_list.size()>1){//if yes, check if we have more than two territories
                handOfCard[i]->play(player->getHand(),i,deck,player);//if yes, play the card
                //play the airlift card, isuure a airlift order, below are the parameter that the order will need
                Territory* sourceTerr = stress_list[0].first;
                int army_To_lift = sourceTerr->get_number_of_armies();
                Territory* targetTerr = weakest_territory;
                std::cout<<"\nBenevolent player is playing an airlift card.\n";
                Orders* airlift = new Airlift(player, "Airlift from benevolent",army_To_lift,sourceTerr,targetTerr);
                player->issueOrder(airlift,player);//still need to be excuted in main function with a loop
                return;
            }
        }
    }
    std::cout<<"\nBenevolent player has fiald to find the airlift card.\n";
}

Territory* BenevolentPlayerStrategy::set_weakest_territory(Player* player){
    pair<Territory*,int> stressOnTerr =std::make_pair(nullptr,0);
    int tempStress = 0;
    for(auto it: BenevolentPlayerStrategy::toDefend(player)){//looping todefend list
            for(auto _it : it->getAdjacencies()){//for each to defend, loop adjacent territories for army number
                if(!player->ownsTerritory(_it)){//check if it is enmeny 
                    tempStress+=_it->get_number_of_armies();//if yes, add army number to stress
                }
            }
            if(tempStress>stressOnTerr.second){
                stressOnTerr = std::make_pair(it,tempStress);
            }
            tempStress = 0;//reset stress for next loop
    }
    return stressOnTerr.first;
}

std::vector<std::pair<Territory*, int>> BenevolentPlayerStrategy::set_List_of_weakest_territories(Player* player){
    std::vector<std::pair<Territory*, int>> stressList;
    int tempStress = 0;
    for(auto it: player->getPlayerTerritories()){//looping owned list
            for(auto _it : it->getAdjacencies()){//for each to defend, loop adjacent territories for army number
                if(!player->ownsTerritory(_it)){//check if it is enmeny 
                    tempStress+=_it->get_number_of_armies();//if yes, add army number to stress
                }
            }
            tempStress-=it->get_number_of_armies();
            if(tempStress==it->get_number_of_armies()){
                tempStress-=10;
            }
            stressList.push_back(std::make_pair(it,tempStress));
            tempStress = 0;//reset stress for next loop
    }
    // Define a custom comparison function or use a lambda expression
    auto compareBySecond = [](const auto& a, const auto& b) {
        return a.second < b.second;
    };

    // Sort the vector based on the int value
    std::sort(stressList.begin(), stressList.end(), compareBySecond);

    return stressList;
}

