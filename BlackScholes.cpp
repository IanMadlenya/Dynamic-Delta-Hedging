
#include "BlackScholes.h"
#include "StdNormalCDF.h"
#include "OptionVanilla.h"
#include "Payoff.h"
#include <cmath>
#include <iostream>
using namespace std;

double BlackScholes(OptionVanilla &option,
                  double spot,
                  double vol,
                  double r,
                  double q)
{
      double blackscholesMean;
      //Get Expiry Time
      double T = option.GetExpiry();
//      double K = opti



      OptionVanilla::Type type = option.GetPayoffPointer()->GetType();

//      double K = option.O
//      cout<<"bool"<<type;

      double K=option.GetPayoffPointer()->GetStrike();

//      double K = option.OptionStrikeOff(type);

      double d1,d2,d3,d4;

      d1 = (log(spot/K) + (r + (pow(-1,0))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));
      d2 = (log(spot/K) + (r + (pow(-1,1))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));

      d3 = -(log(spot/K) + (r + (pow(-1,0))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));
      d4 = -(log(spot/K) + (r + (pow(-1,1))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));

      StdNormalCDF s3(d1);
      double cdf1 = s3(d1);

      StdNormalCDF s4(d2);
      double cdf2 = s4(d2);

      StdNormalCDF s5(d3);
      double cdf3 = s5(d3);

      StdNormalCDF s6(d4);
      double cdf4 = s6(d4);

      double putCallParity;

      // If It's a Call Option
      if( type == 1){
        blackscholesMean = (spot * cdf1 - K*exp(-r*T)*cdf2);
      }else if(type==-1){
        blackscholesMean = (-spot * cdf3 + K*exp(-r*T)*cdf4);
      }

      return blackscholesMean;


//    double variance = vol*vol*expiry;
//    double root_variance = sqrt(variance);
//    double ito_correction = -0.5*variance;
//
//    double moved_spot = spot*exp(r*expiry +ito_correction);
//    double this_spot;
//    double running_sum=0;
//
//    for (unsigned long i=0; i < n_path; i++)
//    {
//        this_spot = moved_spot*exp( root_variance*DrawNormal());
//        running_sum += option.PayoffOnExpiry(this_spot);
//    }
//
//    double mean = running_sum / n_path;
//    mean *= exp(-r*expiry);
//    return mean;

}



double BlackScholesDelta(OptionVanilla &option,
                  double spot,
                  double vol,
                  double r,
                  double q)
{
      double blackscholesMean;

      double T = option.GetExpiry();

      OptionVanilla::Type type = option.GetPayoffPointer()->GetType();

      double K=option.GetPayoffPointer()->GetStrike();
      double d1,d2,d3,d4;

      d1 = (log(spot/K) + (r + (pow(-1,0))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));
      d2 = (log(spot/K) + (r + (pow(-1,1))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));

      d3 = -(log(spot/K) + (r + (pow(-1,0))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));
      d4 = -(log(spot/K) + (r + (pow(-1,1))*0.5*vol*vol)*T)/(vol*(pow(T,0.5)));

      StdNormalCDF s3(d1);
      double cdf1 = s3(d1);

      StdNormalCDF s4(d2);
      double cdf2 = s4(d2);

      StdNormalCDF s5(d3);
      double cdf3 = s5(d3);

      StdNormalCDF s6(d4);
      double cdf4 = s6(d4);

      double putCallParity;

      // If It's a Call Option
      if( type == 1){
        blackscholesMean = (spot * cdf1 - K*exp(-r*T)*cdf2);
      }else if(type==-1){
        blackscholesMean = (-spot * cdf3 + K*exp(-r*T)*cdf4);
      }

      return cdf1;
}


double Solve(OptionVanilla &option, double targetprice, double a, double b,
             double tolerance,unsigned long max_evaluation_number,
             double S0,double K,double T,double r,double q)
{
        // check input validity
        bool root_found_;
        if (a>b || tolerance<=0) {
            cerr<<"Bisection Error: Invalid Input Parameters!"<<endl;
            return -1;
        }


//        cout<<" Target Price : "<<targetprice<<endl;
        // check lower bound
        double fabls = BlackScholes(option,S0,a,r,q);
//        cout<<"FBBLS: "<<fabls<<endl;
        double fa = fabls-targetprice;
//        cout<<"FA Is : "<<fa<<endl;
        if (fabs(fa)<tolerance) {
            root_found_ = true;
            return a;
        }

        // check upper bound
        double fbbls = BlackScholes(option,S0,b,r,q);
//        cout<<"FBBUS : "<< fbbls<<endl;

        double fb = fbbls - targetprice;
//        cout<<"FB: "<<fb<<endl;
        if (fabs(fb)<tolerance) {
            root_found_ = true;
            return b;
        }

        // check root exist or not
        if (fa * fb>0.0) {
////            cerr<<"root not bracketed! "<<endl;
//            cerr<<"a="<<a<<",b="<<b<<endl;
//            cerr<<"fa="<<fa<<",fb="<<fb<<endl;
            return -1;
        }else{
//            cout<<"Success for FA and FB"<<endl;
        }

        // start bisection
        double mid = 0.5 * (a+b);
        double fmidbls = BlackScholes(option,S0,mid,r,q);
        double fmid = fmidbls-targetprice;
        double n = 0;
        while (fabs(fmid)>=tolerance  && n<max_evaluation_number) {
            if (fmid * fb>0) {
                b = mid;
                fb = fmid;
            }
            else {
                a = mid;
                fa = mid;
            }
            mid = 0.5 * (a+b);
            fmidbls = BlackScholes(option,S0,mid,r,q);
            fmid = fmidbls-targetprice;
            n++;
        }

        if (n==max_evaluation_number) {
            cout<<"Warning: max evaluation number reached!"<<endl;
        }
        root_found_ = true;
//        cout<<"Mid is : "<<mid<<endl;
        return mid;
}
