#pragma once
#include <exception>
#include <string>

class CalculatorException : public std::exception
{
  public:
    CalculatorException();
    CalculatorException(std::string text);
    
};


class DividedByZero : public CalculatorException
{
  public:
    DividedByZero();
};


class UnsupportedOperation : public CalculatorException
{
  public:
    UnsupportedOperation();
    UnsupportedOperation(char operation);
};