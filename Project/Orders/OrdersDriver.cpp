#include "Orders.h"
#include<iostream>

// You must be in Orders directory/folder to run this teminal log
// g++ -std=c++17 ../Player/Player.cpp ../Map/Map.cpp ../Cards/Cards.cpp Orders.cpp OrdersDriver.cpp


void testOrderExecution() {
    cout << "we will have two player with empty hand, player1 and player2" << endl;
    Player* player1 = new Player("p1", new Hand());
    Player* player2 = new Player("p2", new Hand());
    Player* neutralPlayer = new Player("Neutral", new Hand());

    cout << "4 territories from territory1 to 4" << endl;
    Territory* territory1 = new Territory("T1");
    Territory* territory2 = new Territory("T2");
    Territory* territory3 = new Territory("T3");
    Territory* territory4 = new Territory("T4");
    cout << "territories has 2 default army units each." << endl;
    territory1->adding_armies_number(2);
    territory2->adding_armies_number(2);
    territory3->adding_armies_number(2);
    territory4->adding_armies_number(2);
    cout << "map looks like this:" << endl << "territory1 =>territory2 =>territory3" << endl <<
        "\t\t||" << endl << "\t\t\\/" << endl<<"\tterritory4"<<endl;
    territory1->addAdjacency(territory2);
    territory2->addAdjacency(territory3);
    territory2->addAdjacency(territory4);

    cout << "player1 owns terrtory1, and player2 owns territory 3 and 4" << endl;
    player1->add_new_player_territory(territory1);
    neutralPlayer->add_new_player_territory(territory2);
    player2->add_new_player_territory(territory3);
    player2->add_new_player_territory(territory4);
    


    Deploy* DeployOrder1 = new Deploy(player1, "Deploy ->1 with 5", territory1, 5);
    Deploy* DeployOrder2 = new Deploy(player2, "Deploy ->4 with 5", territory4, 5);
    
    Advance* AdvanceOrder1 = new Advance(player1, "Advance 1->2", 5, territory1, territory2);
    Advance* AdvanceOrder2 = new Advance(player1, "Advance 2->1", 2, territory2, territory1);

    Bomb* BombOrder1 = new Bomb(player1, "Bomb ->3", territory3);
    Blockade* BlockadeOrder1 = new Blockade(player2, "Blockade ->4", territory4);
    Airlift* AirliftOrder1 = new Airlift(player2, "Airlift 4->3 with 3", 3, territory4, territory3);
    Negotiate* NegotiateOrder1 = new Negotiate(player1, "Negotiate p1->p2", player2);

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
    delete(orderList);
    std::cout<<"OK...let's pretending this is second turn..."<<std::endl;
    orderList = new OrdersList();
    Advance* AdvanceOrder21 = new Advance(player1, "Advance 1->2", 3, territory2, territory4);
    Advance* AdvanceOrder22 = new Advance(player2, "Advance 2->1", 4, territory3, territory2);
    orderList->addOrders(AdvanceOrder21, player1);
    orderList->addOrders(AdvanceOrder22, player2);
    for (auto it : orderList->getOrdersList()) {
        it->execute();
    }
    player1->resetDiplomacy();
    player2->resetDiplomacy();
    for (auto it : orderList->getOrdersList()) {
        it->execute();
    }
}

int main()
{
    std::cout<<"this is main function"<<std::endl;
    testOrderExecution();
    std::cout<<"this is main function after function"<<std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}
