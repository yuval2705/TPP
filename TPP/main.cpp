#include <iostream>
#include <string>
#include "ComplexNumber.h"


void main()
{
    ComplexNumber z1 = ComplexNumber(3, 4);
    ComplexNumber z2 = ComplexNumber(-1, 3);

    std::cout << "z1 = " << z1.to_string() << std::endl;
    std::cout << "z2 = " << z2.to_string() << std::endl;


    std::cout << "z1 + z2 = " << (z1 + z2).to_string() << std::endl;
    std::cout << "z1 - z2 = " << (z1 - z2).to_string() << std::endl;
    std::cout << "z1 * z2 = " << (z1 * z2).to_string() << std::endl;
}