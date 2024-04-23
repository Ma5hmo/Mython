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
    static Type* parseString(std::string str);
    static Type* getType(std::string& str);
    static std::string getVariableTypeName(Type* t);
    static void freeMemory();

private:
    static bool isLegalVarName(std::string str);
    static bool makeAssignment(std::string str);
    static Type* getVariableValue(std::string str);
    static List* parseList(const std::string& str);


    static std::unordered_map<std::string, Type*> _variables;

    static const std::unordered_map<const char*, std::string> typeNameMap;
};
