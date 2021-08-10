
#include <iostream>
#include "least_squares_method.h"

int main()
{
    LeastSquaresMethod m(std::cin);
    std::vector<double> answer = m.getResult(1);
    for (auto el : answer)
    {
        std::cout << el << "\n";
    }
    return 0;
}
