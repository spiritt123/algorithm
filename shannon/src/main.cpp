
#include <iostream>
#include "shannon.h"

int main(int argc, char* argv[])
{
    std::string path;

    if (argc < 2)
    {
        path = "text.txt";
    }
    else
    {
        path = argv[1];
    }

    Shannon shannon;
    shannon.scan(path);
    shannon.encrypt(path);
    return 0;
}
