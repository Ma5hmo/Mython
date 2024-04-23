#pragma once
#include "Type.h"
#include "Sequence.h"
#include <string>

class String : public Sequence
{
public:
	String(const std::string& value);
	bool isPrintable() const override;
	std::string toString() const override;

private:
	std::string _value;
};