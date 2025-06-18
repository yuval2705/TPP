#pragma once
class Calculator
{
  public:
    Calculator();
    double add(double val1, double val2);
    double sub(double val1, double val2);
    double multiply(double val1, double val2);
    double divide(double val1, double val2);
    double calculate(double val1, char op, double val2);
};