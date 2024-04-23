#pragma once
#include "InterpreterException.h"
#include <string>

class NameErrorException : public InterpreterException
{
public:
	NameErrorException(const std::string& name);
	virtual const char* what() const noexcept;
private:
	std::string _what;
};