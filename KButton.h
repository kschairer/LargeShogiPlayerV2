#pragma once

#include <SFML\Graphics.hpp>
//#include<SFML/Graphics.hpp>

#include "TextureModule.h"
#include <string>
using namespace sf;
using namespace std;


////This class provides the basic functionality for a button. I created this class to avoid
////trying to implement OS based GUI (windows forms or Cocoa)
class KButton
{
private:
	Font font;
	Text txtTitle;
	bool isSelected;
	Vector2f pos;
	Vector2f size;
	Color boundsColor;

public:
	RectangleShape btnBounds;

	KButton();
	KButton(TextureModule *t, string title, Vector2f pos, Vector2f size, Color color);
	void Update();
	void Select() { isSelected = true; }
	void Deselect() { isSelected = false; }
	bool IsSelected() { return isSelected; }
	void SetCharSize(int size) { txtTitle.setCharacterSize(size); }

	void Draw(RenderWindow *target);

};

