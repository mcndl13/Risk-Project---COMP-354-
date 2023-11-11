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


    Deploy *order1 = new Deploy(player1, "Deploy", territory1, 5);
    Advance *order2 = new Advance(player2, "Advance",5, territory2,territory3);
    Bomb *order3 = new Bomb(player1, "Bomb", territory3);
    Blockade *order4 = new Blockade(player2, "Blockade", territory4);


    player1->add_new_player_territory(territory1);
    player1->add_new_player_territory(territory3);

    player2->add_new_player_territory(territory2);
    player2->add_new_player_territory(territory4);


    order1->execute();

}

int main()
{
    testOrdersLists();
    return 0;
}
