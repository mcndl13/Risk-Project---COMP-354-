#pragma once
#include <string>
#include <deque>
#include <algorithm>
#include <vector>

#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
// #include "../GameEngine/GameEngine.h"




class Orders {

	private:
        std::string description;
		bool executed = false;
	
    public:
		Orders();
        Orders(const std::string& inDescription);

		virtual bool validate() = 0;
		virtual void execute() = 0;
		virtual std::string getName();
		// virtual int getArmies();

		bool getExecuted();
		void setExecuted(bool);

        std::string getDescription();
		void setDescription(std::string);
		bool checkNegotiate(Player* playerA, std::string playerB);

        friend std::ostream& operator<<(std::ostream& out, const Orders& order);
		// friend std::ostream& operator<< (std::ostream& out, const std::vector<Orders*> orders);
};


class OrdersList {

	private:
		std::deque<Orders*> orders;

	public:
		OrdersList(std::deque<Orders*>);
		OrdersList();
		~OrdersList();

		// Copy constructor
		OrdersList(const std::deque<Orders*>&);

        std::deque<Orders*>& getOrdersList();
		void addOrders(Orders* order, Player* owner);

		void move(int o1, int o2);
		void remove(int index);

		friend std::ostream& operator << (std::ostream& out, OrdersList&);
};




class Deploy : public Orders {

	private:
		Player* order_owner;
		std::string order_name = "Deploy";
		Territory* order_target;
		int new_armies;


	public:
		Deploy(Player* order_owner, const std::string& inDescription, Territory* target, int newArmies);

		bool validate() override;
		void execute() override;
		std::string getName() override;

		friend std::ostream& operator << (std::ostream& out, Deploy& ); // Stream insertion operator
		Deploy& operator = (const Deploy& deploy); //Assignment operator
};





class Advance : public Orders {

	private:
		Player* order_owner;
		std::string order_name = "Advance";
		Territory* order_target;		
		Territory* order_source;
		int army_num;

	public:
		Advance(Player* player, const std::string& inDescription, int num, Territory* source, Territory* target);
		
		bool validate() override;
		void execute() override;
		std::string getName() override;
		bool isAdjacentWith();
		friend std::ostream& operator << (std::ostream& out, Advance&); // Stream insertion operator
		Advance& operator = (const Advance& advance); //Assignment operator
};



class Airlift : public Orders {

private:
	Player* order_owner;
	std::string order_name = "Airlift";
	Territory* order_target;
	Territory* order_source;
	int army_num;

public:
	Airlift(Player* order_owner, const std::string& inDescription, int num, Territory* source, Territory* target);

	bool validate() override;
	void execute() override;
	std::string getName() override;

	friend std::ostream& operator << (std::ostream& out, Airlift&); //Assignment operator
	Airlift& operator = (const Airlift& airlift); //Assignment operator
};




class Bomb : public Orders {

	private:
		Player* order_owner;
		std::string order_name = "Bomb";
		Territory* order_target;

	public:
		Bomb(Player* order_owner, const std::string& inDescription, Territory* target);

		bool validate() override;
		void execute() override;
		std::string getName() override;
		bool isAdjacentWith();
		friend std::ostream& operator << (std::ostream& out, Bomb&); //Assignment operator
		Bomb& operator = (const Bomb& bomb); //Assignment operator
};




class Blockade : public Orders {

	private:
		Player* order_owner;
		std::string order_name = "Blockade";
		Territory* order_target;

	public:
		Blockade(Player* order_owner, const std::string& inDescription, Territory* target);

		bool validate() override;
		void execute() override;
		std::string getName() override;

		friend std::ostream& operator << (std::ostream& out, Blockade&); //Assignment operator
		Blockade& operator = (const Blockade& blockade); //Assignment operator
};




class Negotiate : public Orders {

	private:
		Player* order_owner;
		std::string order_name = "Negotiate";
		Player* target_player;

	public:
		Negotiate(Player* order_owner, const std::string& inDescription, Player* p_target);
		

		bool validate() override;
		void execute() override;
		std::string getName() override;

		friend std::ostream& operator << (std::ostream& out, Negotiate&); //Assignment operator
		Negotiate& operator = (const Negotiate& negotiate); //Assignment operator
};

