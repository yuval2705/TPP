#include "Calculator.h"
#include "CalculatorException.h"


double Calculator::add(double val1, double val2)
{
    return val1 + val2;
}


double Calculator::subtract(double val1, double val2)
{
    return val1 - val2;
}

double Calculator::multiply(double val1, double val2)
{
    return val1 * val2;
}

double Calculator::divide(double val1, double val2)
{
    if (val2 == 0)
    {
        throw DividedByZero();
    }

    return val1 / val2;
}

double Calculator::calculate(double val1, char operation, double val2)
{
    switch (operation)
    {
        case '+':
            return Calculator::add(val1, val2);
            break;
        case '-':
            return Calculator::subtract(val1, val2);
            break;
        case '*':
            return Calculator::multiply(val1, val2);
            break;
        case '/':
            return Calculator::divide(val1, val2);
            break;
        default:
            throw UnsupportedOperation(operation);
    }
}
