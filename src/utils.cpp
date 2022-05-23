#include "utils.hpp"
#include <iostream>
#include <limits>

std::vector<char> strToVector(const std::string& s)
{
    std::vector<char> v(s.begin(), s.end());
    return v;
}

void clear()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system ("clear");
#endif
}