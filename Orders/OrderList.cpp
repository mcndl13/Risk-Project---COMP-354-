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
	if (index >= 0 && index < orders.size()) 
	{
		Order* order = orders[index];
		orders.erase(orders.begin() + index);
		delete order; // 删除被移除的订单指针
	}
}
