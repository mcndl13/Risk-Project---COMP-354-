#include <iostream>
#include "Player.h"

void testPlayers() {
    Player playerA("Player A");
    Player playerB("Player B");

    // Test player functionality
    playerA.toDefend();
    playerB.toAttack();

    OrderList* myOrder = new OrderList(); // Create an order object
    player1.issueOrder(myOrder);

    std::cout << "Player A wants to defend these territories: ";
    for (Territory* territory : playerA.toDefend()) {
        std::cout << territory->getName() << " ";
    }

    std::cout << "Player B wants to attack these territories: ";
    for (Territory* territory : player2.toAttack()) {
        std::cout << territory->getName() << " ";
    }
}

int main() {
    testPlayers();
    return 0;
}
