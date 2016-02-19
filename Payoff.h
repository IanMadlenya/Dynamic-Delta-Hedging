
#ifndef __PayoffNew__
#define __Payoffnew__

#include "OptionVanilla.h"

class Payoff
{
public:

    Payoff(){};
    virtual bool operator()(double spot) const=0;
    virtual double GetStrike() const =0;
    virtual OptionVanilla::Type GetType() const =0;
    virtual ~Payoff(){}

};

// abstract class for Payoff with Call/Put Type
class PayoffWithType : public Payoff
{
public:
    // constructor
    PayoffWithType(OptionVanilla::Type type):type_(type){};

    // set and get type
    void SetType(OptionVanilla::Type type) { type_ = type; }
    OptionVanilla::Type GetType() const {return type_; }

protected:
    // member type
    OptionVanilla::Type type_;
};

// class for Vanilla Payoff with Call/Put Type and Fixed Strike
class PayoffVanilla : public PayoffWithType
{
public:
    // constructor
    PayoffVanilla(OptionVanilla::Type type,double strike);

    // set and get strike
    void SetStrike(double strike) { strike_ = strike; }
    double GetStrike() const {return strike_;}

    // payoff function
    virtual bool operator()(double spot) const;
//    virtual double operator()(bool type) const;

protected:

    // member strike
    double strike_;
};

#endif /* defined(__lab1_3__Payoff__) */
