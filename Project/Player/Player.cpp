#include <iostream>
#include "Player.h"
#include "../Orders/Orders.h"

using namespace std;

// Default Constructor
Player::Player(Hand* p_hand){
    player_Name = "player1";
    player_hand = p_hand;
    player_orders = new OrdersList();
    
}


Player::Player(string pName, Hand* p_hand){
    player_Name = pName;
    player_hand = p_hand;
    player_orders = new OrdersList();
}


// Copy constructor
Player::Player(const Player &p){

    player_Name = p.player_Name;
    player_hand = new Hand (*(p.player_hand));
    owned_territories = p.owned_territories;
    player_orders = new OrdersList(*(p.player_orders));
}

// Destructor
Player::~Player(){

    cout << "Calling Player destructor\n";

    owned_territories.clear();

    delete player_hand;
    delete player_orders;

}


    



// Assignment operator
Player& Player::operator=(const Player& p) {

	player_Name = p.player_Name;
	this->player_hand = new Hand(*(p.player_hand)); 

	owned_territories = p.owned_territories;
	player_orders = new OrdersList(*(p.player_orders));
	return *this;
}



// deque<Orders*> orders;
// Player contains a issueOrder() method that creates an order object and adds it to the list of orders.
void Player::issueOrder(string order_type){

    // try {
    //     Orders* temp = new Deploy(this, "deploy troops", this->toAttack().at(0));

    //     cout << "\n\nAfter deploy is created\n\n";

    //     if (this->player_orders) {  // Check if player_orders is not null
    //         this->player_orders->addOrders(temp); // Causes segmentation fault
    //     } else {
    //         cout << "player_orders is null or uninitialized.\n";
    //     }
    // } catch (const std::exception& e) {
    //     cerr << "Exception: " << e.what() << endl;
    // }


    if (order_type == "Deploy"){
        //TODO: hook input with this commend
        player_orders->addOrders(new Deploy(this, "deploy troops", this->toDefend().at(1), 5), this);
    }

    else if (order_type == "Advance")//TODO: hook input with this commend
        player_orders->addOrders(new Advance(this, "Advance troops",5, this->toAttack().at(0),this->toAttack().at(1)), this);

    
    else if (order_type == "Bomb")
        player_orders->addOrders(new Bomb(this, "Bomb incoming!!!", this->toAttack().at(0)), this);



    else if (order_type == "Blockade")
        player_orders->addOrders(new Blockade(this, "Blockade installed", this->toAttack().at(0)),this);


    else if (order_type == "Airlift")//TODO: hook input with this commend
        player_orders->addOrders(new Airlift(this, "Airlift issued",5, this->toAttack().at(0),this->toAttack().at(1)), this);

    
    else
        cout << "Invalid order\n\n"; 
}


bool Player::ownsTerritory(Territory* territory) {

    cout << "Executing ownsTerritory\n";
	for (Territory* temp : owned_territories) {
        cout << temp->getName() + " vs " + territory->getName() + "\n";
		if (temp->getName() == territory->getName()) {return true;}
	}
	return false;
}



// stream insertion operator
ostream& operator<<(ostream &out, const Player &p){
    return out << p.player_Name << "\n" << p.player_hand << "\n" << p.owned_territories << "\n" << p.player_orders;
}




// Getter
vector<Territory*> Player::toDefend(){
    return owned_territories;
}

// Temporary
vector<Territory*> Player::toAttack(){
    return owned_territories;
}

// Return player hand
Hand* Player::getHand() {return player_hand;}

// Return play orderslist
deque<Orders*>& Player::getOrders(){
    return player_orders->getOrdersList();
}

string Player::getName(){
    return player_Name;
}


std::vector<std::string> Player::getDiplomacyNames() {
    return diplomacyPlayersName;
}
void Player::addDiplomacy(std::string name) {
    diplomacyPlayersName.push_back(name);
}
void Player::resetDiplomacy() {
    diplomacyPlayersName.clear();
}
bool Player::getConquer() {
    return hasConquered;
}
void Player::setConquer(bool has_conquer)
{
    hasConquered = has_conquer;
}

// Adding new territory to the list of territory owned by a player
void Player::add_new_player_territory(Territory* territory) {
	owned_territories.push_back(territory);
}