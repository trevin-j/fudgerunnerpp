#include "utils.hpp"
#include <iostream>
#include <limits>

std::vector<char> strToVector(const std::string& s)
{
    std::vector<char> v(s.begin(), s.end());
    return v;
}

void clearInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}