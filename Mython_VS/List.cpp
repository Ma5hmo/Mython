#include "List.h"

List::List(const std::vector<Type*>& vec)
	: _vec(vec)
{
}

List::~List()
{
	for (const auto& it : _vec)
	{
		delete it;
	}
}

bool List::isPrintable() const
{
	return true;
}

std::string List::toString() const
{
	std::string s = "[";
	for (const auto& it : _vec)
	{
		s += it->toString() + ", ";
	}
	if (s.length() > 1)
	{
		s.pop_back();
		s.pop_back();
	}
	s.push_back(']');
	return s;
}
