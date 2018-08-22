//Keith Schairer
//k.a.schairer@gmail.com
//Large Shogi Player

#pragma once

#include <SFML\Graphics.hpp>
//#include<SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;
using namespace sf;
#include "KButton.h"
#include "ChuBoard.h"
#include "TextureModule.h"
#include "DaiBoard.h"
#include "StateMachine.h"

class Game
{
private:

	StateMachine * stateMachine;

	//window vars
	float windowSizeX;
	float windowSizeY;
	int framerate;
	RenderWindow *window;
	RectangleShape mouseCursorBackground;
	RectangleShape mouseCursorBoard;
	RectangleShape menuBoarder;

	View viewBackground;
	View viewBoard;

	//Gui- labels and KButtons
	
	
	Sprite background;
    Sprite backgroundImg;
	Sprite txtrSampleBoard;
	Sprite txtrSamplePiece;

	Text txtStart;
	Text txtGameSelectMenu;
	Text txtRulesSite;
	Text txtGameSelectDescription;
	Text txtTurn;
	Text txtPieceInfo;
	Text txtMenuTitle;
	Text txtMenuInstruction;
	Text txtSettingsTitle;
	Text txtBackgroundOption;
	Text txtPieceOption;
	Text txtFontOption;
	Text txtBlackWin;
	Text txtWhiteWin;
	Text txtNewGame;
	Text txtLoadGame;
	Text txtSaveGame;

	KButton* btnChuStart;
	KButton* btnChuShoStart;
	KButton* btnDaiStart;
	KButton* btnUndo;
	KButton* btnRedo;
	KButton* btnLoadAuto;
	KButton* btnMenu;
	KButton* btnMenuBack;
	KButton* btnBGOptionPoplar;
	KButton* btnBGOptionBeech;
	KButton* btnBGOptionCherry;
	KButton* btnShapeOptionPlain;
	KButton* btnShapeOptionPattern;
	KButton* btnShapeOptionDarker;
	KButton* btnFontOptionSegoe;
	KButton* btnFontOptionBuxton;
	KButton* btnFontOptionCardinal;
	KButton* btnSettings;
	KButton* btnSettingsBack;
	KButton* btnNewGame;
	KButton* btnSave1;
	KButton* btnSave2;
	KButton* btnSave3;
	KButton* btnLoad1;
	KButton* btnLoad2;
	KButton* btnLoad3;

	vector <KButton *> vectStartBtns;
	vector <KButton *> vectGameBtns;
	vector <KButton *> vectMenuBtns;
	vector <KButton *> vectSettingsBtns;


	vector <string> vectHistory;
	vector <string> vectRedoHistory;

	//Game vars
	Board* gameBoard;
	//ChuBoard chuBoard;
	

	TextureModule *textures;

	string gameState;
	string gameType;
	bool isBlacksTurn;
	int numOfRounds;
	string selectionState;
	int selectedPieceIndex;
	
	////functions
	//check events fired(keyboard, mouse)
	void CheckEvents();
	//draw the game to screen
	void Draw();
	//update every gui object based on possible changes made
	void UpdateObjects();
	//check if there was a button collision on click
	void CheckBtnCollisions(bool isBtnHeld);

	void StartBtnLogic();
	void GameBtnLogic();
	void MenuBtnLogic();
	void SettingsBtnLogic(KButton * clicked);
	void LoadLogic();

	void CheckSpaceCollisions();
	void HighlightSpaces(int occupantIndex, bool lion);
	void DehighlightSpaces();

	void Undo();
	void Redo();
	void SaveGame(int fileSlot);
	void LoadGame(int fileSlot);
	bool LogCapture(int newIndex, int oldIndex, int moveType);
	void LogMove(int newIndex, int oldIndex, int moveType);
	void LoadSettings();
	void SaveSettings();

	void split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	
public:
	Game();
	//the main game loop
	void Run();
};
