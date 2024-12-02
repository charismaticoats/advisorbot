#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
	public:
		/** construct, reading a csv file */
		OrderBook(std::string filename);
		/** return vector of all known products in the datasets */
		std::vector<std::string> getKnownProducts();
		/** return vector of Orders according to the sent filters */
		std::vector<OrderBookEntry> getOrders(OrderBookType type, 
											  std::string product,
											  std::string timestamp);
		/** return the earliest time in the orderbook */
		std::string getEarliestTime();
		/** return the next time after the sent time in the orderbook 
		If there is no next timestamp, wraps around to the start */
		std::string getNextTime(const std::string& timestamp);
		/** return the previous time after the sent time in the orderbook
		If there is no previous timestamp, it stops at the earliest time in the orderbook */
		std::string getPreviousTime(const std::string& timestamp);
		
		/** return the price of the highest bid or ask in the sent set */
		static double getHighPrice(std::vector < OrderBookEntry>& orders);
		/** return the price of the lowest bid or ask in the sent set */
		static double getLowPrice(std::vector < OrderBookEntry>& orders);
		/** return the price of the average bid or ask in the sent set */
		static double getAveragePrice(std::vector < OrderBookEntry>& orders);
		/** return the sum of price squared divided orders size in the sent set */
		static double getSumForVariance(std::vector < OrderBookEntry>& orders);

	private:
		std::vector<OrderBookEntry> orders;
};