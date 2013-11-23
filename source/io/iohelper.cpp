#include "iohelper.h"

#include <sstream>
#include <fstream>

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

std::string LoadFileAsString(const char * filename)
{
	std::string ret = "";
	std::ifstream is(filename);
    if (is == NULL) 
    {
    	return ret;
    }

    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    is.read (buffer,length);

    if (is)
    {
    	ret = buffer;
    }
    is.close();
    delete[] buffer;
  	return ret;
}
