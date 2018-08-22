#pragma once

#include "Space.h"
//base class
class KSIterator
{
	virtual bool hasNext() = 0;
	virtual Space* next() = 0;
};
