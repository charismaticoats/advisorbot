//from example code
#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{
	
}

/** converts data in the CSV file to OrderBookEntry */
std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
	std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{ csvFilename };
    std::string line;
    std::vector<std::string> tokens;

    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception& e) {
                //std::cout << "CSVReader::readCSV bad data " << std::endl;
            }
        }
        csvFile.close();
    }
    //std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
	return entries;
}

/** tokenise -- breaks content in the string into a vector */
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    // used to delineate the postion of the tokens
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        //nothing more to find
        if (start == csvLine.length() || start == end) break;
        //we found the separator
        if (end >= 0) token = csvLine.substr(start, end - start);
        //end is invalid
        else token = csvLine.substr(start, csvLine.length() - start);
        //save the token
        tokens.push_back(token);
        //move past this token
        start = end + 1;
        //continue loop condition
    } while (end != std::string::npos);

    return tokens;
}

/** converts string to OrderBookEntry */
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        //std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    //we have 5 tokens
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE Bad float!" << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float!" << tokens[4] << std::endl;
        throw;
    }
	OrderBookEntry obe{ price,
						amount,
						tokens[0],
						tokens[1],
						OrderBookEntry::stringToOrderBookType(tokens[2])};
	return obe;
}

