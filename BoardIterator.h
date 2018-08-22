#pragma once

#include "Space.h"
#include "KSIterator.h"

class BoardIterator: public KSIterator {

private:
	vector<Space>* board;
	int position = 0;

public:

	BoardIterator(vector<Space>* b)
	{
		board = b;
	}

    //returns next available space
	Space* next()
	{
		Space* space = &board->at(position);
		position++;
		return space;

	}

    //if has another space
	bool hasNext()
	{
		if (position >= board->size())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
