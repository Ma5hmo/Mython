#pragma once
#include "InterpreterException.h"
#include "Type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

#include "String.h"
#include "Integer.h"
#include "Void.h"
#include "Boolean.h"
#include "List.h"


class Parser
{
public:
    static Type* parseString(std::string& str);
    static Type* getType(std::string& str);
    static void freeMemory();

private:
    static bool isLegalVarName(const std::string& str);
    static bool makeAssignment(const std::string& str);
    static Type* getVariableValue(const std::string& str);
    static List* parseList(const std::string& str);


    static std::unordered_map<std::string, Type*> _variables;

    static constexpr auto TRUE_STRING = "True";
    static constexpr auto OPENING_BRACKET = '[';
    static constexpr auto CLOSING_BRACKET = ']';
    static constexpr auto EQUALS_SIGN = '=';
    static constexpr auto SPACE_CHAR = ' ';
    static constexpr auto TAB_CHAR = '\t';

};
