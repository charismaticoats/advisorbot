#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

//from example code
/** construct, reading a csv file */
OrderBook::OrderBook(std::string filename) 
{
	orders = CSVReader::readCSV(filename);
}

//from example code
/** return vector of all known products in the datasets */
std::vector<std::string> OrderBook::getKnownProducts()
{
	std::vector<std::string> products;
	
	std::map<std::string, bool> prodMap;

	for (const OrderBookEntry& e : orders)
	{
		prodMap[e.product] = true;
	}

	//now flatten the map to a vector of strings
	for (const auto& e : prodMap)
	{
		products.push_back(e.first);
	}

	return products;
}

//from example code
/** return vector of Orders according to the sent filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
												 std::string product,
												 std::string timestamp)
{
	std::vector<OrderBookEntry> orders_sub;
	for (OrderBookEntry& e : orders)
	{
		if (e.orderType == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}
	return orders_sub;
}

//from example code
/** return the price of the highest bid or ask in the sent set */
double OrderBook::getHighPrice(std::vector < OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price > max) max = e.price;
	}
	return max;
}

//from example code
/** return the price of the lowest bid or ask in the sent set */
double OrderBook::getLowPrice(std::vector < OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price < min) min = e.price;
	}
	return min;
}

/** return the sum of price squared divided orders size in the sent set */
double OrderBook::getSumForVariance(std::vector < OrderBookEntry>& orders)
{
	double total = 0;
	for (OrderBookEntry& e : orders)
	{
		total += e.price * e.price;
	}
	return total / orders.size();
}

/** return the price of the average bid or ask in the sent set */
double OrderBook::getAveragePrice(std::vector < OrderBookEntry>& orders)
{
	double total = 0;
	for (OrderBookEntry& e : orders)
	{
		total = total + e.price;
	}
	return total / orders.size();
}

//from example code
/** return the earliest time in the orderbook */
std::string OrderBook::getEarliestTime()
{
	return orders[0].timestamp;
}

//from example code
/** return the next time after the sent time in the orderbook 
    If there is no next timestamp, wraps around to the start */
std::string OrderBook::getNextTime(const std::string& timestamp)
{
	std::string next_timestamp = "";
	for (OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;
			break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = getEarliestTime();
	}
	return next_timestamp;
}

/** return the previous time after the sent time in the orderbook
    If there is no previous timestamp, it stops at the earliest time in the orderbook */
std::string OrderBook::getPreviousTime(const std::string& timestamp)
{
	std::string prev_timestamp = "";
	for (int i = orders.size() - 1; i >= 0; --i)
	{
		if (orders[i].timestamp < timestamp)
		{
			prev_timestamp = orders[i].timestamp;
			break;
		}
	}
	return prev_timestamp;
}
