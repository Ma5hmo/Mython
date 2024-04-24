#include "String.h"

String::String(std::string&& value)
	: _value(std::move(value))
{
}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	const char enclosingChar = _value.find('\'') != std::string::npos // is ' in the string?
		? '"' : '\''; // use " if ' is in the string, else use '
	return enclosingChar + _value + enclosingChar;
}
