#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sys/stat.h>

// Return a char vector from a string.
std::vector<char> strToVector(const std::string& s);

// Clear terminal
void clear();

// Check if a path exists.
bool pathExists(const std::string &s);

#endif