//from example code
#pragma once
#include <string>

enum class OrderBookType { bid, ask, unknown };

class OrderBookEntry // this is the name of the class
{
public: // parts of the class that can be seen from outside
    OrderBookEntry(double _price,  // this is a data member (AKA a variable inside a class)
                   double _amount,
                   std::string _timestamp,
                   std::string _product,
                   OrderBookType _orderType);
    
    /** converts string to OrderBookType */
    static OrderBookType stringToOrderBookType(const std::string& s);

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};