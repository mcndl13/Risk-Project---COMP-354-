#pragma once
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Orders/Orders.h"
// #include "../Game Engine/GameEngine.h"


using namespace std;

class Deck;


class Card{

    private:
        string card_type;

    public:
        // Group of constant that represent the Types of cards 
        enum class cardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
        
        Card();
        Card(cardType);
        Card(const Card& card);


        //Helpers
        void play(Hand* hand, int index, Deck* Deck, Player * player);
        bool checkIndex(vector<Card*>, int);
        string getCardType();



        // Assignment operator
        Card& operator= (const Card& Card);

        // Stream insertion operator
        friend ostream& operator << (ostream&, const vector<Card*>);
        friend ostream& operator << (ostream&, const Card&);
};


class Deck{

    public:
        Deck();
        Deck(int size);
        Deck(const Deck&); // Copy constructor 


        //Helpers
        Card* draw ();
        void addCardToDeck(Card* card);
        void setsizeDeck(int);
        int getDeckSize();


        // Assignment operator
        Deck& operator=(const Deck& deck);

        // Stream insertion operator
        friend ostream& operator << (ostream&, const vector<Card*>);
        friend ostream& operator << (ostream&, const Deck&);


    private:
        vector<Card*> deck_cards;
        int sizeDeck;
};



class Hand{

    public:
        Hand();
        ~Hand();
        Hand(int size);
        Hand(const Hand&); // Copy constructor 


        //Helpers
        
        Card* getCardInHand(int); // Get a card in the players hand
        vector<Card*> getPlayerHand();// Get all the Card in a player's hand

        void setSize(int number);
        int getSize();

        void removeCardFromHand(int index);
        void addCardToHand(Card* card);

        bool IsHandFull();

        




        // Assignment operator
        Hand& operator=(const Hand& deck);

        // Stream insertion operator
        friend ostream& operator << (ostream&, const vector<Card*>);
        friend ostream& operator << (ostream&, const Hand&);


    private:
        vector<Card*> cards_in_hand;
        int sizeHand;
};




// // These should be removed and instead link other files


// class Player {

//     public:

//         Player();
//         void issueOrder(class Orders*);
//         vector<class Orders*> getOrders();
//         ~Player();

//     private:
//         string name;
//         vector<Orders*> player_orders;
// };


// class Orders {

//     public:
//         Orders(const string& inDescription);

//         friend ostream& operator<<(ostream& os, const vector<Orders*>);

//     private:
//         string description;
// };



