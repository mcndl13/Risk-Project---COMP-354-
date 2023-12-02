#include <iostream>
#include "Player.h"
#include "../Orders/Orders.h"
#include "PlayerStrategy.h"
using namespace std;

// Default Constructor
Player::Player(Hand* p_hand){
    player_Name = "player1";
    player_hand = p_hand;
    player_orders = new OrdersList();
    reinforcementPool = 0;
}


Player::Player(string pName, Hand* p_hand){
    player_Name = pName;
    player_hand = p_hand;
    player_orders = new OrdersList();
    reinforcementPool = 0;
}


// Copy constructor
Player::Player(const Player &p){

    player_Name = p.player_Name;
    player_hand = new Hand (*(p.player_hand));
    owned_territories = p.owned_territories;
    player_orders = new OrdersList(*(p.player_orders));
    reinforcementPool = p.reinforcementPool;
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



    if (order_type == "Deploy"){
        // 
        player_orders->addOrders(new Deploy(this, "deploy troops", this->getPlayerTerritories().at(1), 5), this);
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

// Change to owning player
bool Player::ownsTerritory(Territory* territory) {

    cout << "Executing ownsTerritory\n";
	for (Territory* temp : owned_territories) {
        cout << temp->getName() + " vs " + territory->getName() + "\n";
		if (temp->get_owning_player() == territory->get_owning_player()) {return true;}
	}
	return false;
}



// stream insertion operator
ostream& operator<<(ostream &out, const Player &p){
    return out << p.player_Name << "\n" << p.player_hand << "\n" << p.owned_territories << "\n" << p.player_orders;
}




// Getter

vector<Territory*> Player::getPlayerTerritories(){
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

int Player::getReinforcementPool(){
    return reinforcementPool;
}

bool Player::hasReinforcements(){
    return reinforcementPool > 0;
}

bool Player::hasCards(){
    return this->getHand()->getPlayerHand().empty();
}

void Player::setReinforcementPool(int r){
    reinforcementPool = r;
    cout << "\n\nReinforcement pool is now: " << r << endl;;
}

void  Player::changeStrategy(){
    PlayerStrategy* temp =  new AggressivePlayerStrategy();
    cout << this->player_Name << " became aggressive";

    delete this->player_strategy;
    player_strategy = temp;
}




// Adding new territory to the list of territory owned by a player
void Player::add_new_player_territory(Territory* territory) {
    cout << territory->getName() << " was added to " << this->getName() << " list of territories\n\n";
	owned_territories.push_back(territory);
    territory->set_owning_player(this);
}

void Player::addOrder(Orders* o){
    this->getOrders().push_back(o);
}

vector<string> Player::getDiplomacyNames() {
    return diplomacyPlayersName;
}
void Player::addDiplomacy(string name) {
    diplomacyPlayersName.push_back(name);
    std::cout<<"\n"<< name <<" was added to "<<name<<"'s diplomacy list\n";
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
