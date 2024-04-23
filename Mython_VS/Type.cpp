#include "Type.h"

Type::Type()
	: _isTemp(false)
{
}

bool Type::getIsTemp() const
{
	return _isTemp;
}

void Type::setIsTemp(bool isTemp)
{
	_isTemp = isTemp;
}
