#pragma once
#include <vector>
#include <deque>
#include <string>
#include "../Map/Map.h"

class Hand;
class Orders;
class OrdersList;
class Player;

enum Strategy_type{Human_player, Aggressive_player, Benevolent_player, Neutral_player, Cheater_player, Undefined};



// Abstract class
class PlayerStrategy{

    public:
        PlayerStrategy();
        PlayerStrategy(Strategy_type);
        PlayerStrategy(Player*);
        PlayerStrategy(const PlayerStrategy& toCopy);
        virtual ~PlayerStrategy();
        PlayerStrategy& operator=(const PlayerStrategy&);

        virtual void issueOrder() = 0;
        virtual std::vector<Territory*> toAttack() = 0; // Priority of territories to attack
        virtual std::vector<Territory*> toDefend() = 0; // which of their own territories are to be defended in priority
        Strategy_type getStrategyName() const { return strategyName;};
        Player* getPlayer();


    protected:

        Strategy_type player_strat;
        int armies_to_place;

        int armiesToPlace;
        Player* player;
        Territory* from;
        Territory* to;
        Strategy_type strategyName;


};


class HumanPlayerStrategy : public PlayerStrategy {

    public:
        HumanPlayerStrategy();
        HumanPlayerStrategy(const HumanPlayerStrategy&);
        ~HumanPlayerStrategy();
        HumanPlayerStrategy& operator=(const HumanPlayerStrategy&);

        void issueOrder() override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;


    private:



};





class AggressivePlayerStrategy : public PlayerStrategy {


    public:
        AggressivePlayerStrategy();
        AggressivePlayerStrategy(const AggressivePlayerStrategy&);
        ~AggressivePlayerStrategy();
        AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy&);

        void issueOrder() override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;
        

    private:

};




class BenevolentPlayerStrategy : public PlayerStrategy {

    public:
        BenevolentPlayerStrategy();
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy&);
        ~BenevolentPlayerStrategy();
        BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy&);

        void issueOrder() override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

    private:

};




class RandomPlayerStrategy : public PlayerStrategy {

    public:
        RandomPlayerStrategy();
        RandomPlayerStrategy(const RandomPlayerStrategy&);
        ~RandomPlayerStrategy();
        RandomPlayerStrategy& operator=(const RandomPlayerStrategy&);

        void issueOrder() override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

    private:

};



class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        CheaterPlayerStrategy();
        CheaterPlayerStrategy(const CheaterPlayerStrategy&);
        ~CheaterPlayerStrategy();
        CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy&);

        void issueOrder() override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

    private:
    
};
