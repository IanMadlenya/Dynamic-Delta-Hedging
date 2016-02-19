
#ifndef __BlackScholes__
#define __BlackScholes__

class OptionVanilla;

double BlackScholes(OptionVanilla &option,
                         double spot,
                         double vol,
                         double r,
                         double q);

//double BlackScholes(OptionVanilla &option,
//                         double spot,
//                         double K,
//                         double vol,
//                         double r,
//                         double q);

double BlackScholesDelta(OptionVanilla &option,
                         double spot,
                         double vol,
                         double r,
                         double q);

double Solve(OptionVanilla &option, double targetprice, double a, double b,
             double tolerance,unsigned long max_evaluation_number,
             double S0,double K,double T,double r, double q);

#endif /* defined(__lab1_1__MonteCarlo__) */
