#include "Parser.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include <functional>

#include <iostream>
#include <string>

std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string& str)
{
	if (str[0] == SPACE_CHAR || str[0] == TAB_CHAR)
	{
		throw IndentationException();
	}

	if (getVariableValue(str) != nullptr) // getVariableValue is O(1) anyways, no need to assign to variable
	{
		return getVariableValue(str);
	}

	Type* type = getType(str);
	if (type == nullptr)
	{
		throw NameErrorException(str);
	}
	type->setIsTemp(true);

	return type;
}

Type* Parser::getType(std::string& str)
{
	static const std::unordered_map<TypeCode, std::function<Type* (const std::string&)>> codeToTypeObject =
	{
		{ TypeCode::Boolean, [](const std::string& s) { return new Boolean(s == TRUE_STRING ? true : false); }},
		{ TypeCode::Integer, [](const std::string& s) { return new Integer(std::stoi(s)); }},
		{ TypeCode::String,  [](const std::string& s) { return new String(s.substr(1, s.length() - 2)); }},
		{ TypeCode::List,    [](const std::string& s) { return parseList(s); }},
		{ TypeCode::Void,    [](const std::string& s) { return makeAssignment(s) ? new Void() : nullptr; }}
	};

	Helper::trim(str);
	return codeToTypeObject.at(Helper::getTypeCode(str))(str);
}

void Parser::freeMemory()
{
	for (const auto& it : _variables)
	{
		delete it.second;
	}
}

bool Parser::isLegalVarName(const std::string& str)
{
	if (Helper::isDigit(str[0]))
	{
		return false;
	}
	for (const auto& c : str)
	{
		if (!Helper::isLetter(c) && !Helper::isDigit(c)
			&& !Helper::isUnderscore(c))
		{
			return false;
		}
	}
	return true;
}

bool Parser::makeAssignment(const std::string& str)
{
	const auto equalsSignPos = str.find(EQUALS_SIGN);
	if (equalsSignPos == std::string::npos || equalsSignPos == 0)
	{
		return false;
	}
	std::string name = str.substr(0, equalsSignPos);
	std::string value = str.substr(equalsSignPos + 1);
	Helper::rtrim(name);
	Helper::ltrim(value);

	if (!isLegalVarName(name))
	{
		throw SyntaxException();
	}

	Type* valueType = getVariableValue(value); // search it as a name in the existing variables
	if (valueType == nullptr) // variable doesnt exist
	{
		valueType = getType(value);
		if (valueType == nullptr) // not a valid variable
		{
			if (isLegalVarName(value))
			{
				throw NameErrorException(value);
			}
			throw SyntaxException();
		}
	}
	else // variable exists, copy the value
	{
		auto typeToString = valueType->toString();
		if (!Helper::isList(typeToString)) // a list shouldnt be deep copied
		{
			valueType = getType(typeToString); // for deep copying
		}
	}

	if (getVariableValue(name) != nullptr) // delete before assigning
	{
		delete getVariableValue(name);
	}

	_variables[name] = valueType; // [] operator returns a reference, meaning it will create if name doesnt exist
	return true;
}

Type* Parser::getVariableValue(const std::string& str)
{
	try
	{
		return _variables.at(str);
	}
	catch (const std::out_of_range&)
	{
		return nullptr;
	}
}

List* Parser::parseList(const std::string& str)
{
	std::stringstream listStream(str.substr(1, str.length() - 2));
	std::string segment;
	std::vector<Type*> vec;
	while (std::getline(listStream, segment, ','))
	{
		Type* val = nullptr;
		if (Helper::getTypeCode(segment) == TypeCode::Void)
		{
			val = getVariableValue(segment);
			if (val == nullptr) // variable doesnt exist
			{
				throw NameErrorException(segment);
			}
			auto valString = val->toString();
			if (!Helper::isList(valString))
			{
				val = getType(valString); // deep copy the variable
			}
		}
		else
		{
			val = getType(segment);
		}
		vec.push_back(val);
	}
	return new List(std::move(vec));
}
