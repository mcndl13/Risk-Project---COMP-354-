#include "Orders.h"

#include <deque>

class OrderList
{
public:

	void add(Order* order);
	void move(int srcIndex, int destIndex);
	void remove(int index);

private:
	std::deque<Order*> orders;
};