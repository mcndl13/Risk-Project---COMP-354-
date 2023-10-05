#include "OrderList.h"

void OrderList::add(Order* order)
{
	orders.push_back(order);
}

void OrderList::move(int srcIndex, int destIndex)
{
	if (srcIndex >= 0 && srcIndex < orders.size() && destIndex >= 0 && destIndex < orders.size()) 
	{
		if (srcIndex != destIndex) 
		{
			Order* order = orders[srcIndex];
			orders.erase(orders.begin() + srcIndex);
			orders.insert(orders.begin() + destIndex, order);
		}
	}
}

void OrderList::remove(int index)
{

}
