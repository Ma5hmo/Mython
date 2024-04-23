#include "NameErrorException.h"

NameErrorException::NameErrorException(const std::string& name)
    : _what("NameError: name '" + name + "' is not defined") 
    // have to build the _what string in the constructor, because if we
    // built it in the what() function, c_str() will return a dangling pointer
    // since the string we have built is going to be deleted after the function ends.
{
}

const char* NameErrorException::what() const noexcept
{;
    return _what.c_str();
}
