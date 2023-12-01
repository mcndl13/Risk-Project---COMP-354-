#include <iostream>
#include "PlayerStrategies.h"
using namespace std;




//=================== PlayerStrategy class =======================



//=================== Orders class =======================

HumanPlayerStrategy::HumanPlayerStrategy(){

    strategy_type = "Human";

}

bool HumanPlayerStrategy::issueOrder(Player *player, Deck* deck, Map* territoriesMap, const std::vector<Player*> gamePlayers){
    std::cout<<"\nWhat order do you want to issue?\n"<<
    "a. Deploy. b. Advance. c. Play a card.\n\nPlease enter one letter as your choise:"<<std::endl;
    char playerInput;
    std::cin>>playerInput;
    if(player->getConquer()){
        player->getHand()->addCardToHand(deck->draw());
        player->setConquer(false);
    }
    if(playerInput=='c'){
        std::cout<<"\nPlease choose a card in your hand:\n";
        Hand* playerHand = player->getHand();
        for(int i=0;i<playerHand->getSize();i++){
            playerHand->getPlayerHand();
        }
        
    }
}


CheaterPlayerStrategy::CheaterPlayerStrategy(){
    strategy_type = "Cheater";
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
    for(auto it : player->toDefend()){//get all owned territory
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
    for(auto it : player->toDefend()){
        for(auto _it : it->getAdjacencies()){
            if(!(player->ownsTerritory(_it))){
                listToReturn.push_back(it);
                break;
            }
        }
    }
    return listToReturn;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(){
    strategy_type = "Benevolent";
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack(Player *player) {return;}//play defensive

std::vector<Territory*> BenevolentPlayerStrategy::toDefend(Player *player){//put territories that are adjacent to enemy territory into list
    std::vector<Territory*> listToReturn;
    for(auto it : player->toDefend()){
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
    stress_list = set_List_of_weakest_territories(player);

}



//Helpers 
// Territory* BenevolentPlayerStrategy::get_weakest_territory(){
//     return weakest_territory;
// }
void BenevolentPlayerStrategy::negotiate(Player *player, Deck *deck){
    //TODO
}
void BenevolentPlayerStrategy::airlift(Player *player, Deck *deck){
    vector<Card*> handOfCard = player->getHand()->getPlayerHand();//get the hand of cards
    for(int i =0; i<handOfCard.size()-1;i++){//loop through cards
        if(handOfCard[i]->getCardType() == "Airlift"){//check if we have airlift card
            if(stress_list.size()>1){//if yes, check if we have more than two territories
                handOfCard[i]->play(player->getHand(),i,deck,player);//if yes, play the card
                //play the airlift card, isuure a airlift order, below are the parameter that the order will need
                Territory* sourceTerr = stress_list[0].first;
                int army_To_lift = stress_list[0].second;
                Territory* targetTerr = weakest_territory;
                Orders* airlift = new Airlift(player, "Airlift from benevolent",army_To_lift,sourceTerr,targetTerr);
                player->issueOrder(airlift,player);
                
            }
        }
    }
}

Territory* BenevolentPlayerStrategy::set_weakest_territory(Player* player){
    pair<Territory*,int> stressOnTerr ={nullptr,0};
    int tempStress = 0;
    for(auto it: BenevolentPlayerStrategy::toDefend(player)){//looping todefend list
            for(auto _it : it->getAdjacencies()){//for each to defend, loop adjacent territories for army number
                if(!player->ownsTerritory(_it)){//check if it is enmeny 
                    tempStress+=_it->get_number_of_armies();//if yes, add army number to stress
                }
            }
            if(tempStress>stressOnTerr.second){
                stressOnTerr = {it,tempStress};
            }
            tempStress = 0;//reset stress for next loop
    }
    return stressOnTerr.first;
}

std::vector<std::pair<Territory*, int>> BenevolentPlayerStrategy::set_List_of_weakest_territories(Player* player){
    std::vector<std::pair<Territory*, int>> stressList;
    int tempStress = 0;
    for(auto it: player->toDefend()){//looping owned list
            for(auto _it : it->getAdjacencies()){//for each to defend, loop adjacent territories for army number
                if(!player->ownsTerritory(_it)){//check if it is enmeny 
                    tempStress+=_it->get_number_of_armies();//if yes, add army number to stress
                }
            }
            tempStress-=it->get_number_of_armies();
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