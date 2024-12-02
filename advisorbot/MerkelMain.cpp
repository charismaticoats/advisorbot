#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{

}

//from example code
void MerkelMain::init()
{
    std::vector<std::string> input;
    int mode = 0;
    currentTime = orderBook.getEarliestTime();
    while (true)
    {
        printMenu();
        input = getUserOption();
        mode = checkCommand(input);
        processUserOption(mode, input);
    }
}

/** print initial instructions */
void MerkelMain::printMenu()
{
    const char* BG_BLUE = "\033[44m";
    std::cout << BG_BLUE << "======================================================================" << std::endl;
    std::cout << "Please enter a command, or help for a list of all available commands. " << std::endl;
    std::cout << "======================================================================" << std::endl;
}

/** tokenise user input */
std::vector<std::string> MerkelMain::getUserOption()
{
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ' ');

    return tokens;
}

/** check which the command user input */
int MerkelMain::checkCommand(std::vector<std::string> tokens)
{
    int userOption = 0;

    if (tokens[0] == "help") {
        if (tokens.size() == 1)
        {
            //help
            userOption = 1;
        }
        else
        {
            //help cmd
            userOption = 2;
        }
    }
    else if (tokens[0] == "prod") {
        userOption = 3;
    }
    else if (tokens[0] == "min") {
        userOption = 4;
    }
    else if (tokens[0] == "max") {
        userOption = 5;
    }
    else if (tokens[0] == "avg") {
        userOption = 6;
    }
    else if (tokens[0] == "predict") {
        userOption = 7;
    }
    else if (tokens[0] == "time") {
        userOption = 8;
    }
    else if (tokens[0] == "step") {
        userOption = 9;
    }
    else if (tokens[0] == "variance") {
        userOption = 10;
    }
    else {
        std::cout << "Invalid choice." << std::endl;
    }
    return userOption;
}

//from example code
/** call different functions depending on user input */
void MerkelMain::processUserOption(int userOption, std::vector<std::string> tokens)
{
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printHelpCMD(tokens);
    }
    if (userOption == 3)
    {
        printProd();
    }
    if (userOption == 4)
    {
        printMin(tokens);
    }
    if (userOption == 5)
    {
        printMax(tokens);
    }
    if (userOption == 6)
    {
        printAvg(tokens);
    }
    if (userOption == 7)
    {
        printPredict(tokens);
    }
    if (userOption == 8)
    {
        printTime();
    }
    if (userOption == 9)
    {
        printStep();
    }
    if (userOption == 10)
    {
        printVariance(tokens);
    }
}

//from example code
/** print all available commands */
void MerkelMain::printHelp()
{
    std::cout << "The available commands are help, help <cmd>, prod, min, max, avg, predict, time, step, variance. " << std::endl;
}

/** explain all available commands */
void MerkelMain::printHelpCMD(std::vector<std::string> tokens)
{
    if (tokens.size() != 2)
    {
        std::cout << "MerkelMain::printHelpCMD Bad input ! " << std::endl;
    }
    else
    {
        if (tokens[1] == "prod") 
        {
            std::cout << "This command lists available products. " << std::endl;
        }
        else if (tokens[1] == "min") 
        {
            std::cout << "Command: min product ask/bid, e.g. min ETH/BTC ask " << std::endl;
            std::cout << "This command finds the minimum ask or bid for the sent product in the current time step. " << std::endl;
        }
        else if (tokens[1] == "max")
        {
            std::cout << "Command: max product ask/bid, e.g. max ETH/BTC ask " << std::endl;
            std::cout << "This command finds the maximum ask or bid for the sent product in the current time step. " << std::endl;
        }
        else if (tokens[1] == "avg")
        {
            std::cout << "Command: avg product ask/bid timesteps, e.g. avg ETH/BTC ask 10 " << std::endl;
            std::cout << "This command computes the average ask or bid for the sent product over the sent number of time steps. " << std::endl;
        }
        else if (tokens[1] == "predict")
        {
            std::cout << "Command: predict max/min product ask/bid, e.g. predict max ETH/BTC bid " << std::endl;
            std::cout << "This command predicts the maximum or minimum ask or bid for the sent product for the next time step. " << std::endl;
        }
        else if (tokens[1] == "time")
        {
            std::cout << "This command states current time in dataset, i.e. which timeframe we are looking at. " << std::endl;
        }
        else if (tokens[1] == "step")
        {
            std::cout << "This command moves to the next time step. " << std::endl;
        }
        else if (tokens[1] == "variance")
        {
            std::cout << "Command: variance product ask/bid, e.g. variance ETH/BTC bid " << std::endl;
            std::cout << "This command computes the variance of ask or bid for the sent product in the current time step. " << std::endl;
        }
        else
        {
            std::cout << "MerkelMain::printHelpCMD Bad input ! " << std::endl;
        }
    }
}

/** print all available products */
void MerkelMain::printProd()
{
    std::cout << "listing available products" << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << p << std::endl;
    }
}

/** print minimum ask or bid for the sent product in the current time step */
void MerkelMain::printMin(std::vector<std::string> tokens)
{
    //to print error to console
    int flag = 0;
    //to see if all products have been checked against user input
    int counter = 0;

    if (tokens.size() != 3)
    {
        flag = 1;
    }
    else
    {
        std::string product = tokens[1];
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (product == p) 
            {
                if (tokens[2] == "ask") 
                {
                    //from example code
                    std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                           p, currentTime);
                    std::cout << "Min ask for " << p << ": " << OrderBook::getLowPrice(asks) << std::endl;
                }
                else if (tokens[2] == "bid") 
                {
                    //from example code
                    std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                                           p, currentTime);
                    std::cout << "Min bid for " << p << ": " << OrderBook::getLowPrice(bids) << std::endl;
                }
                else
                {
                    flag = 1;
                    //orderBookType not found
                }
            }
            else
            {
                counter++;
                if (counter == orderBook.getKnownProducts().size()) 
                {
                    flag = 1;
                    //product not found
                }
            }
        }
    }

    if (flag == 1)
    {
        std::cout << "MerkelMain::printMin Bad input ! " << std::endl;
    }
}

/** print maximum ask or bid for the sent product in the current time step */
void MerkelMain::printMax(std::vector<std::string> tokens)
{
    //to print error to console
    int flag = 0;
    //to see if all products have been checked against user input
    int counter = 0;

    if (tokens.size() != 3)
    {
        flag = 1;
    }
    else
    {
        std::string product = tokens[1];
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (product == p)
            {
                if (tokens[2] == "ask")
                {
                    //from example code
                    std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                           p, currentTime);
                    std::cout << "Max ask for " << p << ": " << OrderBook::getHighPrice(asks) << std::endl;
                }
                else if (tokens[2] == "bid")
                {
                    //from example code
                    std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                                           p, currentTime);
                    std::cout << "Max bid for " << p << ": " << OrderBook::getHighPrice(bids) << std::endl;
                }
                else
                {
                    flag = 1;
                    //orderBookType not found
                }
            }
            else
            {
                counter++;
                if (counter == orderBook.getKnownProducts().size())
                {
                    flag = 1;
                    //product not found
                }
            }
        }
    }

    if (flag == 1)
    {
        std::cout << "MerkelMain::printMax Bad input ! " << std::endl;
    }
}

/** print variance of ask or bid for the sent product in the current time step */
void MerkelMain::printVariance(std::vector<std::string> tokens)
{
    //to print error to console
    int flag = 0;
    //to see if all products have been checked against user input
    int counter = 0;
    double variance = 0;

    if (tokens.size() != 3)
    {
        flag = 1;
    }
    else
    {
        std::string product = tokens[1];
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (product == p)
            {
                if (tokens[2] == "ask")
                {
                    std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                           p, currentTime);
                    variance = OrderBook::getSumForVariance(asks) - ((OrderBook::getAveragePrice(asks)) * (OrderBook::getAveragePrice(asks)));
                    std::cout << "Variance of ask for " << p << ": " << variance << std::endl;
                }
                else if (tokens[2] == "bid")
                {
                    std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                                           p, currentTime);
                    variance = OrderBook::getSumForVariance(bids) - ((OrderBook::getAveragePrice(bids)) * (OrderBook::getAveragePrice(bids)));
                    std::cout << "Variance of bid for " << p << ": " << variance << std::endl;
                }
                else
                {
                    flag = 1;
                    //orderBookType not found
                }
            }
            else
            {
                counter++;
                if (counter == orderBook.getKnownProducts().size())
                {
                    flag = 1;
                    //product not found
                }
            }
        }
    }

    if (flag == 1)
    {
        std::cout << "MerkelMain::printVariance Bad input ! " << std::endl;
    }
}

/** print average ask or bid for the sent product over the sent number of time steps */
void MerkelMain::printAvg(std::vector<std::string> tokens)
{
    //to print error to console
    int flag = 0;
    //to see if all products have been checked against user input
    int counter = 0;
    //from user input
    int timesteps = 0;
    //to calculate the average accurately, if there are lesser timesteps ran than value from user input
    int rounds = 0;
    //to not intefere with the current time of advisorbot
    std::string storeTime = currentTime;
    double total = 0;
    double average = 0;
    

    if (tokens.size() != 4)
    {
        flag = 1;
    }
    else
    {
        std::string product = tokens[1];
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (product == p)
            {
                if (tokens[2] == "ask")
                {
                    try {
                        timesteps = std::stoi(tokens[3]);
                    }
                    catch (const std::exception& e)
                    {
                        flag = 1;
                        //cannot convert string to integer
                    }
                    for (int i = 0; i < timesteps; ++i)
                    {
                        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                                p, storeTime);
                        total += OrderBook::getAveragePrice(asks);
                        rounds++;
                        storeTime = orderBook.getPreviousTime(storeTime);
                        //if there is no previous timestamp, stops at the earliest time in the orderbook
                        if (storeTime == "")
                        {
                            break;
                        }
                    }
                    average = total / rounds;
                    std::cout << "Average " << p << " ask price over the last " << timesteps << " timesteps: " << average << std::endl;
                }
                else if (tokens[2] == "bid")
                {
                    try {
                        timesteps = std::stoi(tokens[3]);
                    }
                    catch (const std::exception& e)
                    {
                        flag = 1;
                        //cannot convert string to integer
                    }
                    for (int i = 0; i < timesteps; ++i)
                    {
                        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                                                p, storeTime);
                        total += OrderBook::getAveragePrice(bids);
                        rounds++;
                        storeTime = orderBook.getPreviousTime(storeTime);
                        //if there is no previous timestamp, stops at the earliest time in the orderbook
                        if (storeTime == "")
                        {
                            break;
                        }
                    }
                    average = total / rounds;
                    std::cout << "Average " << p << " bid price over the last " << timesteps << " timesteps: " << average << std::endl;
                }
                else
                {
                    flag = 1;
                    //orderBookType not found
                }
            }
            else
            {
                counter++;
                if (counter == orderBook.getKnownProducts().size())
                {
                    flag = 1;
                    //product not found
                }
            }
        }
    }

    if (flag == 1)
    {
        std::cout << "MerkelMain::printAvg Bad input ! " << std::endl;
    }
}

/** print prediction of the maximum or minimum ask or bid for the sent product for the next time step */
void MerkelMain::printPredict(std::vector<std::string> tokens)
{
    //to print error to console
    int flag = 0;
    //to see if all products have been checked against user input
    int counter = 0;
    //to not intefere with the current time of advisorbot
    std::string storeTime = currentTime;
    double predict = 0;

    if (tokens.size() != 4)
    {
        flag = 1;
    }
    else
    {
        std::string product = tokens[2];
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (product == p)
            {
                if (tokens[3] == "ask")
                {
                    //if there is no previous timestamp
                    if (currentTime != orderBook.getEarliestTime())
                    {
                        //previous time data
                        storeTime = orderBook.getPreviousTime(storeTime);
                        std::vector<OrderBookEntry> asksPrev = orderBook.getOrders(OrderBookType::ask,
                                                                                    p, storeTime);
                        //current time data
                        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                               p, currentTime);
                        if (tokens[1] == "max")
                        {
                            predict = 0.4 * OrderBook::getHighPrice(asksPrev) + 0.6 * OrderBook::getHighPrice(asks);

                            std::cout << "Predict max " << p << " ask price to be " << predict << std::endl;
                        }
                        else if (tokens[1] == "min")
                        {
                            predict = 0.4 * OrderBook::getLowPrice(asksPrev) + 0.6 * OrderBook::getLowPrice(asks);

                            std::cout << "Predict min " << p << " ask price to be " << predict << std::endl;
                        }
                        else
                        {
                            flag = 1;
                            //max or min not found
                        }
                    }
                    else 
                    {
                        if (tokens[1] == "max") {
                            std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                                   p, currentTime);
                            std::cout << "Predict max " << p << " ask price to be " << OrderBook::getHighPrice(asks) << std::endl;
                        }
                        else if (tokens[1] == "min") {
                            std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                                                   p, currentTime);
                            std::cout << "Predict min " << p << " ask price to be " << OrderBook::getLowPrice(asks) << std::endl;
                        }
                        else
                        {
                            flag = 1;
                            //max or min not found
                        }
                    }
                }
                else if (tokens[3] == "bid")
                {
                    if (currentTime != orderBook.getEarliestTime())
                    {
                        //previous time data
                        storeTime = orderBook.getPreviousTime(storeTime);
                        std::vector<OrderBookEntry> bidsPrev = orderBook.getOrders(OrderBookType::bid,
                                                                                   p, storeTime);
                        //current time data
                        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                                               p, currentTime);
                        if (tokens[1] == "max")
                        {
                            predict = 0.4 * OrderBook::getHighPrice(bidsPrev) + 0.6 * OrderBook::getHighPrice(bids);

                            std::cout << "Predict max " << p << " bid price to be " << predict << std::endl;
                        }
                        else if (tokens[1] == "min")
                        {
                            predict = 0.4 * OrderBook::getLowPrice(bidsPrev) + 0.6 * OrderBook::getLowPrice(bids);

                            std::cout << "Predict min " << p << " bid price to be " << predict << std::endl;
                        }
                        else
                        {
                            flag = 1;
                            //max or min not found
                        }
                    }
                    else
                    {
                        if (tokens[1] == "max") {
                            std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                p, currentTime);
                            std::cout << "Predict max " << p << " bid price to be " << OrderBook::getHighPrice(bids) << std::endl;
                        }
                        else if (tokens[1] == "min") {
                            std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                p, currentTime);
                            std::cout << "Predict min " << p << " bid price to be " << OrderBook::getLowPrice(bids) << std::endl;
                        }
                        else
                        {
                            flag = 1;
                            //max or min not found
                        }
                    }
                }
                else
                {
                    flag = 1;
                    //orderBookType not found
                }
            }
            else
            {
                counter++;
                if (counter == orderBook.getKnownProducts().size())
                {
                    flag = 1;
                    //product not found
                }
            }
        }
    }

    if (flag == 1)
    {
        std::cout << "MerkelMain::printAvg Bad input ! " << std::endl;
    }

}

//from example code
/** print current time in dataset, i.e. which timeframe we are looking at */
void MerkelMain::printTime()
{
    std::cout << "Current time is: " << currentTime << std::endl;
}

//from example code
/** move to the next time frame */
void MerkelMain::printStep()
{
    std::cout << "Going to next time frame. " << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Current time is: " << currentTime << std::endl;
}

