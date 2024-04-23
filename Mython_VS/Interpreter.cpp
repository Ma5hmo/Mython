#include "Type.h"
#include "InterpreterException.h"
#include "Parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Itaychook"


int main(int argc, char** argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string inp_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, inp_string);

	while (inp_string != "quit()")
	{
		if (inp_string.length() != 0)
		{
			try
			{
				Type* inp_type = Parser::parseString(inp_string);
				if (inp_type->isPrintable())
				{
					std::cout << inp_type->toString() << std::endl;
				}
				if (inp_type->getIsTemp())
				{
					delete inp_type;
				}
			}
			catch (const InterpreterException& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, inp_string);
	}

	Parser::freeMemory();

	return 0;
}
