#include <iostream>
#include "Player.h"
#include "../Orders/Orders.h"

using namespace std;

// g++ -std=c++17 Player.cpp PlayerDriver.cpp ../Map/Map.cpp ../Cards/Cards.cpp ../Orders/Orders.cpp
void testPlayers(){

    cout << "The code running is the PlayerDriver" << endl;

    Player *player1 = new Player("p1", new Hand());
    Player *player2 = new Player("p2", new Hand());


    Territory *territory1 = new Territory("T1");

    Territory *territory2 = new Territory("T2");
    Territory *territory3 = new Territory("T3");
    Territory *territory4 = new Territory("T4");

    Deploy *order1 = new Deploy(player1, "Deploy", territory1, 5);
    Advance *order2 = new Advance(player2, "Advance", territory2);
    Bomb *order3 = new Bomb(player1, "Bomb", territory3);
    Blockade *order4 = new Blockade(player2, "Blockade", territory4);

    player1->add_new_player_territory(territory1);
    player1->add_new_player_territory(territory3);

    player2->add_new_player_territory(territory2);
    player2->add_new_player_territory(territory4);


    cout << "\n\n" << player1->getName() << " must defend the territories:\n" << player1->toDefend();

    cout << "\n\n" << player2->getName() << " must defend the territories:\n" << player2->toDefend();

    cout << "\n\n" << player1->getName() << " must attack the territories:\n" << player1->toAttack();

    cout << "\n\n" << player2->getName() << " must attack the territories:\n" << player2->toAttack();



    
    cout << "Calling issueOrder:\n\n";
    player1->issueOrder(order1->getDescription());
    player1->issueOrder(order3->getDescription());
    player2->issueOrder(order2->getDescription());
    player2->issueOrder(order4->getDescription());

    cout << endl << player1->getName() <<"'s orders:" << endl;
	for (Orders* o : player1->getOrders()) {
		cout << *o << endl;
	}


    cout << endl << player2->getName() <<"'s orders:" << endl;
	for (Orders* o : player2->getOrders()) {
		cout << *o << endl;
	}


    cout << "\n\n" << player1->getName() << "has territories:\n" << player1->toDefend();
    cout << "\n\n" << player2->getName() << "has territories:\n" << player2->toDefend();


    delete player1; delete player2;
	delete territory1; delete territory2; delete territory3; delete territory4;
	delete order1; delete order2; delete order3; delete order4;


    player1 = nullptr; player2 = nullptr;
	territory1 = nullptr; territory2 = nullptr; territory3 = nullptr; territory4 = nullptr;
	order1 = nullptr; order2 = nullptr; order3 = nullptr; order4 = nullptr;
}


int main(){

    testPlayers();
    return 0;
}
