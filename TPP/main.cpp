#include <iostream>
#include <string>
#include <cmath>

enum ReturnCodes
{
    SUCCESS = 0,
    INVLID_NUM_ARGS,
    ERROR
};

/// <summary>
/// Returns True if the given number is a prime number, false if not.
/// </summary>
/// <param name="number">The int number to check if it is a prime number.</param>
/// <returns></returns>
bool isPrime(int number)
{
    if (number <= 0)
    {
        throw std::exception("Invalid number " + number);
    }
    // Its enough to check all the number until the sqrt of the value and not value / 2
    for (int i = 2; i <= std::sqrt(number); i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

/// <summary>
/// Prints to the screen if the given number is a prime number or not.
/// </summary>
/// <param name="number">The number to check if it prime or not.</param>
void testNumber(char* number)
{
    int number_value = std::atoi(number);

    if (number_value == 0)
    {
        throw std::exception("Invalid value " + number_value);
    }


    std::string text = "";

    bool isValPrime = isPrime(number_value);
    if (isValPrime)
    {
        text += " is Prime!";
    }
    else
    {
        text += " is NOT Prime!";
    }
    std::cout << "The number " << number_value << text << std::endl;
}


int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            std::cout << "Usage: {path} {Natural_Nuber}" << std::endl;
            return ReturnCodes::INVLID_NUM_ARGS;
        }
        else
        {
            for (int i = 1; i < argc; i++)
            {
                testNumber(argv[i]);
            }
        }
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return ReturnCodes::ERROR;
    }
    return ReturnCodes::SUCCESS;
}