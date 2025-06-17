#include <iostream>
#include <cmath>

enum ReturnCodes
{
    SUCCESS = 0,
    ERROR
};

/*
 * Asks the user for a double as an input.
 * Throws an indicating error if its invalid.
 *
 * @Return a double representing the user's input.
 */
double getInputFromUser()
{
    std::cout << "Enter a number to calculate its sqrt: ";
    double x = 0;

    std::cin >> x;

    if (!std::cin)
    {
        throw std::exception("Invalid value!");
    }
    return x;
}

/*
 * Prints the sqrt of the given value to the screen.
 *
 * @param value [IN]: The value the calculation.
 */
void printSQRT(double value)
{
    if (value < 0)
    {
        throw std::exception("Negetive value had been given!");
    }
    std::cout << "The square root of: " << value << " is " << std::sqrt(value) << std::endl;
}

int main()
{
    try
    {
        double x = getInputFromUser();
        printSQRT(x);
        return ReturnCodes::SUCCESS;
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return ReturnCodes::ERROR;
    }
}