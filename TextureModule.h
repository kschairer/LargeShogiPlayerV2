#pragma once

#include <string>
#include <SFML\Graphics.hpp>
//#include<SFML/Graphics.hpp>
#include"ResourcePath.hpp"

using namespace sf;
using namespace std;


/*///
Simply contains a reference to every space texture so loading
maps accesses the hardrive less, thus speeding up in game load times.
Having new objects prevents the mischance that the texture disappears
from memory which would cause game objects to be white squares
///*/
class TextureModule
{
private:

public:
	TextureModule();

	Texture baseShape;
	Texture blank;
	Texture range;
	Texture step;
	Texture lion;
	Texture jump;
	Texture directedLion;
	Texture knight;
	Texture bgPoplar;
	Texture bgCherry;
	Texture bgBeech;
	Texture baseShapeDarker;
	Texture baseShapePattern;
	Texture *bgSelection;
	Texture *baseShapeSelection;
	Font fontArialI;
	Font fontComic;
	Font fontComicB;
	Font fontArial;
	Font segoesc;
	Font fontBuxtonSketch;
	Font fontCardinal;
	Font *fontSelection;
};

