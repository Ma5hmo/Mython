#pragma once
#include "Sequence.h"
#include <vector>

class List : public Sequence
{
public:
	List(const std::vector<Type*>& vec);
	~List();

	bool isPrintable() const override;
	std::string toString() const override;

private:
	std::vector<Type*> _vec;
};
