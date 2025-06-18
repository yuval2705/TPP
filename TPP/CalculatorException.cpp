#include <exception>
#include <string>
#include "CalculatorException.h"

CalculatorException::CalculatorException(char* text) : std::exception(text)
{
}


DividedByZero::DividedByZero() : CalculatorException((char*)"Divided by zero!")
{
}


UnsupportedOperation::UnsupportedOperation(char operation) : CalculatorException((char*)("Unsupport operation " + operation))
{
}