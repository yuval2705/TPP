#include <iostream>

enum ReturnCodes {
    SUCCESS = 0,
    INVALID_VALUE = 1
};

int main() {
    std::cout << "Enter a number to calculate its sqrt: ";
    double x = 0;

    std::cin >> x;

    if (!std::cin) {
        std::cout << "Unsupported value!" << std::endl;
        return ReturnCodes::INVALID_VALUE;
    }

    if (x < 0) {
        std::cout << "Value must be a Non-Negetive!" << std::endl;
        return ReturnCodes::INVALID_VALUE; 
    }

    std::cout << "The square root of: " << x << " is " << std::sqrt(x) << std::endl;
    return ReturnCodes::SUCCESS;
}
