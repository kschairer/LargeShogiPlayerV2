#include "TextureModule.h"

TextureModule::TextureModule()
{

//pc
//fonts that must be passed to the Text objects
//pc
	fontArialI.loadFromFile("ariali.ttf");
	fontComic.loadFromFile("comic.ttf");
	fontArial.loadFromFile("arial.ttf");
	fontComicB.loadFromFile("comicbd.ttf");
	segoesc.loadFromFile("segoesc.ttf");
	fontBuxtonSketch.loadFromFile("BuxtonSketch.ttf");
	fontCardinal.loadFromFile("Cardinal.ttf");

	baseShape.loadFromFile("baseShape.png");
	range.loadFromFile("range.png");
	step.loadFromFile("step.png");
	jump.loadFromFile("jump.png");
	directedLion.loadFromFile("directedLion.png");
	lion.loadFromFile("lion.png");
	blank.loadFromFile("blank.png");
	knight.loadFromFile("knight.png");
	
	bgPoplar.loadFromFile("poplarWoodTexture.jpg");
	bgBeech.loadFromFile("beechWoodTexture.jpg");
	bgCherry.loadFromFile("cherryWoodTexture.jpg");
	baseShapeDarker.loadFromFile("baseShape2.png");
	baseShapePattern.loadFromFile("baseShape3.png");

	//mac
	/*fontArialI.loadFromFile(resourcePath() + "ariali.ttf");
	fontComic.loadFromFile(resourcePath() +"comic.ttf");
	fontArial.loadFromFile(resourcePath() +"arial.ttf");
	fontComicB.loadFromFile(resourcePath() +"comicbd.ttf");
	bgPoplar.loadFromFile(resourcePath()+"poplarWoodTexture.jpg");
	bgBeech.loadFromFile(resourcePath()+"beechWoodTexture.jpg");
	bgCherry.loadFromFile(resourcePath()+"cherryWoodTexture.jpg");
	baseShapeDarker.loadFromFile(resourcePath()+"baseShape2.png");
	baseShapePattern.loadFromFile(resourcePath()+"baseShape3.png");
	fontBuxtonSketch.loadFromFile(resourcePath()+"BuxtonSketch.ttf");
	fontCardinal.loadFromFile(resourcePath()+"Cardinal.ttf");
	knight.loadFromFile(resourcePath()+"knight.png");
	segoesc.loadFromFile(resourcePath()+"segoesc.ttf");


	baseShape.loadFromFile(resourcePath() + "baseShape.png");
	range.loadFromFile(resourcePath() +"range.png");
	step.loadFromFile(resourcePath() +"step.png");
	jump.loadFromFile(resourcePath() +"jump.png");
	directedLion.loadFromFile(resourcePath() +"directedLion.png");
	lion.loadFromFile(resourcePath() + "lion.png");
	blank.loadFromFile(resourcePath() + "blank.png");*/
	

	baseShapeSelection = &baseShape;
	bgSelection = &bgBeech;
	fontSelection = &segoesc;
}
