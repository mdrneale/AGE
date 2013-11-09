#include "iohelper.h"

#include <sstream>

std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    return Split(s, delim, elems);
}

