
#include "Payoff.h"
#include <algorithm>
#include <iostream>
using std::max;
using std::endl;
using std::cerr;
using std::cout;

// constructor
PayoffVanilla::PayoffVanilla(OptionVanilla::Type type,double strike)
: PayoffWithType(type), strike_(strike)
{
}

// payoff function
bool PayoffVanilla::operator()(double spot) const
{

    if (type_==OptionVanilla::Call) {
        return true;
    }
    else if(type_==OptionVanilla::Put) {
        return false;
    }

}

//double PayoffVanilla::operator(bool type)const
//{
//    return strike_;
//}
