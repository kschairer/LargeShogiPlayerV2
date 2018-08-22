#pragma once
#include"Space.h"
#include"Board.h"

class ChuBoard: public Board
{
public:
	
	ChuBoard();
	void SetupPieces(TextureModule *t);
	
};