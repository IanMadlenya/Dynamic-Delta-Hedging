
/* Black Scholes Formula Used
* C(S,t)=SN(d1)−Ke−rTN(d2)
*/
#include "OptionVanilla.h"
#include "Payoff.h"

OptionVanilla::OptionVanilla(Payoff& payoff, double expiry)
:expiry_(expiry)
{
     p_payoff_ = &payoff;
}

double OptionVanilla::GetExpiry() {
    return expiry_;
}

//double OptionVanilla::GetStrike() {
//    return strike_;
//}

bool OptionVanilla::OptionPayoff(double T) const{
   return (*p_payoff_)(T);
}

//double OptionVanilla::OptionStrikeOff(bool type) {
//    return payoff_(type);
//}
