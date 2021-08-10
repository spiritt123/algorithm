
#include "matrix.h"
#include <iostream>
#include "slau.h"


int main()
{
    Slau slau(std::cin);
    std::vector<double> offset = {1, 2, 3};
    slau.addOffset(offset);
    //std::vector<double> answer = slau.findByKramer();
    std::vector<double> answer = slau.findByMatrix();
    //std::vector<double> answer = slau.findByGausse();
    for (auto el : answer)
    {
        std::cout << el << "\n";
    }
    return 0;
}
