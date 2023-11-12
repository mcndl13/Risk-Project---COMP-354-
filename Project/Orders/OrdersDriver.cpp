#include "Orders.h"
#include<iostream>
using namespace std;

// You must be in Orders directory/folder to run this teminal log
// g++ -std=c++17 ../Player/Player.cpp OrdersDriver.cpp ../Map/Map.cpp ../Cards/Cards.cpp Orders.cpp

void testOrdersLists (){

    cout << "The code running is the OrdersDriver" << endl;

    Player *player1 = new Player("p1", new Hand());
    Player *player2 = new Player("p2", new Hand());

    Territory *territory1 = new Territory("T1");
    territory1->adding_armies_number(2);
    Territory *territory2 = new Territory("T2");
    Territory *territory3 = new Territory("T3");
    Territory *territory4 = new Territory("T4");

    territory1->set_owning_player(player1);
    territory3->set_owning_player(player2);
    territory4->set_owning_player(player2);
    player1->add_new_player_territory(territory1);
    player2->add_new_player_territory(territory3);
    player2->add_new_player_territory(territory4);

    //couldn't do the test properly, because the territory is not adjacent now
    Deploy *DeployOrder1 = new Deploy(player1, "Deploy", territory1, 5);
    Deploy* DeployOrder2 = new Deploy(player2, "Deploy", territory4, 5);
    Airlift* AirliftOrder1 = new Airlift(player2, "Airlift", 3, territory4, territory3);
    Advance * AdvanceOrder1 = new Advance(player1, "Advance",5,territory1, territory2);
    Advance * AdvanceOrder2 = new Advance(player1, "Advance",2,territory2, territory1);
    
    Bomb * BombOrder1 = new Bomb(player1, "Bomb", territory3);
    Blockade * BlockadeOrder1 = new Blockade(player2, "Blockade", territory4);
    Negotiate* NegotiateOrder1 = new Negotiate(player1,"Negotiate",player2);

    OrdersList* orderList = new OrdersList();
    orderList->addOrders(DeployOrder1, player1);
    orderList->addOrders(DeployOrder2, player2);
    orderList->addOrders(AdvanceOrder1, player1);
    orderList->addOrders(AdvanceOrder2, player1);
    orderList->addOrders(BombOrder1, player1);
    orderList->addOrders(BlockadeOrder1, player2);
    orderList->addOrders(AirliftOrder1, player2);
    orderList->addOrders(NegotiateOrder1, player1);

    for (auto it : orderList->getOrdersList()) {
        it->execute();
    }

}

int main()
{
    //testOrdersLists();
    cout<<"2";
    return 0;
}
