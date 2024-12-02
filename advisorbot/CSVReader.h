//from example code
#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
	public:
		CSVReader();
		/** converts data in the CSV file to OrderBookEntry */
		static std::vector<OrderBookEntry> readCSV(std::string csvFile);
		/** tokenise -- breaks content in the string into a vector */
		static std::vector<std::string> tokenise(std::string csvLine, char separator);

	private:
		/** converts string to OrderBookEntry */
		static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};