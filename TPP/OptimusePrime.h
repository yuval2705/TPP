#pragma once
/// <summary>
/// Prints to the screen if the given number is a prime number or not.
/// </summary>
/// <param name="number">The number to check if it prime or not.</param>
void testIfPrimeNumber(int number);


enum ReturnCodes
{
    SUCCESS = 0,
    INVLID_NUM_ARGS,
    ERROR
};