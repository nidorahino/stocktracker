/*  
* Header file of the Stock class in the StockTracker project.
* Created by Rahin Rahman. 
*/

#ifndef stock_h
#define stock_h

#include <string>
#include <fstream>

using namespace std;

class Stock {
private:

    //Contains all the html from the respective stock page
    string html;

    //Stock full name including (ticker)
    string stockName;

    string ticker;
    double currentPrice;
    double dayLow;
    double dayHigh;
    double priceChange;
    double changePercent;
    double peRatio;

public:

    /**
     * Parameterized constructor for the Stock object. 
     *
     * @param NAME String holding the ticker of the stock.
     * @param HTML String containing all the html from the stock page. 
     */
    Stock(string NAME, string HTML);

    /**
     * Parses through the html string and stores the relevant information inside of data members that will be printed by the printData function.
     */
    void parseHtml();

    /**
     * Prints out all the relevant data about the stock that was stored by the parseHtml function. 
     */
    void printStock();
};

#endif
