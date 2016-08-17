

#include "StdNormalCDF.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <cmath>


const double StdNormalCDF::A1 = 0.319381530;
const double StdNormalCDF::A2 = -0.35653782;
const double StdNormalCDF::A3 = 1.781477937;
const double StdNormalCDF::A4 = -1.821255978;
const double StdNormalCDF::A5 = 1.330274429;
const double StdNormalCDF::B = 0.2316419;
const double StdNormalCDF::NORMALIZER = 0.39894228;     // really 1/sqrt(2*pi);

StdNormalCDF::StdNormalCDF(double x){}

double StdNormalCDF::operator()(double x) const {
    double absoluteValue;
    double intermediateValue;
    double stdnormalCDFValue;

    absoluteValue = fabs(x);
    intermediateValue = 1.0 / ( 1.0 + (StdNormalCDF::B) * absoluteValue);
    stdnormalCDFValue = 1.0 - (StdNormalCDF::NORMALIZER * exp(-absoluteValue *absoluteValue / 2) * (StdNormalCDF::A1 * intermediateValue + StdNormalCDF::A2 * intermediateValue *intermediateValue + StdNormalCDF::A3 * pow(intermediateValue,3) + StdNormalCDF::A4 * pow(intermediateValue,4) + StdNormalCDF::A5 * pow(intermediateValue,5)));

    if(x < 0){
        stdnormalCDFValue = 1.0 - stdnormalCDFValue;
    }
    return stdnormalCDFValue;

}


