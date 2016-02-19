
#include "Random.h"
#include <cstdlib>
#include <cmath>


// Draw a sample from a standard normal distribution using Box-Muller Method
double DrawNormal(){

    double x;
    double y;
    double size_squared;

    do
    {
        x = 2.0*rand()/(double)(RAND_MAX)-1;
        y = 2.0*rand()/(double)(RAND_MAX)-1;
        size_squared = x*x + y*y;
    }
    while (size_squared >= 1.0);

    return x*sqrt(-2*log(size_squared)/size_squared);

}
