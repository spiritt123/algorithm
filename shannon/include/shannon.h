#pragma once

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

class Shannon
{
public:
    Shannon();
    ~Shannon() {} ;

    void scan(std::string path);
    int encrypt(std::string path);

private:
    void createCodes(std::vector<std::pair<char, double>> vector, std::string str);
    std::map<char, double> readFileAndCreateMapFrequencies(std::string path);

private:
    std::map<char, std::string> _codes;
};

