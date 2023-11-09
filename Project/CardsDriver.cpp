#include <iostream>
#include "Cards.h"


// g++ -std=c++17 ../Player/Player.cpp CardsDriver.cpp ../Map/Map.cpp Cards.cpp ../Orders/Orders.cpp
using namespace std;

void testCards() {

    Card* card = new Card();		
	Player* player = new Player("p1", new Hand());

    Territory *territory1 = new Territory("T1");
    territory1->adding_armies_number(2);
    Territory *territory2 = new Territory("T2");
    Territory *territory3 = new Territory("T3");
    Territory *territory4 = new Territory("T4");

    Deploy *order1 = new Deploy(player, "Deploy", territory1, 5);
    Bomb *order3 = new Bomb(player, "Bomb", territory3);

    player->add_new_player_territory(territory1);
    player->add_new_player_territory(territory3);



// Creating a deck
	int size_of_deck;

	cout << "Enter number the max amount of cards allowed in the deck (between 5 and 30): ";
	cin >> size_of_deck;

	while (size_of_deck < 5 || size_of_deck > 30) {
		cout << "The number of cards you've entered is invalid. Please try again: ";
		cin >> size_of_deck;
	}



	cout << "\n----------------------------------------------------------\n\n";

	Deck* deck = new Deck(size_of_deck);	//Create a deck object
	cout << *deck; // Print what's in the deck


	Deck* copyDeck = new Deck(*deck);	//Copy constructor		
	Deck copyDeck2 = *deck;				//overloaded assignment operator




// Creating hand and drawing cars
	int size_of_hand;

	cout << "\nEnter number for the player's hand (at most 5): ";
	cin >> size_of_hand;


	while (size_of_hand > 5 || size_of_hand < 0) {
		cout << "The number of cards you've entered is invalid. Please try again: ";
		cin >> size_of_hand;
	}

	cout << "\n----------------------------------------------------------\n\n";

	Hand* hand = new Hand(size_of_hand); //Create an object hand

	cout << "# of cards a player can have is: " << hand->getSize() << '\n';

	while (!(hand->IsHandFull())) {
		hand->addCardToHand(deck->draw());	//Draws and add the drawn card to the hand
		cout << *deck << *hand;
	}



	Hand* copyHand = new Hand(*hand);	//Copy constructor
	Hand copyHand2 = *hand;				//Calls overloaded assignment operator


// Play()
	int index;

	cout << endl << "Enter the index of the card to play: ";
	cin >> index;

	card->play(hand, index, deck, player);
	cout << *deck << *hand;


    cout << endl << player->getName() <<"'s orders:" << endl;
	for (Orders* o : player->getOrders()) {
		cout << *o << endl;
	}


	cout << "\n----------------------------------------------------------\n\n";

	cout << "Original deck: " << *deck << "Memory address: " << &deck << '\n';
	cout << "\nOriginal hand: " << *hand << "Memory address: " << &hand << '\n';

	delete card;
	delete player;
	delete deck;
	delete hand;
	delete copyDeck;
	delete copyHand;

    // Avoid dangling pointers
	card = NULL;
	player = NULL;
	deck = NULL;
	hand = NULL;
	copyDeck = NULL;
	copyHand = NULL;

}

int main() {

	testCards();

	return 0;
}