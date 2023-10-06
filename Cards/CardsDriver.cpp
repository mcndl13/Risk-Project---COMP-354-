#include <iostream>
#include "Card.h"


using namespace std;

int main() {

	Card* card = new Card();		
	Player* player = new Player();	


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
	cout << *deck; // Print what's i nthe deck


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

	Hand* hand = new Hand(size_of_hand);		//Create an object hand

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


	cout << "\nThe player order list is as follows: " << player->getOrders();

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



	return 0;
}