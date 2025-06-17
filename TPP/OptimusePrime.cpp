#include <iostream>
#include <string>
#include <cmath>
#include "OptimusePrime.h"


/// <summary>
/// Returns True if the given number is a prime number, false if not.
/// </summary>
/// <param name="number">The int number to check if it is a prime number.</param>
/// <returns>A bool value representing if the given number is a prime number or not.</returns>
bool isPrime(int number)
{
    if (number <= 0)
    {
        throw std::exception("Invalid value " + number);
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
void testIfPrimeNumber(int number)
{
    std::string text = "";

    bool isValPrime = isPrime(number);
    if (isValPrime)
    {
        text += " is Prime!";
    }
    else
    {
        text += " is NOT Prime!";
    }
    std::cout << "The number " << number << text << std::endl;
}
