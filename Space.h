#pragma once

#include<SFML\Graphics.hpp>
//#include<SFML/Graphics.hpp>
using namespace sf;

#include "Piece.h"

class Space
{
private:
	RectangleShape frame;
	void Initialize();
	Vector2f loc;
	Vector2f pos;
	string greenDirection;
	bool isHighlightedGreen;

public:
	Piece* occupant;
	bool isOccupied;
	bool isHighlightedBlack;
	bool isHighlightedWhite;
	bool isHighlightedRed;

	
	Space();
	Space(int x, int y, int gridx, int gridy);
	void Draw(RenderWindow * window);
	void Update();
	void Deoccupy() { isOccupied = false; occupant = NULL; }
	RectangleShape GetFrame() { return frame; }
	void Capture(Piece *newOccupant);
	
	void Occupy(Piece *newOccupant);
	
	Vector2f GetLocation() { return loc; }
	string GetLionDirection() { return greenDirection; }
	bool IsHighlightedGreen() { return isHighlightedGreen; }
	void HighlightGreen(bool highlighted, string direction);

};
