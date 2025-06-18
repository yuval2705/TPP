#include <iostream>
#include "StringBasic.h"


void main()
{
    StringBasic a = "hello, world";
    std::cout << a.getLength() << std::endl;
    std::cout << a.getStr() << std::endl;
}