#pragma once
class Calculator
{
  private:
    Calculator() = default;
    
    /**
     * Takes to doubles and return their sum.
     *
     * @param val1 [IN] The first number to add.
     * @param val1 [IN] The second number to add.
     * @return The sum of the two numbers given.
     */
    static double add(double val1, double val2);

    /**
     * Subtracts the second double from the first one.
     *
     * @param val1 [IN] The number to subtract from.
     * @param val1 [IN] The number to subtract.
     * @return The value of the first value subtracted by the second.
     */
    static double subtract(double val1, double val2);

    /**
     * Multiply the two given values.
     *
     * @param val1 [IN] The first number to multiply.
     * @param val1 [IN] The second number to multiply with.
     * @return The multiplication value of the two given numbers.
     */
    static double multiply(double val1, double val2);

    /**
     * Divides the first value by the second value.
     *
     * @param val1 [IN] The number to divide.
     * @param val1 [IN] The number to divde by.
     * @return The result of the first number divided by the second.
     */
    static double divide(double val1, double val2);
    
  public:
    /**
     * Calculates the math operation between the 2 given numbers.
     *
     * @param val1 [IN] The first number for the calculation.
     * @param operation [IN] The math operation to perform between the 2 numbers.
     * @param val1 [IN] The second number for the calculation.
     * @return The result of the given operation between the 2 numbers.
     */
    static double calculate(double val1, char operation, double val2);
};