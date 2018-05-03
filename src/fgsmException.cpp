#include "fgsmException.h"

FgsmException::FgsmException(std::string message) throw()
: whatStr(message)
{
}

FgsmException::~FgsmException() throw()
{
}

const char* FgsmException::what() const throw()
{
	return (whatStr.c_str());
}

