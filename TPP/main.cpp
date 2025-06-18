#include <iostream>
#include <string>
#include "Calculator.h"
#include "CalculatorException.h"


void main()
{

    std::cout << Calculator::calculate(1, '+', 2.14) << std::endl;
    std::cout << Calculator::calculate(1, '-', 2.14) << std::endl;
    std::cout << Calculator::calculate(1, '*', 2.14) << std::endl;

    try
    {
        std::cout << Calculator::calculate(1, '/', 0) << std::endl;
    }
    catch (const CalculatorException& exception)
    {
        std::cout << exception.what() << std::endl;
    }
    try
    {
        std::cout << Calculator::calculate(1, '~', 2.14) << std::endl;
    }
    catch (const UnsupportedOperation& exception)
    {
        std::cout << "Unsupported operation: " << exception.what() << std::endl;
    }
}