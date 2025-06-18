#include <exception>
#include <string>
#include "CalculatorException.h"

CalculatorException::CalculatorException(std::string text) : std::exception(text.c_str())
{
}


DividedByZero::DividedByZero() : CalculatorException("Divided by zero!")
{
}


UnsupportedOperation::UnsupportedOperation(char operation) : CalculatorException(std::string(1, operation))
{
}