#ifndef LINEAREXCEPTION_H
#define LINEAREXCEPTION_H

#include <exception>
#include "tools.h"

class FgsmException : public std::exception
{
	private:
		std::string whatStr;
	
	public:
		FgsmException(std::string message) throw();
		virtual ~FgsmException() throw();
	    virtual const char* what() const throw();
};


#endif

