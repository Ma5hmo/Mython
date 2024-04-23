#include "Boolean.h"

Boolean::Boolean(bool value)
	: _value(value)
{
}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	return _value ? "True" : "False";
}
