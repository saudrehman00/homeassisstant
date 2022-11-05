#include <stdlib.h>

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator{
    public:
        Calculator();
        ~Calculator();
        double addition(double x, double y);
        double subtraction(double x, double y); 
        double multiplication(double x, double y);
        double division(double x, double y);
        double exponent(double x, double y);
        double square(double x);
        double root(double x);
};

#endif