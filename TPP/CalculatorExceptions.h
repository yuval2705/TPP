#pragma once
#include <exception>
#include <string>

class CalculatorException : public std::exception
{
  public:
    CalculatorException();
    CalculatorException(std::string text);
};
