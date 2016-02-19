
#ifndef __lab2_1__Option__
#define __lab2_1__Option__

//#include "Payoff.h"

class Payoff;


class OptionVanilla {

public:
    // define a type
    enum Type {Put = -1, Call = 1, None = 0};

    // constructor
    OptionVanilla(Payoff& payoff, double expiry);

    // return payoff at the expiration date
    bool OptionPayoff (double spot) const;
//    double OptionStrikeOff(bool type);


    // set and get expiry
    void SetExpiry(double expiry) {expiry_=expiry;}
    double GetExpiry() const {return expiry_;}

    double GetExpiry();

    Payoff* GetPayoffPointer() const {return p_payoff_;}

//    void SetStrike(double strike) {strike_=strike;}
//    double GetStrike() const {return strike_;}
    //set and get Strike

    ~OptionVanilla(){};

protected:

    // pointer to Payoff
    Payoff* p_payoff_;
    // we cannot "Payoff payoff_;", because Payoff is an abstract class, and we cannot creat instances of abstract class
    // we can "PayoffVanilla payoff_", but the possibility of our class to contain exotic payoff is lost

    // time to expiration
    double expiry_;
//    double strike_;
};



#endif /* defined(__lab2_1__Option__) */
