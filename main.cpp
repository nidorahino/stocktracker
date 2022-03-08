/*
* This code contains the main for the StockTracker project. This program can help a user analyze multiple stocks at once by just inputting 
* the stock tickers. The program will ask the user for the number of stocks to retrieve information about and the tickers for those stocks. 
* The program will then return several key statistics about each of those stocks printed to console and a file named after the stock ticker.
* Created by Rahin Rahman.
*/

#define CURL_STATICLIB

#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "stock.h"

using namespace std;

class CurlObj {
public:

    CurlObj(string url) {
        curl = curl_easy_init(); //Initializes the curl handle.

        //Set options.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //Sets the URL to the yahoo page of the stock. 
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); //Follows HTTP redirect.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlObj::curlWriter); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer); //Determines the data we pulled is held in curlBuffer until used in our Stock object.

        //Performs the actions
        curl_easy_perform(curl);
    };


    //Callback function. Called by libcurl when there is data that needs to be saved where data is the delivered data, 
    //nmemb is the size of the data, and size is always 1. 
    static int curlWriter(char* data, int size, int nmemb, string* buffer) {
        int result = 0;
        if (buffer != NULL) {
            buffer->append(data, size * nmemb);
            result = size * nmemb;
        }

        return result;
    }

    string getData() {
        return curlBuffer;
    }

private:
    CURL* curl; //Curl handle.
    string curlBuffer;
};

int main() {



    string numTickersString;

    cout << "How many stocks would you like to analyze?: ";
    int numTickers = -1; //Initialized to -1 so that we enter the while loop. 

    //Until we have a valid amount of companies, the program will keep asking the user for a number. 
    while (numTickers < 0) {
        try {
            cin >> numTickersString;
            numTickers = stoi(numTickersString); //Converts the input into an int. 
            if (numTickers < 0) {
                cout << "Invalid input. Please enter a number greater than 0: ";
            }
        }
        catch (exception e) {
            cout << "Invalid input. Please enter a number greater than 0: ";
        }
    }

    //Container of all the tickers that were input.
    vector<string> tickers;

    //Ask the users for a number of tickers matching the number input earlier.
    for (int i = 0; i < numTickers; ++i) {
        string name;
        cout << "Enter the ticker for a stock: ";
        cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::tolower); //Turns the entire input into lowercase. 
        tickers.push_back(name);
    }

    //Container of the Stock objects. 
    vector<Stock> stocks;

    //For each of the tickers that the user input, the program attempts to connect to a yahoo stock page for the ticker
    for (size_t i = 0; i < tickers.size(); i++) {
        string currentTicker = tickers[i];
        string address = "https://finance.yahoo.com/quote/" + currentTicker;
        CurlObj temp(address); //Creates a temporary curlobj object passing in the url of the yahoo stock page.
        try {
            Stock data = Stock::Stock(currentTicker, temp.getData());
            data.parseHtml(); //Fills the current stock object with data about the stock.
            data.printStock(); //Prints the data that was found about the stock.
        }
        catch (exception e) {
            //If the ticker is not on yahoo, the program outputs that the ticker was invalid.
            cout << currentTicker << " is not a valid ticker." << endl;
        }
    }

    return 0;
}