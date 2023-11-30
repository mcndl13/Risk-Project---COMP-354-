#include <iostream>
#include "PlayerStrategies.h"
using namespace std;




//=================== PlayerStrategy class =======================
PlayerStrategy::PlayerStrategy() {
    armiesToPlace = 0;
    this->player = nullptr;
    strategyName = Strategy_type::Undefined;
}

PlayerStrategy::PlayerStrategy(Player* player) {
    armiesToPlace = 0;
    this->player = player;
    strategyName = Strategy_type::Undefined;
}


PlayerStrategy::PlayerStrategy(const PlayerStrategy& copy) {
    armiesToPlace = copy.armiesToPlace;
    this->player = copy.player;
    strategyName = Strategy_type::Undefined;
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& player_strat) {
    armiesToPlace = player_strat.armiesToPlace;
    this->player = player_strat.player;
    strategyName = Strategy_type::Undefined;
}

PlayerStrategy::PlayerStrategy(Strategy_type st){
    this->strategyName = st;
}


//=================== Orders class =======================

HumanPlayerStrategy::HumanPlayerStrategy(){

    strategyName = Strategy_type::Human_player;
    this->armiesToPlace = 0;
    this->player = nullptr;

}