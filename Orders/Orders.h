#pragma once

#include <string>
#include <iostream>

class Order
{
public:
	Order(const std::string& inDescription) { description = inDescription; }

	virtual bool validate() = 0;
	virtual void execute() = 0;

	friend std::ostream& operator<<(std::ostream& os, const Order& order);

	std::string description;
};

class Deploy : public Order
{

public:
	Deploy(const std::string& inDescription) : Order(inDescription) {}

	bool validate() override;
	void execute() override;
};

class Advance : public Order
{
public:
	Advance(const std::string& inDescription) : Order(inDescription) {}

	bool validate() override;
	void execute() override;
};

class Bomb : public Order
{
public:
	Bomb(const std::string& inDescription) : Order(inDescription) {}

	bool validate() override;
	void execute() override;
};

class Blockade : public Order
{
public:
	Blockade(const std::string& inDescription) : Order(inDescription) {}

	bool validate() override;
	void execute() override;
};

class Airlift : public Order
{
public:
	Airlift(const std::string& inDescription) : Order(inDescription) {}

	bool validate() override;
	void execute() override;
};