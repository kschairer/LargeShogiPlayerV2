#pragma once
#include "Space.h"
#include "BoardIterator.h"

class Board
{
public:
	vector<Space> board;
	int width;
	int height;
	int size;
	string name;
	string directions[8];
	RectangleShape frame;

	Board();
	virtual void SetupPieces(TextureModule *t);
	void Reset(TextureModule *t);
	void Draw(RenderWindow* window);
	void Update();
	void RedDehighlight();
	void Dehighlight();
	void Highlight(int occupantIndex);
	void HighlightLion(int occupantIndex);
	void Occupy(int newIndex, int oldIndex);
	bool Capture(int newIndex, int oldIndex);

	//converts 2d coordinates to 1d index
	int Index(int i1, int i2) { return (i2 * width) + i1; }


	BoardIterator CreateIterator();
	
};