
#ifndef __StdNormalCDF__
#define __StdNormalCDF__

class StdNormalCDF {

public:
    StdNormalCDF(double x);
    virtual double operator()(double x) const;
    virtual ~StdNormalCDF(){};

private:
    static const double A1;
    static const double A2;
    static const double A3;
    static const double A4;
    static const double A5;
    static const double B;
    static const double NORMALIZER;
};

#endif /* defined(__hw3__StdNormalCDF__) */
