#include "Integer.h"

Integer::Integer(int value)
	: _value(value)
{
}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return std::to_string(_value);
}
