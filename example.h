#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "macros.h"

class BINDINGS_API Example
{
    public:
        Example(double a, double b);

        double add();

    private:
        double number1, number2;
};

#endif
