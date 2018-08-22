#pragma once

#include<string>
#include<sstream>
#include<SFML\Graphics.hpp>
//#include<SFML/Graphics.hpp>
using namespace sf;
#include"TextureModule.h"

using namespace std;


class Piece
{
protected:
	Sprite pieceShape;
	Text pieceName;
	Text pieceName2;
	Sprite moveSymbols[9];
	TextureModule *textures;
	bool isPromoted;
	bool isPromotable;

	void TextureSetup();
	void Initialize(); 
public:
	string stepMoves;
	string rangeMoves;
	string lionMoves;
	string jumpMoves;
	string name;
	string abrName;
	string abrName2;
	bool isWhite;
	bool didPromoteLastTurn;
	bool IsPromoted() { return isPromoted; }


	Piece() { Initialize(); }
	Piece(bool white1black0, TextureModule *t);
	Piece(bool white1black0, TextureModule *t, string n);

	void Update();
	void Draw(RenderWindow* window);
	void SetPosition(Vector2f pos);

	void SetBishop();
	void SetBlindTiger();
	void SetCopper();
	void SetDrunkElephant();
	void SetDragonHorse();
	void SetDragonKing();
	void SetFerociousLeopard();
	void SetGold();
	void SetGoBetween();
	void SetKing();
	void SetKirin();
	void SetLance();
	void SetLion();
	void SetPawn();
	void SetPheonix();
	void SetQueen();
	void SetRook();
	void SetReverseChariot();
	void SetSilver();
	void SetSideMover();
	void SetVerticalMover();
	void SetFlyingStag();
	void SetPrince();
	void SetHornedFalcon();
	void SetSoaringEagle();
	void SetWhiteHorse();
	void SetWhale();
	void SetFreeBoar();
	void SetFlyingOx();
	void SetKnight();
	void SetStone();
	void SetIron();
	void SetCatSword();
	void SetViolentOx();
	void SetAngryBoar();
	void SetEvilWolf();
	void SetFlyingDragon();

	void Promote();
	void DeterminePieceType(string n, bool promoted);

};
