#pragma once
#include <string>

class Type
{
public:
	Type();

	virtual bool isPrintable() const = 0;
	virtual std::string toString() const = 0;

	bool getIsTemp() const;
	void setIsTemp(bool isTemp);

private:
	bool _isTemp;
};
