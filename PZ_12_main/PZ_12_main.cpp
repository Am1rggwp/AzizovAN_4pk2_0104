

#include <iostream>
#include "MathLibary.h"

int main()
{
    double a, b;
    std::cout << "Enter first number (a): " << std::endl;
    std::cin >> a;

    std::cout << "Enter second number (b): " << std::endl;
    std::cin >> b;

    std::cout << "\nAll arithmetic operation (a and b): " << std::endl;
    std::cout << a << " + " << b << " = " << MathLib::Arithmetic::Add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << MathLib::Arithmetic::Substruct(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << MathLib::Arithmetic::Multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << MathLib::Arithmetic::Devide(a, b) << std::endl;
}

