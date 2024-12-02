#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain {
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

private:
    /** print initial instructions */
    void printMenu();
    /** print all available commands */
    void printHelp();
    /** explain all available commands */
    void printHelpCMD(std::vector<std::string> tokens);
    /** print all available products */
    void printProd();
    /** print minimum ask or bid for the sent product in the current time step */
    void printMin(std::vector<std::string> tokens);
    /** print maximum ask or bid for the sent product in the current time step */
    void printMax(std::vector<std::string> tokens);
    /** print variance of ask or bid for the sent product in the current time step */
    void printVariance(std::vector<std::string> tokens);
    /** print average ask or bid for the sent product over the sent number of time steps */
    void printAvg(std::vector<std::string> tokens);
    /** print prediction of the maximum or minimum ask or bid for the sent product for the next time step */
    void printPredict(std::vector<std::string> tokens);
    /** print current time in dataset, i.e. which timeframe we are looking at */
    void printTime();
    /** move to the next time frame */
    void printStep();

    /** tokenise user input */
    std::vector<std::string> getUserOption();
    /** check which command user input */
    int checkCommand(std::vector<std::string> tokens);
    /** call different functions depending on user input */
    void processUserOption(int userOption, std::vector<std::string> tokens);

    std::string currentTime;

    // CSV data file we are using
    OrderBook orderBook{ "20200601.csv" };

};