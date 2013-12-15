#ifndef IOHELP
#define IOHELP

#include <vector>
#include <string>
#include <sstream>

std::string LoadFileAsString(const char * filename);

std::vector<std::string> & Split(const std::string & s, char delim, std::vector<std::string> & elems);

std::vector<std::string> Split(const std::string &s, char delim);

template<typename T>
std::string NtoS(T number);

template<typename T>
std::string NtoS(T number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

template<typename T>
T StoN(const std::string& numberAsString);

template<typename T>
T StoN(const std::string& numberAsString)
{
	T ret;

	std::stringstream stream(numberAsString);
	stream >> ret;
	if (stream.fail()) 
	{
		//log or something
	}
	return ret;
}

#endif