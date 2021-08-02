#include <iostream>
#include "complex_number.h"

int main()
{
    ComplexNumber first(-5, -2.3), second(1, 2), buffer;
    
    first += second;
    buffer = second - first * ComplexNumber(2, 0);

    std::cout << "first = " << first << "\n";
    std::cout << "second = " << second << "\n";

    buffer /= ComplexNumber(3.2, 0);
    std::cout << buffer << "\n";

    return 0;
}
