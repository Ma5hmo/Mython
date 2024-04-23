#include "Parser.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include <functional>

#include <iostream>
#include <string>

std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string str)
{
	if (str[0] == ' ' || str[0] == '\t')
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
	Type* ret = nullptr;
	Helper::trim(str);
	if (str.empty())
	{
		return nullptr;
	}

	if (Helper::isBoolean(str))
	{
		ret = new Boolean(str == "True" ? true : false);
	}
	else if (Helper::isInteger(str))
	{
		ret = new Integer(std::stoi(str));
	}
	else if (Helper::isString(str))
	{
		ret = new String(str.substr(1, str.length() - 2));
	}
	else if (str[0] == '[' && str[str.length() - 1] == ']')
	{
		ret = parseList(str);
	}
	else if (makeAssignment(str))
	{
		ret = new Void();
	}
	else
	{
		return nullptr;
	}
	return ret;
}

void Parser::freeMemory()
{
	for (const auto& it : _variables)
	{
		delete it.second;
	}
}

bool Parser::isLegalVarName(std::string str)
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

bool Parser::makeAssignment(std::string str)
{
	const auto equalsSignPos = str.find('=');
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
	else
	{
		auto typeToString = valueType->toString();
		if (typeToString[0] != '[') // a list shouldnt be deep copied
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

Type* Parser::getVariableValue(std::string str)
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
		const auto t = getType(segment);
		if (t == nullptr)
		{
			throw NameErrorException(segment);
		}
		vec.push_back(t);
	}
	return new List(vec);
}

const std::unordered_map<const char*, std::string> Parser::typeNameMap =
{ { typeid(Integer()).name(), "int"}, {typeid(Boolean()).name(), "bool"},
	{ typeid(String()).name(), "str"} };


std::string Parser::getVariableTypeName(Type* t)
{
	const auto type = typeid(t).name();
	if (typeNameMap.find(type) == typeNameMap.end()) // list isnt in the map since it has an annoying consturctor
	{
		return "<type 'list'>";
	}
	return "<type '" + typeNameMap.at(type) + "'>";
}
