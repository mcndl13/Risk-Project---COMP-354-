#include "Orders.h"

#include <stdexcept>

std::ostream& operator<<(std::ostream& os, const Order& order)
{
	os << order.description;
	return os;
}

bool Deploy::validate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Deploy::execute()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Advance::validate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Advance::execute()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Bomb::validate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Bomb::execute()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Blockade::validate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Blockade::execute()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Airlift::validate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Airlift::execute()
{
	throw std::logic_error("The method or operation is not implemented.");
}
