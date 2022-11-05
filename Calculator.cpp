#include "Calculator.h"
#include <cmath>

using namespace std;

double Calculator::addition(double x, double y){
    return x + y;
}

double Calculator::division(double x, double y){
    return x/y;
}

double Calculator::exponent(double x, double y){
    return pow(x,y);
}

double Calculator::subtraction(double x, double y){
    return x-y;
}

double Calculator::multiplication(double x, double y){
    return x*y;

}

double Calculator::root(double x){
    return sqrt(x);
}

double Calculator::square(double x){
    return pow(x,2);
}