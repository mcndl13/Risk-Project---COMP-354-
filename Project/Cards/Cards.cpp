#include<iostream>
#include <cstdlib>
#include <ctime> // For random
#include <time.h>
#include "../Orders/Orders.h"
#include "Cards.h"
// #include "Player.h"
// #include "Order.h"


using namespace std;

// Card

    // Default constructor
    Card::Card(){
        card_type = "Default";
    }

    // Parameterized Constructor
    Card::Card(cardType type) {

        if (type == cardType::Bomb){
            card_type = "Bomb";
        }

        else if (type == cardType::Reinforcement){
            card_type = "Reinforcement";
        }


        else if (type == cardType::Blockade){
            card_type = "Blockade";
        }


        else if (type == cardType::Airlift){
            card_type = "Airlift";
        }

        else{
            card_type = "Diplomacy";
        }
    }

    // Copy constructor
    Card::Card(const Card & card){
        card_type = card.card_type;
    }


    Card& Card::operator=(const Card& Card){
        this->card_type = Card.card_type;

        return *this;
    }





    /**
        1. Checks if the index given is valid for the collection of cards in the player's hand
        2. Get the specified card to play from the hand
        3. Creat an order and add that card to the order
        4. Remove card from hand
        5. Push back card onto the deck
    */
    void Card::play(Hand* hand, int index, Deck* deck, Player * player){

        cout << "\n\n1\n\n";

        if(!checkIndex(hand->getPlayerHand(), index)){
            cout << "The index you have entered, " << index << " is invalid.\n Terminating program." << endl;
            exit(1);
        }

        cout << "\n\n2\n\n" << "index" << to_string(index);



        // Get the card to play in the card pointer
        Card* card_to_play = hand ->getCardInHand(index);

                cout << "\n\n3\n\n" << "index" << to_string(index);

        // Get the card type to play and create a new order
        Orders* new_order = new Deploy(player, hand->getCardInHand(index)->getCardType(), nullptr, 5);

                cout << "\n\n4\n\n" << "index" << to_string(index);


                cout << "\n\n5\n\n" << "index" << to_string(index);

        // Remove card from hand (cards_in_hand vector)
        hand->removeCardFromHand(index);

                cout << "\n\n6\n\n" << "index" << to_string(index);

        // return card back into the deck
        deck->addCardToDeck(card_to_play);
    }



    // Get the type of the card
    string Card::getCardType(){return card_type;}



    // Checking if the index given is valid for the cards in the player's hand
    bool Card::checkIndex(vector<Card*> vector, int index){
    cout << "Executing checkIndex()";
        if ((index >= vector.size()) || index < 0)
            return false;
        return true;
    }


    // Printing a collection of card
    ostream& operator<< (ostream& out, const vector<Card*> cards) {
        for (int i = 0; i < cards.size(); i++) {
            out << "-  " <<cards[i]->getCardType();
            out << "\n"; 
        }
        out << "\n\n";

        //Printing format: [ car1, car2, car3 ]
        return out;
    }


    // overloading output stream operator cards
    ostream& operator<< (ostream& out, const Card& card){

        out << "The card's type/name is: " << card.card_type;
        return out;
    }





// Deck

    //Default constructor
    Deck::Deck(){
        sizeDeck = 15;
        
        cout << "\nCreating a default deck..." << '\n';

        //Default deck has 5 cards, and we have 5 different types of cards
        deck_cards.push_back(new Card(Card::cardType::Bomb));
        deck_cards.push_back(new Card(Card::cardType::Blockade));
        deck_cards.push_back(new Card(Card::cardType::Reinforcement));
        deck_cards.push_back(new Card(Card::cardType::Airlift));
        deck_cards.push_back(new Card(Card::cardType::Diplomacy));

        deck_cards.push_back(new Card(Card::cardType::Bomb));
        deck_cards.push_back(new Card(Card::cardType::Blockade));
        deck_cards.push_back(new Card(Card::cardType::Reinforcement));
        deck_cards.push_back(new Card(Card::cardType::Airlift));
        deck_cards.push_back(new Card(Card::cardType::Diplomacy));

        deck_cards.push_back(new Card(Card::cardType::Bomb));
        deck_cards.push_back(new Card(Card::cardType::Blockade));
        deck_cards.push_back(new Card(Card::cardType::Reinforcement));
        deck_cards.push_back(new Card(Card::cardType::Airlift));
        deck_cards.push_back(new Card(Card::cardType::Diplomacy));
    }


    // Parameterized constructor
    Deck::Deck(int size){
        sizeDeck = size;

        int morecards = size -  5;
        
        cout << "\nCreating a default deck..." << '\n';

        //Default deck has 5 cards, and we have 5 different types of cards
        deck_cards.push_back(new Card(Card::cardType::Bomb));
        deck_cards.push_back(new Card(Card::cardType::Blockade));
        deck_cards.push_back(new Card(Card::cardType::Reinforcement));
        deck_cards.push_back(new Card(Card::cardType::Airlift));
        deck_cards.push_back(new Card(Card::cardType::Diplomacy));

        // In the case that the size is larger than 5  
        for (int i = 0; i < morecards; i++){
            
            // While be a random number between 1 - 5
            int random = rand() % 4 + 1;

            if(random == 1)
                deck_cards.push_back(new Card(Card::cardType::Bomb));
            

            if (random == 2)
                deck_cards.push_back(new Card(Card::cardType::Blockade));
            

            if (random == 3)
                deck_cards.push_back(new Card(Card::cardType::Reinforcement));
            

            if (random == 4)
                deck_cards.push_back(new Card(Card::cardType::Airlift));
            

            if (random == 5)
                deck_cards.push_back(new Card(Card::cardType::Diplomacy));
        }
    }

    // Copy constructor
    Deck::Deck(const Deck& deck) {
        sizeDeck = deck.sizeDeck; // Copy the size of the deck

        // Iterate through each element in the source deck
        for (int i = 0; i < deck.deck_cards.size(); i++) {
            // Create a copy of the card and add it to the new deck
            deck_cards.push_back(deck.deck_cards[i]);
        }
    }





    /**
        1. Get random number from size of the deck
        2. Store the card at that index into a pointer variable
        3. Remove the card from the deck
        4. return the newly drawn card
    */
    Card* Deck::draw() {

        srand(time(NULL)); // Makes the random change every single run

        //Random int from 0 to the size of the deck
        int index = (rand() % (int) deck_cards.size() );

        cout << "\nYou picked the " << index << "nth card from the deck." << '\n';

        //Temp pointer to the drawn card
        Card* cardDrawn = deck_cards[index];

        //Removing the card from the deck
        deck_cards.erase(deck_cards.begin() + index);

        return cardDrawn;
    }
    
    
    // Push back card onto the deck
    void Deck::addCardToDeck(Card* card) {
        deck_cards.push_back(card);
        cout << "\nThe " << card->getCardType() << " card has been added to the deck." << '\n';
    }


    void Deck::setsizeDeck (int size){
        sizeDeck = size;
    }

    int Deck::getDeckSize() {
        return sizeDeck;
    }


    //Overloading the assignment operator
    Deck& Deck::operator= (const Deck& deck) {
        this->sizeDeck = deck.sizeDeck;
        this->deck_cards = deck.deck_cards;

        return *this;
    }

    // overloading output stream operator Deck
    ostream& operator<< (ostream& out, const Deck& deck){
        out << "The deck is made of " << deck.deck_cards.size() << " card(s) and contains:\n" << deck.deck_cards;
        return out;
    }




// Hand

    //Default constructor
    Hand::Hand() {
        sizeHand = 3; 
        cout << "\nCreating the player's hand..." << '\n';
    }

    //Constructor accepting an integer
    Hand::Hand(int size){
        sizeHand = size; 
        cout << "\nCreating the player's hand..." << '\n';
    }

    //Copy constructor
    Hand::Hand(const Hand& hand)  {

        sizeHand = hand.sizeHand;

        // Iterate through each element in the source hand
        for (int i = 0; i < hand.cards_in_hand.size(); i++) {
            // Create a copy of the card and add it to the new hand
            cards_in_hand.push_back(hand.cards_in_hand[i]);
        }
    }


    //Destructor for the deck object
    Hand::~Hand() {

        //Removing each pointer and pointing them to NULL
        for (int i = 0; i < cards_in_hand.size(); i++) {
            cards_in_hand[i] = NULL;
        }

        //Clearing the vector
        cards_in_hand.clear();
    }


    // Add a card to the hand vector
    void Hand::addCardToHand(Card* card){
        cards_in_hand.push_back(card);
    }

    // Remove a card from the hand vector
    void Hand::removeCardFromHand(int index){
        cards_in_hand.erase(cards_in_hand.begin() + index);
    }

    void Hand::setSize(int number) {
	    sizeHand = number;
    }

    // Get the allowed number of cards in hand 
    int Hand::getSize() {
        return sizeHand;
    }


    // Gets the card at the specified index from the hand vector
    Card* Hand::getCardInHand(int index){
        return cards_in_hand.at(index);
    }

    //Retrieves all cards in the hand vector
    vector<Card*> Hand::getPlayerHand(){return cards_in_hand;}

    //Chech if the size of the hand vector is equal to the limit on number of cards 
    bool Hand::IsHandFull(){
        if (sizeHand == cards_in_hand.size())
            cout << "Your hand is full";

        return sizeHand == cards_in_hand.size();
    }


    //Overloading the assignment operator
    Hand& Hand::operator= (const Hand& hand) {
        this->sizeHand = hand.sizeHand;
        this->cards_in_hand = hand.cards_in_hand;

        return *this;
    }

    // overloading output stream operator for hand
    ostream& operator<< (ostream& out, const Hand& hand){
        out << "The hand is made of " << hand.cards_in_hand.size() << " card(s), it contains:\n" << hand.cards_in_hand;
	    return out;
    }
