#include <iostream>

#include "example.h"

Example::Example(double a, double b)
{
    this->number1 = a;
    this->number2 = b;
}

double Example::add()
{
    return this->number1 + this->number2;
}