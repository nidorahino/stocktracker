/*
* Implementation of the Stock class for the StockTracker project.
* Created by Rahin Rahman.
*/

#include "stock.h"
#include <iostream>
#include <fstream>

using namespace std;

//Parameterized constructor that will save the ticker and the entire html of the respective stock page as a data member. 
Stock::Stock(string NAME, string HTML) {
    ticker = NAME;
    html = HTML;
}

void Stock::parseHtml() {

    //These strings contain reference html near the data that we are looking for.
    string stockNameFinder = "Find the latest ";
    string currentPriceFinder = "currentPrice";
    string daysRangeFinder = "DAYS_RANGE-value";
    string priceChangeFinder = "FIN_TICKER_PRICE_CHANGE_AMOUNT";
    string changePercentFinder = "FIN_TICKER_PRICE_CHANGE_PERCENT";
    string peRatioFinder = "PE_RATIO-value";

    //We find our reference html in the larger stored html string, and store an index for where the actual data we are searching for begins.
    size_t stockNameIndex = html.find(stockNameFinder) + 16;
    size_t currentPriceIndex = html.find(currentPriceFinder) + 21;
    size_t daysRangeIndex = html.find(daysRangeFinder) + 18;
    size_t priceChangeIndex = html.find(priceChangeFinder) + 43;
    size_t changePercentIndex = html.find(changePercentFinder) + 44;
    size_t peRatioIndex = html.find(peRatioFinder) + 16;

    //We use the stored index to create a substring containing the data we were looking for. 
    //20 is used as a default because no individual piece of data except stock name exceeds 20 characters.
    string stockNameString = html.substr(stockNameIndex, 40);
    string currentPriceString = html.substr(currentPriceIndex, 20);
    string daysRangeString = html.substr(daysRangeIndex, 20);
    string priceChangeString = html.substr(priceChangeIndex, 20);
    string changePercentString = html.substr(changePercentIndex, 20);
    string peRatioString = html.substr(peRatioIndex, 20);

    //Using a new index, we find where our data ends and resize our string to fit only the data we were searching for. 
    size_t characterIndex = currentPriceString.find(',', 0);
    currentPriceString.resize(characterIndex);

    characterIndex = stockNameString.find(')', 0) + 1;
    stockNameString.resize(characterIndex);

    characterIndex = priceChangeString.find('&', 0);
    priceChangeString.resize(characterIndex);

    characterIndex = changePercentString.find('%', 0);
    changePercentString.resize(characterIndex);

    characterIndex = peRatioString.find('<', 0);
    peRatioString.resize(characterIndex);

    characterIndex = daysRangeString.find('<', 0);
    daysRangeString.resize(characterIndex);

    //Iterates over the day range string to get rid of unwanted characters (commas).
    for (int i = 0; i < daysRangeString.size(); i++) {
        if (daysRangeString[i] == ',')
            daysRangeString.erase(i, 1);
    }

    //We can then create substrings of the range to find the 24 hour low and 24 hour high for this stock.
    //Stod is used to turn the strings into doubles.
    characterIndex = daysRangeString.find(' ', 0);
    dayLow = stod(daysRangeString.substr(0, characterIndex + 1));
    dayHigh = stod(daysRangeString.substr(characterIndex + 3, daysRangeString.size()));

    stockName = stockNameString;
    currentPrice = stod(currentPriceString);
    priceChange = stod(priceChangeString);
    changePercent = stod(changePercentString);
    peRatio = stod(peRatioString);
}


//Prints all the data that is now stored as data members of the stock object. 
void Stock::printStock() {
    //Prints to console.
    cout << endl << stockName << ": " << endl;
    cout << "Current Price: " << currentPrice << endl;
    cout << "24 Hour Range (Low/High): " << dayLow << " / " << dayHigh << endl;
    cout << "Price Change: " << priceChange << endl;
    cout << "Price Change Percentage: " << changePercent << endl;
    cout << "PE (Price to Earnings) Ratio: " << peRatio << endl << endl;

    //Prints to an output file (ticker).txt
    ofstream outputFile(ticker + ".txt");
    outputFile << endl << stockName << ": " << endl;
    outputFile << "Current Price: " << currentPrice << endl;
    outputFile << "24 Hour Range (Low/High): " << dayLow << " / " << dayHigh << endl;
    outputFile << "Price Change: " << priceChange << endl;
    outputFile << "Price Change Percentage: " << changePercent << endl;
    outputFile << "PE (Price to Earnings) Ratio: " << peRatio << endl << endl;
    outputFile.close();
}





