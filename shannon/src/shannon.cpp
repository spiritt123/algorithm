
#include <algorithm>
#include "shannon.h"

Shannon::Shannon()
{

}

void Shannon::scan(std::string path)
{
    std::map<char, double> frequency = readFileAndCreateMapFrequencies(path);

    std::vector<std::pair<char, double>> probability;
    for (const auto &[key, value] : frequency)
    {
        std::pair<char, double> pair = {key, value};
        probability.push_back(pair);
    }

    std::sort(probability.begin(), 
              probability.end(), 
              [](std::pair<char, double> a, std::pair<char, double> b) { return a.second > b.second; });
    
    std::string code = "";
    createCodes(probability, code);
}

std::map<char, double> Shannon::readFileAndCreateMapFrequencies(std::string path)
{
    std::ifstream file;
    file.open(path);
    std::string line;
    
    if (!file.is_open())
        std::cerr << "file isn't open\n";

    size_t count = 0;
    std::map<char, double> frequency;

    while (std::getline(file, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            ++frequency[line[i]];
            ++count;
        }
    }
    
    file.close();

    for (const auto &[key, value] : frequency)
    {
        frequency[key] /= count;
    }
    
    return frequency;
}

void Shannon::createCodes(std::vector<std::pair<char, double>> vector, std::string str)
{
    if (vector.size() == 1)
    {
        str+="0";
        _codes[vector[0].first] = str;
        return;
    }
    if (vector.size() == 2)
    {
        _codes[vector[0].first] = str + "0";
        _codes[vector[1].first] = str + "1";
        return;
    }
    std::vector<std::pair<char, double>> top;
    std::vector<std::pair<char, double>> bottom;
    
    double top_probability = 0;
    double bottom_probability = 0;

    size_t begin = 0;
    size_t end = vector.size() - 1;
    while (top.size() + bottom.size() != vector.size())
    {
        if (top_probability < bottom_probability)
        {
            top.push_back(vector[begin]);
            top_probability += vector[begin].second;
            ++begin;
        }
        else
        {
            bottom.push_back(vector[end]);
            bottom_probability += vector[end].second;
            --end;
        }
    }

    createCodes(top, str + "0");
    createCodes(bottom, str + "1");

    return ;
}

int Shannon::encrypt(std::string path)
{
    if (_codes.size() == 0)
    {
        return -1;
    }

    std::ifstream file(path);
    std::string output_path = "codes_" + path;
    std::ofstream output(output_path, std::ios_base::out);;

    if (!file.is_open())
        std::cerr << "file isn't open\n";

    if (!output.is_open())
        std::cerr << "output file isn't open\n";

    std::string line;
    while (std::getline(file, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (_codes.count(line[i]) < 0)
            {
                file.close();
                output.close();
                return -2;
            }
            output << _codes[line[i]];
        }
    }
    file.close();
    output.close();
    return 0;
}

/*Shannon::(std::string _codes)
{
    
}*/
