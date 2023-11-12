#include <iostream>
#include "Orders.h"

using namespace std;

//=================== Orders class =======================

    // Default constructor
    Orders::Orders () = default;

    Orders::Orders(const string& inDescription){
        description = inDescription; 
    }

    string Orders::getDescription(){
        return description;
    }

    ostream& operator<< (ostream& out, const Orders& order){
        out << "The order's description is: " << order.description;
        return out;
    }


    //Implemented in other child classes
    bool Orders::validate() {
        return false;
    }

    //Implemented in order child classes
    void Orders::execute() {}

    string Orders::getName() {return {};}

    void Orders::setDescription(string desc){
        description = desc;
    }


    bool Orders::getExecuted(){return executed;}
    void Orders::setExecuted(bool exec) {executed = exec;}




//=================== Deploy class =======================
    Deploy::Deploy(Player* order_owner, const string& inDescription, Territory* target, int newArmies): Orders(inDescription){
        this->order_owner = order_owner;
        order_target = target;
        new_armies = newArmies;
    }

    string Deploy::getName() {
        return order_name;
    }

    // Checks if the deploy conditions are met
    // 1. the target territory is owned by the player
    // 2. the player has number of armies > 0
    bool Deploy::validate() {

        if(order_target == nullptr)
            return false;

        // If the target territory does not belong to the player that issued the order, the order is invalid
        if(order_owner->ownsTerritory(order_target) && order_target->get_number_of_armies() > 0) {
            cout << "Deploy order is valid" << endl;
            return true;
        }
        cout << "Deploy order is invalid. " + order_owner->getName() + " does not own " + order_target->getName() + " territory" <<endl;
            return false;
    }

    // Execute the the Deploy order and print message
    void Deploy::execute(){

    cout << "Executing execute()\n\n";

        if (!order_owner) {
            cout << "Error: order_owner is null\n";
            // Handle the error or return as appropriate
            return;
        }

        if (!order_target) {
            cout << "Error: order_target is null\n";
            // Handle the error or return as appropriate
            return;
        }

        if (this->validate()) {
            cout << "Executing Deploy order on " + order_target->getName();
            order_target->adding_armies_number(new_armies);
            setDescription(order_owner->getName() + " has executed the order to Deploy " + to_string(order_target->get_number_of_armies())
                        + " on the territory " + order_target->getName() + "\n\n");
            setExecuted(true);
        } else {
            setDescription("The Deploy order failed to execute\n");
        }

        cout << getExecuted();
    }

    
    ostream& operator<< (ostream& out, Deploy& deploy){
        return out << "Deploy Order";
    }

    //Assignment operator overload
    Deploy& Deploy::operator = (const Deploy& deploy){
        order_owner = deploy.order_owner;
        order_target = deploy.order_target;
        return *this;
    }






//=================== Advance class =======================
    Advance::Advance(Player* order_owner, const string& inDescription, int num, Territory* source, Territory* target): Orders(inDescription){
        order_owner = order_owner;
        order_target = target;
        army_num = num;
        order_source = source;
        order_target = target;
    }

    string Advance::getName() {return order_name;}

    bool Advance::validate() {return true;}
    void Advance::execute(){}



    ostream& operator<< (ostream& out, Advance& advance){
        return out << "Advance Order";
    }

    //Assignment operator overload
    Advance& Advance::operator = (const Advance& advance){
        order_owner = advance.order_owner;
        order_target = advance.order_target;
        return *this;
    }






//=================== Bomb class =======================
    Bomb::Bomb(Player* order_owner, const string& inDescription, Territory* target): Orders(inDescription){
        order_owner = order_owner;
        order_target = target;
    }
    bool Bomb::validate() {return true;}
    void Bomb::execute(){}

    string Bomb::getName() {return order_name;}



    ostream& operator<< (ostream& out, Bomb& bomb){
        return out << "Bomb Order";
    }

    //Assignment operator overload
    Bomb& Bomb::operator = (const Bomb& bomb){
        order_owner = bomb.order_owner;
        order_target = bomb.order_target;
        return *this;
    }






//=================== Blockade class =======================
    Blockade::Blockade(Player* order_owner, const string& inDescription, Territory* target): Orders(inDescription){
        order_owner = order_owner;
        order_target = target;
    }
    bool Blockade::validate() {return true;}
    void Blockade::execute(){}

    string Blockade::getName() {return order_name;}



    ostream& operator<< (ostream& out, Blockade& blockade){
        return out << "Blockade Order";
    }

    //Assignment operator overload
    Blockade& Blockade::operator = (const Blockade& blockade){
        order_owner = blockade.order_owner;
        order_target = blockade.order_target;
        return *this;
    }









//=================== Airlift class =======================
    Airlift::Airlift(Player* order_owner, const string& inDescription, int num, Territory* source, Territory* target): Orders(inDescription){
        order_owner = order_owner;
        order_target = target;
        army_num = num;
        order_source = source;
        order_target = target;
    }

    bool Airlift::validate() {return true;}
    void Airlift::execute(){}
    string Airlift::getName() {return order_name;}



    ostream& operator<< (ostream& out, Airlift& airlift){
        return out << "Airlift Order";
    }

    //Assignment operator overload
    Airlift& Airlift::operator = (const Airlift& airlift){
        order_owner = airlift.order_owner;
        order_target = airlift.order_target;
        return *this;
    }


//=================== Negotiate class =======================

    Negotiate::Negotiate(Player* order_owner, const string& inDescription, Player* p_target): Orders(inDescription){
        order_owner = order_owner;
        target_player = p_target;
    }

    bool Negotiate::validate() {return true;}
    void Negotiate::execute(){}
    string Negotiate::getName() {return order_name;}



    ostream& operator<< (ostream& out, Negotiate& Negotiate){
        return out << "Negotiate Order";
    }

    //Assignment operator overload
    Negotiate& Negotiate::operator = (const Negotiate& negotiate){
        order_owner = negotiate.order_owner;
        target_player = negotiate.target_player;
        return *this;
    }



//=================== OrdersList class ======================

    OrdersList::OrdersList(): orders(){}

    // Constructor
    OrdersList::OrdersList(deque<Orders*> list_of_orders){
        orders = list_of_orders;
    }

    // Destructor
    OrdersList::~OrdersList(){
        cout << "Calling OrdersList destructor\n";
        orders.clear();
    }

    // Copy constructor
    OrdersList::OrdersList(const std::deque<Orders*>& original_orders_list){
        orders = original_orders_list;
    }

    // Get orderslist
    deque<Orders*>& OrdersList::getOrdersList(){return orders;}


    void OrdersList::addOrders(Orders* order, Player* owner){
        orders.push_back(order);
        cout << "A " + order->getDescription() + " order was issued and added to the orderlist of " + owner->getName() + "\n\n";
    }

    // Move two orders in the orderslist around
    void OrdersList::move(int o1_index, int o2_index){

        Orders* temp = orders.at(o2_index);
        orders[o2_index] = orders[o1_index];
        orders[o1_index] = temp;
    }

    // Remove an order from the orderslist
    void OrdersList::remove(int index){
        orders.erase(orders.begin() + index);
    }

    // 
    ostream& operator<< (std::ostream& out, OrdersList& orders_List){

        for(Orders* temp: orders_List.getOrdersList()){
            out << temp << "\n";
        }
        out << "\n\n";

        return out;
    }









