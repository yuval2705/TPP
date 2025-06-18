#include <iostream>
#include "StringBasic.h"


void main()
{
    StringBasic a = "hello, world";
    std::cout << a.getLength() << std::endl;
    std::cout << a.getStr() << std::endl;

    StringBasic b;
    std::cout << b.getLength() << std::endl;
    std::cout << b.getStr() << std::endl;

    StringBasic c = 'c';
    std::cout << c.getLength() << std::endl;
    std::cout << c.getStr() << std::endl;

    StringBasic e = a;
    std::cout << e.getLength() << std::endl;
    std::cout << e.getStr() << std::endl;


    std::cout << a.compare(e) << std::endl;
    std::cout << a.compare("hello, world") << std::endl;
    std::cout << a.compare("hello, ") << std::endl;

    std::cout << a.isEmpty() << std::endl;
    std::cout << b.isEmpty() << std::endl;

    a.append("i am appended");
    std::cout << a.getStr() << std::endl;

    std::cout << a[7] << std::endl;
}