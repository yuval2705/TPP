#pragma once
/// <summary>
/// Prints to the screen if the given number is a prime number or not.
/// </summary>
/// <param name="number">The number to check if it prime or not.</param>
void testIfPrimeNumber(int number);

/// <summary>
/// Returns True if the given number is a prime number, false if not.
/// </summary>
/// <param name="number">The int number to check if it is a prime number.</param>
/// <returns>A bool value representing if the given number is a prime number or not.</returns>
bool isPrime(int number);

enum ReturnCodes
{
    SUCCESS = 0,
    INVLID_NUM_ARGS,
    ERROR
};