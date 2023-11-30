#include <iostream>
#include "Orders.h"
#include <random>


//=================== Orders class =======================

    bool SimulateResult(double probability);

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

    void Orders::setDescription(std::string desc){
        description = desc;
    }
    bool Orders::checkNegotiate(Player* playerA, std::string playerB) {
        if (playerA->getDiplomacyNames().empty())
            return false;//no negotiate
        vector<string> nameList = playerA->getDiplomacyNames();
        auto it = std::find(nameList.begin(), nameList.end(), playerB);
        if (it != nameList.end()) return true;//negotiate found
        //else didn't find it
        return false;//no negotiate
    }


    bool Orders::getExecuted(){return executed;}
    void Orders::setExecuted(bool exec) {executed = exec;}




//=================== Deploy class =======================
        Deploy::Deploy(Player* player, const string& inDescription, Territory* target, int newArmies): Orders(inDescription){
        order_owner = player;
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
        std::cout<<"\nValidating Deploy order..."<<std::endl;

        if (order_target == nullptr||order_owner==nullptr) {
            cout << "Deploy order is invalid due to a NULLPTR problem"<<endl;
            return false;
        }

        //if target territory belongs to order owner, deploy order is valid
        if(order_owner->ownsTerritory(order_target)) {
            cout << "Deploy order is valid" << endl;
            return true;
        }
        // If the target territory does not belong to the player that issued the order, the order is invalid
        cout << "Deploy order is invalid. " + order_owner->getName() + " does not own " + order_target->getName() + " territory" <<endl;
            return false;
    }

    // Execute the the Deploy order and print message
    void Deploy::execute(){

    std::cout << "\nExecuting execute() in Deploy\n\n";

        if (!order_owner) {
            cerr << "Error: order_owner is null\n";
            // Handle the error or return as appropriate
            return;
        }

        if (!order_target) {
            cerr << "Error: order_target is null\n";
            // Handle the error or return as appropriate
            return;
        }

        if (validate()) {
            cout << "Executing Deploy order on " + order_target->getName();
            order_target->adding_armies_number(new_armies);
            setDescription("\n"+order_owner->getName() + " has executed the order to Deploy " + std::to_string(new_armies)
                        + " on the territory " + order_target->getName() + ", and now there are "+std::to_string(order_target->get_number_of_armies())+" army units.\n\n");
            setExecuted(true);
        } else {
            setDescription("The Deploy order failed to execute\n");
        }

        std::cout << getDescription()<<std::endl;
    }

    
    ostream& operator<< (ostream& out, Deploy& deploy){
        return out << "Deploy Order's description is "<<deploy.getDescription();
    }

    //Assignment operator overload
    Deploy& Deploy::operator = (const Deploy& deploy){
        order_owner = deploy.order_owner;
        order_target = deploy.order_target;
        return *this;
    }






//=================== Advance class =======================
    Advance::Advance(Player* in_order_owner, const string& inDescription, int num, Territory* source, Territory* target): Orders(inDescription){
        order_owner = in_order_owner;
        army_num = num;
        order_source = source;
        order_target = target;
    }

    string Advance::getName() {return order_name;}


    bool Advance::isAdjacentWith() {
        std::cout<<"\nChecking is adjacent"<<std::endl;

        //look for the pointer in the vector
        auto it = std::find(order_source->getAdjacencies().begin(), order_source->getAdjacencies().end(), order_target);
        Territory* foundValue = *it;
        // if(foundValue){
        //     std::cout<<"\nThis is our target ->"<<order_target->getName()<<", and this is the territory in iterator ->"<<foundValue->getName()<<std::endl;
        // }else{
        //     std::cout<<"foundValue is nullptr"<<std::endl;
        // }

        //if the iterater returned is not the end(), found the target
        if (it != order_source->getAdjacencies().end()) {
            return true;
        }
        //didn't find it, return false
        std::cout<<order_source->getName()<<" is not adjacent with "<<order_target->getName()<<std::endl;
        return false;
    }

    bool Advance::validate() {
        std::cout<<"\nValidating Advance order..."<<std::endl;
            if (order_source == nullptr || order_target == nullptr ||
                order_owner == nullptr) {
                    if(order_source == nullptr){
                            cerr << "ERROR: Advance order has order_source as NULLPTR" << endl;
                    }
                    if(order_target == nullptr){
                            cerr << "ERROR: Advance order has order_target as NULLPTR" << endl;
                    }
                    if(order_owner == nullptr){
                            cerr << "ERROR: Advance order has order_owner as NULLPTR" << endl;
                    }
                cerr << "ERROR: Advance order validatation failed because NULLPTR" << endl;
                return false;
            }
            //return true if owns source and source and target are adjacent
            if (order_owner->ownsTerritory(order_source)&& isAdjacentWith()) {
                cout << "The advance order is valid" << endl;
                return true;
            }
            cout << "The advance order is invalid" << endl;
            return false;
    }

    void Advance::execute() {
        std::cout<<"\nExecuting excute() in Advance..."<<std::endl;
        if (!validate()) {
            setDescription("The advance order failed to execute due to invalid\n");
            std::cout << getDescription()<<std::endl;
            return;
        }
        //if owns target, them move units to it
        if (order_owner->ownsTerritory(order_target)) {
            setDescription("The advance order executed as a transformation of army units\n");
            //check if the army exist in the source territory
            //if not enough, will send all source has
            if (order_source->get_number_of_armies() < army_num) {
                army_num = order_source->get_number_of_armies();
            }

            order_source->adding_armies_number(-army_num);
            order_target->adding_armies_number(army_num);
            setDescription(getDescription()+std::to_string(army_num)+" army units being removed from source territory "+order_source->getName()+
            ".\n"+std::to_string(army_num)+" army units being added to target territory."+order_target->getName()+"\n");
            std::cout << getDescription()<<std::endl;
            return;
        }
        //attack simulation
        //if there is a negotiate,abort
        if (checkNegotiate(order_owner, order_target->get_owning_player()->getName())) {
            setDescription("The advance order is in valid and was abort because of diplomacy.\n");
            std::cout << getDescription()<<std::endl;
            return;
        }
        std::cout<<"\nThe advance order executed as an attack, attacker army units: "<<army_num<<" Defender army units: "<< order_target->get_number_of_armies()
        <<"(number in attacker may change because source territory may not have enough army units)"<<std::endl;
        if (order_source->get_number_of_armies() < army_num) 
            army_num = order_source->get_number_of_armies();
        order_source->adding_armies_number(-army_num);
        int attackKill = 0;
        int defendKill = 0;
        for (int i = 0; i < army_num; i++) {
            //std::cout<<"\n doing the looop"<<std::endl;
            if (SimulateResult(1.0)) {//attack killing probability is 60% TODO:change it bakc to 0.6 when random works
                attackKill++;
                //std::cout<<"\n in the if in the looop and attackKill is "<<std::to_string(attackKill) <<std::endl;
            }
        }
        for (int j = 0; j < order_target->get_number_of_armies();j++) {
            //std::cout<<"\n doing the looop"<<std::endl;
            if (SimulateResult(1.0)) {//defend killing probability is 70% TODO:change it bakc to 0.6
                defendKill++;
                //std::cout<<"\n in the if in the looop and attackKill is "<<std::to_string(defendKill) <<std::endl;
            }
        }
        //army number decrease the amount that got killed, and wont be negative
        army_num = (army_num - defendKill<0) ? 0 : army_num - defendKill;
        //if all killed ,then minus the whole amount, otherwise minus the amount that was killed
        order_target->adding_armies_number((order_target->get_number_of_armies()-attackKill<0)?-order_target->get_number_of_armies():-attackKill);
        std::cout<<"\nAfter calculation -> attackKill: "<<std::to_string(attackKill)<<" defendKill: "<<std::to_string(defendKill)
        <<" And army left: "<< std::to_string(army_num)<<" , order_target army: "<<std::to_string(order_target->get_number_of_armies()) <<std::endl;
        //If all the defender's army units are eliminated, the attacker captures the territory. The attacking army
        //units that survived the battle then occupy the conquered territory
        //In this case, if both are eliminated, nothing happens
        if (order_target->get_number_of_armies() == 0&&army_num>0) {
            order_owner->add_new_player_territory(order_target);
            order_owner->setConquer(true);
            //receive a card after capture,should be end of the turn
            //order_owner->getHand()->addCardToHand();
            setDescription("\nAfter a victorious battle, "+std::to_string(army_num)+" army units take over the territory"+order_target->getName()+"."+
            "\nNow "+order_target->getName()+" belongs to "+order_owner->getName()+".\n");
            order_target->adding_armies_number(army_num);
            std::cout << getDescription()<<std::endl;
            return;
        }
        //if defender's army were not eliminated then nothing happens after
        //but if there are still attacker's army left
        //send them back
        if(army_num>0&&order_target->get_number_of_armies() > 0){
            order_source->adding_armies_number(army_num);
            setDescription("\nAfter a hard fight, "+std::to_string(army_num)+" army units retreated, and the defenders has "+std::to_string(order_target->get_number_of_armies())+" army units left.");
            std::cout << getDescription()<<std::endl;
            return;
        }
        if(army_num==0&&order_target->get_number_of_armies() > 0){
            setDescription("\nAfter a hard fight, the defenders eliminated all the attackers with "+std::to_string(order_target->get_number_of_armies())+" army units left.");
        }
        if(order_target->get_number_of_armies() == 0&&army_num==0){
            setDescription("\nNo one survived, all the armies died and nothing happend after.");
        }
        std::cout << getDescription()<<std::endl;
    }
    /// <summary>
    /// return true if the random number is smaller than
    ///  the probability 
    /// </summary>
    /// <param name="probability"></param>
    /// <returns></returns>

    bool SimulateResult(double probability) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double randomValue = dis(gen);
        std::cout<<"\nrandom value is :"<<randomValue<<std::endl;
        return randomValue < probability;
    }



    ostream& operator<< (ostream& out, Advance& advance){
        return out << "Advance Order's description is " << advance.getDescription();
    }

    //Assignment operator overload
    Advance& Advance::operator = (const Advance& advance){
        order_owner = advance.order_owner;
        order_target = advance.order_target;
        return *this;
    }


    //=================== Airlift class =======================
    Airlift::Airlift(Player* player, const string& inDescription, int num, Territory* source, Territory* target) : Orders(inDescription) {
        order_owner = player;
        army_num = num;
        order_source = source;
        order_target = target;
    }
    bool Airlift::validate() { 
        std::cout<<"\nValidating Airlift order..."<<std::endl;
        if (order_target == nullptr ||
            order_owner == nullptr) {
            cerr << "ERROR: Airlift order validatation failed because NULLPTR" << std::endl;
            return false;
        }
        if (order_owner->ownsTerritory(order_target)&&order_owner->ownsTerritory(order_target)) {
            cout << "The airlift order is valid" << endl;
            return true;
        }
        cout << "The airlift order is invalid" << endl;
        return false;
    }

    void Airlift::execute() {
        std::cout<<"\nExecuting execute() in Airlift..."<<std::endl;
        if (validate()) {
            setDescription("The airlift order executed\n"+std::to_string(army_num)+" army units were removed from source territory "+order_source->getName()+".\n"+
            std::to_string(army_num)+"army units were airlifted to the target territory"+order_target->getName()+".\n");
            if (army_num > order_source->get_number_of_armies()) {
                army_num = order_source->get_number_of_armies();
            }
            order_source->adding_armies_number(-army_num);
            cout << army_num << " army units were removed from source territory."<<order_source->getName() <<std::endl;
            order_target->adding_armies_number(army_num);
            cout << army_num << " army units were airlifted to the target territory." << order_target->getName()<< std::endl;
            std::cout << getDescription()<<std::endl;
            return;
        }
        //if not valid
        setDescription("Airlift order did not execute because the order is invalid.\n");
        std::cout << getDescription()<<std::endl;
    }
    string Airlift::getName() { return order_name; }



    ostream& operator<< (ostream& out, Airlift& airlift) {
        return out << "Airlift Order's description is" << airlift.getDescription();
    }

    //Assignment operator overload
    Airlift& Airlift::operator = (const Airlift& airlift) {
        order_owner = airlift.order_owner;
        order_target = airlift.order_target;
        return *this;
    }



//=================== Bomb class =======================
    Bomb::Bomb(Player* player, const string& inDescription, Territory* target): Orders(inDescription){
        order_owner = player;
        order_target = target;
    }

     bool Bomb::isAdjacentWith() {
        for (const auto& obj : order_target->getAdjacencies()) {
            if (order_owner->ownsTerritory(obj)) {
                return true;//if there is one adjacent territory that was owned by order_owner
            }
        }
        //no adjacent territory
        std::cout<<order_owner->getName()<<"'s territories are not adjacent with "<<order_target->getName()<<std::endl;
        return false;
    }

    bool Bomb::validate() {
        std::cout<<"\nValidating Bomb order..."<<std::endl;
        if ( order_target == nullptr ||
            order_owner == nullptr) {
            cerr << "ERROR: Bomb order validatation failed because NULLPTR" << endl;
            return false;
        }
        if (order_owner->ownsTerritory(order_target) || !isAdjacentWith()) {
            cout << "Boom order is invalid because owenership or adjacent problem" << endl;
            return false;
        }
        if (checkNegotiate(order_owner, order_target->get_owning_player()->getName())) {
            cout << "Boom order is invalid because diplomacy" << endl;
            return false;
        }
        return true;
    }

    void Bomb::execute(){
        std::cout<<"\nExecuting execute() in Bomb..."<<std::endl;
        if (!validate()) {
            setDescription("The bomb order failed to execute due to invalid\n");
            return;
        }
        //remove half of the army units from target
        cout << "Half of target territory's army has been removed."<<order_target<<endl;
        order_target->adding_armies_number(-order_target->get_number_of_armies() / 2);
        setDescription("The bomb order has been executed, Half of target territory's("+order_target->getName()+") army has been removed. Now it has "+std::to_string(order_target->get_number_of_armies()) +" units of army. \n");
        std::cout << getDescription()<<std::endl;
    }

    string Bomb::getName() {return order_name;}

    ostream& operator<< (ostream& out, Bomb& bomb){
        return out << "Bomb Order's description is" << bomb.getDescription();
    }





//=================== Blockade class =======================
    Blockade::Blockade(Player* player, const string& inDescription, Territory* target): Orders(inDescription){
        order_owner = player;
        order_target = target;
    }

    bool Blockade::validate() {
        std::cout<<"\nValidating Blockade order..."<<std::endl;
        if (order_target == nullptr ||
            order_owner == nullptr) {
            cerr << "ERROR: Blockade order validatation failed because NULLPTR" << endl;
            return false;
        }
        if (order_owner->ownsTerritory(order_target)) {
            cout << "Blockade order is valid" << endl;
            return true;
        }
        cout << "Blockade order is invalid because order_owner doesn't own the target territory." << endl;
        return false;
    }
    void Blockade::execute(){
        std::cout<<"\nExecuting execute() in Blockade"<<std::endl;
        if (validate()) {
            order_target->adding_armies_number(order_target->get_number_of_armies());
            setDescription("Blockade order has been executed, and "+order_target->getName()+" is now neutral and the army on it was doubled. Now it has "+std::to_string(order_target->get_number_of_armies())+" units of army\n");
            // for(auto it : engine->GetPlayerList()){
        //  
        //  if(it->GetName()=="Neutral"){
        //        order_target->set_owning_player(it);
        //          return;//go out of function
        //      }
        // }
        //TODO: set owner to neutral
        //TODO: need to create neutral if doesn't exist
            Player* neutralPlayer = new Player("Neutral", new Hand());
            //if we have engine referance push it into the player list
            //engine->GetPlayerList().pushback(neutralPlayer);
            order_target->set_owning_player(neutralPlayer);
        }
    }

    string Blockade::getName() {return order_name;}



    ostream& operator<< (ostream& out, Blockade& blockade){
        return out << "Blockade Order's description is" << blockade.getDescription();
    }

    //Assignment operator overload
    Blockade& Blockade::operator = (const Blockade& blockade){
        order_owner = blockade.order_owner;
        order_target = blockade.order_target;
        return *this;
    }












//=================== Negotiate class =======================


    Negotiate::Negotiate(Player* player, const string& inDescription, Player* p_target): Orders(inDescription){
        order_owner = player;
        target_player = p_target;
    }
    bool Negotiate::validate() {
        std::cout<<"\nValidating Negotiate order..."<<std::endl;
        if (target_player == nullptr ||
            order_owner == nullptr) {
            cerr << "ERROR: Negotiate order validatation failed because NULLPTR" << std::endl;
            return false;
        }
        if (order_owner!=target_player&&target_player->getName()!="Neutral") {
            cout << "Negotiate order is valid." << std::endl;
            return true;
        }
        cout << "Negotiate order is invalid." << std::endl;
        return false;
    }
    void Negotiate::execute(){
        std::cout<<"\nExecuting execute() in Negotiate..."<<std::endl;
        if (validate()) {
            setDescription("Negotiate order has been executed."+order_owner->getName()+" and "+target_player->getName()+" can not attack each other until next turn.");
            target_player->addDiplomacy(order_owner->getName());
            order_owner->addDiplomacy(target_player->getName());
            std::cout<<getDescription()<<std::endl;
            return;
        }
        setDescription("Negotiate order failed to execute because of invalidation.");

        
    }
    string Negotiate::getName() {return order_name;}



    ostream& operator<< (ostream& out, Negotiate& Negotiate){
        return out << "Negotiate Order's description is" << Negotiate.getDescription();
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









