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

bool pathExists(const std::string &s)
{
    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
}