#include "Calculator.h"
#include "CalculatorException.h"

double Calculator::add(double val1, double val2)
{
    return val1 + val2;
}

double Calculator::sub(double val1, double val2)
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
            return this->add(val1, val2);
            break;
        case '-':
            return this->sub(val1, val2);
            break;
        case '*':
            return this->multiply(val1, val2);
            break;
        case '/':
            return this->divide(val1, val2);
            break;
        default:
            throw UnsupportedOperation(operation);
    }
}
