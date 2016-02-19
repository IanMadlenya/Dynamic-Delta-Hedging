/*
* Name: Chinmay Rane
* GT ID: 903156331
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "StdNormalCDF.h"
#include "Payoff.h"
#include "OptionVanilla.h"
#include "BlackScholes.h"
#include "Random.h"
//#include <ql/quantlib.hpp>

using namespace std;
//using namespace boost;
//using namespace QuantLib;

double stringToDouble(string s) {
    double d;
    stringstream ss(s); //turn the string into a stream
    ss >> d; //convert
    return d;
}

//Convert DOuble to String
string doubleToString(double d){
    stringstream strs;
    strs<< d;
    string str = strs.str();
    return str;

}

int main(int argc, const char * argv[]) {

    cout<<"Mid Term Project"<<endl;

    double S = 100.0;  // Option price spot price
    double K = 105.0;  // Strike price
    double r = 0.025;   // Risk-free rate (5%)
    double v = 0.24;    // Volatility of the underlying (20%)
    double T = 0.4;    // One year until expiry
    double q = 0.0;    // Dividend Yield

    cout<<endl;

    double mean = 0.05;
    double intervals = 100;
    double delta_time = (T/intervals);
    double putOptionValueTemp;
    double callDelta;
    double betaTemp;
    double hedgeErrorTemp;
    double tempVal;
    double deltaValTemp;

    vector <double> simulatePrice;
    vector <double> blackScholesPrices;
    vector <double> blackScholesDeltaPrices;
    vector <double> betaVal;
    vector <double> hedgeError;
    vector <double> hedginePortfolio;
    vector <double> stockToBuy;

    ofstream HedgingFile ("hedging.csv"); //Opening file to print info to
    HedgingFile << "Hedging Portfolio" << endl; //Headings for file
    HedgingFile << "Simulated Stock Price"<<","<< "Option Prices"<<","<<"Delta Value"<<","<<"Hedging Error"<<","<<"Stock to Buy"<<","<<"Risk Free Rate Borrow"<<endl;


    // Simulate the Time Series
    simulatePrice.push_back(100);

    PayoffVanilla payoff_call(OptionVanilla::Call,K);
    OptionVanilla option_call(payoff_call, T);

    putOptionValueTemp = BlackScholes(option_call, S, v, r,q);

    blackScholesPrices.push_back(putOptionValueTemp);

    deltaValTemp = BlackScholesDelta(option_call, S, v, r, q);

    blackScholesDeltaPrices.push_back(deltaValTemp);

    betaTemp = blackScholesPrices[0] - ((T/intervals) * S);

    betaVal.push_back(betaTemp);

    for(int i=0; i<100; i++){

        cout<<"***********************Start****************************"<<endl;
        //Simulate Values
        tempVal = simulatePrice[i] + (mean * simulatePrice[i]* (T/intervals)) + (v * simulatePrice[i] * sqrt((T/intervals)) * DrawNormal());
        simulatePrice.push_back(tempVal);
        cout<<"Simulated Stock Price : "<<simulatePrice[i]<<endl;
        HedgingFile << simulatePrice[i] <<",";

        //Dynamic Delta Hedging
        callDelta = T - ((i+1)*delta_time);

        //Set the PayOff Vanilla
        PayoffVanilla payoff_call(OptionVanilla::Call,K);
        OptionVanilla option_call(payoff_call, callDelta);

        //Calculate BlackScholes Model
        putOptionValueTemp = BlackScholes(option_call, simulatePrice[i+1], v, r,q);
        blackScholesPrices.push_back(putOptionValueTemp);

        cout <<"Black Scholes Option Price : " <<blackScholesPrices[i+1] << endl;
        HedgingFile << blackScholesPrices[i] <<",";

        //Delta Value
        deltaValTemp = BlackScholesDelta(option_call, simulatePrice[i+1], v, r, q);

        blackScholesDeltaPrices.push_back(deltaValTemp);
        cout <<"Delta Value : " <<blackScholesDeltaPrices[i+1] << endl;
        HedgingFile << blackScholesDeltaPrices[i] <<",";

        //Calculate B VALue and HEdging Error
        betaTemp = blackScholesPrices[i] - (blackScholesDeltaPrices[i] * simulatePrice[i]);
        hedgeErrorTemp = (blackScholesDeltaPrices[i] * simulatePrice[i+1] ) + (betaTemp * exp((r*(T/intervals)))) - blackScholesPrices[i+1];

        hedgeError.push_back(hedgeErrorTemp);

        cout <<"Hedge Error : " <<hedgeError[i] << endl;
        if(i==0){
            HedgingFile << 0 <<",";
        }else{
            HedgingFile << hedgeError[i] <<",";
        }

        //Hedging Portfolio No of Stocks to Buy + Borrow Risk Frere Bonds
        stockToBuy.push_back((blackScholesDeltaPrices[i] * simulatePrice[i]));
        hedginePortfolio.push_back((blackScholesPrices[i] - (blackScholesDeltaPrices[i] * simulatePrice[i])));

        cout<<"Stock to buy : "<<stockToBuy[i]<<endl;
        HedgingFile << stockToBuy[i] <<",";
        cout<<"Risk Free Bonds : "<<hedginePortfolio[i]<<endl;
        HedgingFile << hedginePortfolio[i] <<endl;

        cout<<"**********************End*******************************"<<endl;
        cout<<endl;
    }

    //Cumulative Hedging Error
    double cumulativehedge;
    for(int k=0; k<hedgeError.size();k++){
        cumulativehedge +=hedgeError[k];
    }
    cout<<"The cumulative Hedging Error is : "<<cumulativehedge<<endl;
    HedgingFile<<"Cumulative Hedging Error"<<","<<cumulativehedge<<endl;
    HedgingFile.close();

    //Part 2

    //File1
    ifstream infile("./interest.csv");
    string line;
    vector<string> date;
    vector<double> rate;

    //Declared for storing the double value after it's conversion from string
    double cellConverted;
    while(getline(infile,line))
    {
        if(line[0]== 'd'){
                //Do Nothing
        }else{
            stringstream lineStream(line);
            string cell;
            int counter = 0;
            while(getline(lineStream,cell,','))
            {
                if(counter %2 ==0){
                    date.push_back(cell);
                    }
                else{
                    cellConverted = stringToDouble(cell);
                    rate.push_back((cellConverted/100));
                }
                counter++;
            }
        }
    }// End while
    infile.close();

    //File2
    ifstream closeRateFile("./sec_GOOG.csv");
    vector<string> date_Goog;
    vector<double> close_rate;

    while(getline(closeRateFile,line))
    {
            if(line[0]== 'd'){
                //Do Nothing
            }else{
            stringstream lineStream(line);
            string cell;
            int counter = 0;

            while(getline(lineStream,cell,','))
            {
                if(counter %2 ==0){
                    date_Goog.push_back(cell);
                }
                else{
                    cellConverted = stringToDouble(cell);
                    close_rate.push_back(cellConverted);
                }
                counter++;
            }
        }
    }// End while
    closeRateFile.close();

    //Read 3rd File
    //6 Columns
    //Average of last two columns is the option price
    ifstream excerciseFile("./op_GOOG.csv");
    vector<string> date_purchase;
    vector<string> date_expiry;
    vector<string> optionType;
    vector<double> strike_price;
    vector<double> bid_price;
    vector<double> ask_price;
    double convert_bid_price;
    double convert_ask_price;
    double convert_strike_price;
    double closingPrice;

    while(getline(excerciseFile,line))
    {
         if(line[0]== 'd'){
            }else{
            stringstream lineStream(line);
            string cell;
            int counter = 0;
            while(getline(lineStream,cell,','))
            {
                if(counter == 0){
                date_purchase.push_back(cell);
                    counter++;
                }else if(counter == 1){
                    date_expiry.push_back(cell);
                    counter++;
                }else if(counter == 2){
                    optionType.push_back(cell);
                    counter++;
                }else if(counter == 3){
                    convert_strike_price = stringToDouble(cell);
                    strike_price.push_back(convert_strike_price);
                    counter++;
                }else if(counter == 4){
                    convert_bid_price = stringToDouble(cell);
                    bid_price.push_back(convert_bid_price);
                    counter++;
                }else if(counter == 5){
                    convert_ask_price= stringToDouble(cell);
                    closingPrice = (convert_bid_price + convert_ask_price)/2;
                    ask_price.push_back(closingPrice);
                    counter++;
                }
              }
             counter=0;
           }
        }// End while

  excerciseFile.close();


//Change Parameters here
//Can change to user based Input
string t0 = "2011-07-05";
string tn = "2011-07-29";
string texp = "2011-09-17";


//Separating Vectors
vector <string> dateDisect;
vector <double> rateDisect;
vector <double> stockPriceDisect;
double strike_given =500.0;
double startDateIndex, endDateIndex;
vector <double> returnPrices;
double businessDays;
string newExpiryDate = texp;
string new2ExpiryDate = texp;

//Friday, Saturday,Sunday phenomena as explained in the write up
for (int l=0; l<date.size(); l++)
    {
        if(texp != date[l])
        {
            string day0(1,texp[8]);
            string day1(1,texp[9]);
            string dayTotal = day0 + day1;
            double dayDouble   = stringToDouble(dayTotal);
            dayDouble = dayDouble-1;
            string dayString = doubleToString(dayDouble);
            newExpiryDate[8]= dayString[0];
            newExpiryDate[9]= dayString[1];
                for (int l=0; l<date.size(); l++)
                    {
                        if(newExpiryDate!= date[l])
                        {
                            string day00(1,newExpiryDate[8]);
                            string day01(1,newExpiryDate[9]);
                            string dayNow = day00 + day01;
                            double dayDouble1 = stringToDouble(dayNow);
                            dayDouble1 = dayDouble1 -1;
                            string dayString1 = doubleToString(dayDouble1);
                            new2ExpiryDate[8]= dayString1[0];
                            new2ExpiryDate[9]= dayString1[1];
                        }
                        else
                        {
                            newExpiryDate = new2ExpiryDate;
                        }
                    }
        }
        else
        {
            newExpiryDate = texp;
        }
    }

//FInding Indexes
for(double iter =0; iter< date.size(); iter++){
    if(date[iter] == t0){
        startDateIndex = iter;
    }
    else if(date[iter] == newExpiryDate){
        endDateIndex = iter;
    }
}

//Stripping the vectors into smaller required vectors
//Use of mutable property of vectors

businessDays = endDateIndex - startDateIndex;

//Separating/segregating
for(double it =0; it<date.size(); it++){
    if( it >= startDateIndex  && it <= endDateIndex){
        dateDisect.push_back(date[it]);
        rateDisect.push_back(rate[it]);
        stockPriceDisect.push_back(close_rate[it]);
    }
}

//COmpare with the Six Column CSV VaLues to get another OPTION PRicing vector
for(double ito = 0; ito < dateDisect.size(); ito++){
    for(double jk = 0; jk< date_purchase.size(); jk++){
        if(date_purchase[jk] == dateDisect[ito] && optionType[jk] == "C" && date_expiry[jk] == texp && strike_price[jk] == strike_given){
                returnPrices.push_back(ask_price[jk]);
        }
    }
}

//Implied VOlatality Calculation
PayoffVanilla payoff_ImpCall (OptionVanilla::Call, strike_given);

vector<double> ImpliedVolatility;
double dividendYield =0.0;
double tempImpliedVolatility;
double timedifference;

//    vector <double> simulatePrice;
//    vector <double> blackScholesPrices;
    vector <double> blackScholesImpliedDeltaPrices;
    double tempImpliedDelta;
    double bTemp;
    vector <double> hedgeErrorImpliedVol;
    double initialCash = 0;

    vector<double> wealthWithoutHedge;
    vector<double> wealthWithHedge;
    double wealthhedgewithoutTemp;

    ofstream Result ("result.csv"); //Opening file to print info to
    Result << "Results" << endl; //Headings for file
    Result << "Stock Price"<<","<< "Option Prices"<<","<<"Implied Volatality"<<","<<"Delta"<<","<<"Hedging Error"<<","<<"Wealth without Hedge"<<","<<"Wealth with Hedge"<<endl;


for(double rem=0; rem< dateDisect.size(); rem++){

      cout<<"***********************Start****************************"<<endl;
      //Time Difference
      timedifference = (businessDays/252)- (rem/252);
      cout<<"The Time Difference is: "<<timedifference<<endl;
      OptionVanilla option_Impcall(payoff_ImpCall, timedifference);
      Result<< stockPriceDisect[rem]<<",";
      Result<< returnPrices[rem]<<",";

     //Implied Volatality
      tempImpliedVolatility = Solve(option_Impcall, returnPrices[rem],0,1,0.01,1000.00,stockPriceDisect[rem],strike_given,businessDays,rateDisect[rem],dividendYield);
      cout<<"Implied Volatality : "<<tempImpliedVolatility<<endl;
      ImpliedVolatility.push_back(tempImpliedVolatility);
        //DElta VAlue
      Result<< ImpliedVolatility[rem]<<",";
      tempImpliedDelta = BlackScholesDelta(option_Impcall,stockPriceDisect[rem] , ImpliedVolatility[rem],rateDisect[rem],q);
      cout<<"Delta Value : "<<tempImpliedDelta<<endl;

      blackScholesImpliedDeltaPrices.push_back(tempImpliedDelta);
      Result<< blackScholesImpliedDeltaPrices[rem]<<",";

      if(rem==0){

        hedgeErrorTemp = 0;
        cout<<"The Hedge Error is : "<<hedgeErrorTemp<<endl;
        hedgeErrorImpliedVol.push_back(hedgeErrorTemp);
        Result<< hedgeErrorImpliedVol[rem]<<",";
        wealthWithoutHedge.push_back(initialCash + returnPrices[rem]);
        Result<< wealthWithoutHedge[rem]<<",";
        wealthWithHedge.push_back(hedgeErrorImpliedVol[0]);
        Result<< wealthWithHedge[rem]<<endl;

      }else{
        bTemp  = returnPrices[rem-1] - (blackScholesImpliedDeltaPrices[rem-1] * stockPriceDisect[rem-1]);
//        cout<<"B Value : "<< bTemp<<endl;
        hedgeErrorTemp = (blackScholesImpliedDeltaPrices[rem-1] * stockPriceDisect[rem] ) + (bTemp * exp((rateDisect[rem-1]*(1/252)))) - returnPrices[rem];
        cout<<"The Hedge Error is : "<<hedgeErrorTemp<<endl;
        hedgeErrorImpliedVol.push_back(hedgeErrorTemp);
        Result<< hedgeErrorImpliedVol[rem]<<",";

        wealthhedgewithoutTemp = (wealthWithoutHedge[rem-1] * (1+rateDisect[rem]))-(returnPrices[rem]-returnPrices[rem-1]);
        cout<<"Wealth without Hedge : "<<wealthhedgewithoutTemp<<endl;
        wealthWithoutHedge.push_back((wealthWithoutHedge[rem-1] * (1+rateDisect[rem]))-(returnPrices[rem]-returnPrices[rem-1]));
        Result<< wealthWithoutHedge[rem]<<",";
        wealthWithHedge.push_back(hedgeErrorImpliedVol[rem-1]);
        cout<<"Wealth With Hedge : "<<wealthWithHedge[rem]<<endl;
        Result<< wealthWithHedge[rem]<<endl;
        cout<<"***********************End****************************"<<endl;
        cout<<endl;
      }
}

//CAlculate CUmulative Hedging Error
double cumulativehedgeImpliedVol;

for(int k=0; k<hedgeErrorImpliedVol.size();k++){
    cumulativehedgeImpliedVol +=hedgeErrorImpliedVol[k];
}

    cout<<"The cumulative Hedging Error is : "<<cumulativehedgeImpliedVol<<endl;
    Result<<"Cumulative Hedging Error Real WOrld Data"<<","<<cumulativehedgeImpliedVol<<endl;
    Result.close();

    return 0;
}
