#include "DaiBoard.h"

DaiBoard::DaiBoard()
{
	Board();
	width = 15;
	height = 15;
	size = width * height;
	name = "Dai";

    //fill the board vector with spaces
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board.push_back(Space(j * 50 + 250, i * 50 + 50, j, i));
		}
	}

	frame.setSize(Vector2f(50 * width + 5, 50 * height + 5));
	frame.setPosition(Vector2f(222.5, 22));
	frame.setFillColor(Color::Transparent);
	frame.setOutlineThickness(-5);
	frame.setOutlineColor(Color::Black);
}

void DaiBoard::SetupPieces(TextureModule * t)
{
	Piece *newPiece;

	//Lance
	newPiece = new Piece(1, t);
	newPiece->SetLance();
	board[Index(0, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetLance();
	board[Index(14, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLance();
	board[Index(0, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLance();
	board[Index(14, 14)].Occupy(newPiece);

	//Knight
	newPiece = new Piece(1, t);
	newPiece->SetKnight();
	board[Index(1, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetKnight();
	board[Index(13, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKnight();
	board[Index(1, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKnight();
	board[Index(13, 14)].Occupy(newPiece);

	//stone general
	newPiece = new Piece(1, t);
	newPiece->SetStone();
	board[Index(2, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetStone();
	board[Index(12, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetStone();
	board[Index(2, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetStone();
	board[Index(12, 14)].Occupy(newPiece);

	//iron general
	newPiece = new Piece(1, t);
	newPiece->SetIron();
	board[Index(3, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetIron();
	board[Index(11, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetIron();
	board[Index(3, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetIron();
	board[Index(11, 14)].Occupy(newPiece);

	//copper general
	newPiece = new Piece(1, t);
	newPiece->SetCopper();
	board[Index(4, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetCopper();
	board[Index(10, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCopper();
	board[Index(4, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCopper();
	board[Index(10, 14)].Occupy(newPiece);

	//silver general
	newPiece = new Piece(1, t);
	newPiece->SetSilver();
	board[Index(5, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetSilver();
	board[Index(9, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSilver();
	board[Index(5, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSilver();
	board[Index(9, 14)].Occupy(newPiece);

	//gold general
	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(6, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(8, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(6, 14)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(8, 14)].Occupy(newPiece);

	//King
	newPiece = new Piece(1, t);
	newPiece->SetKing();
	board[Index(7, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKing();
	board[Index(7, 14)].Occupy(newPiece);

	//reverse chariot
	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(0, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(14, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(0, 13)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(14, 13)].Occupy(newPiece);

	//Cat Sword
	newPiece = new Piece(1, t);
	newPiece->SetCatSword();
	board[Index(2, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetCatSword();
	board[Index(12, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCatSword();
	board[Index(2, 13)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCatSword();
	board[Index(12, 13)].Occupy(newPiece);
	
	//Ferosious leopard
	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(4, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(10, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(4, 13)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(10, 13)].Occupy(newPiece);

	//blind tiger
	newPiece = new Piece(1, t);
	newPiece->SetBlindTiger();
	board[Index(6, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetBlindTiger();
	board[Index(8, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBlindTiger();
	board[Index(6, 13)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBlindTiger();
	board[Index(8, 13)].Occupy(newPiece);

	//Drunk Elephant
	newPiece = new Piece(1, t);
	newPiece->SetDrunkElephant();
	board[Index(7, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDrunkElephant();
	board[Index(7, 13)].Occupy(newPiece);

	//Violent Ox
	newPiece = new Piece(1, t);
	newPiece->SetViolentOx();
	board[Index(1, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetViolentOx();
	board[Index(13, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetViolentOx();
	board[Index(1, 12)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetViolentOx();
	board[Index(13, 12)].Occupy(newPiece);

	//Angry Boar
	newPiece = new Piece(1, t);
	newPiece->SetAngryBoar();
	board[Index(3, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetAngryBoar();
	board[Index(11, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetAngryBoar();
	board[Index(3, 12)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetAngryBoar();
	board[Index(11, 12)].Occupy(newPiece);

	//Evil Wolf
	newPiece = new Piece(1, t);
	newPiece->SetEvilWolf();
	board[Index(5, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetEvilWolf();
	board[Index(9, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetEvilWolf();
	board[Index(5, 12)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetEvilWolf();
	board[Index(9, 12)].Occupy(newPiece);

	//Pheonix
	newPiece = new Piece(1, t);
	newPiece->SetPheonix();
	board[Index(6, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetPheonix();
	board[Index(8, 12)].Occupy(newPiece);

	//Kirin
	newPiece = new Piece(1, t);
	newPiece->SetKirin();
	board[Index(8, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKirin();
	board[Index(6, 12)].Occupy(newPiece);

	//Lion
	newPiece = new Piece(1, t);
	newPiece->SetLion();
	board[Index(7, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLion();
	board[Index(7, 12)].Occupy(newPiece);

	//Rook
	newPiece = new Piece(1, t);
	newPiece->SetRook();
	board[Index(0, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetRook();
	board[Index(14, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetRook();
	board[Index(0, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetRook();
	board[Index(14, 11)].Occupy(newPiece);

	//Flying Dragon
	newPiece = new Piece(1, t);
	newPiece->SetFlyingDragon();
	board[Index(1, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetFlyingDragon();
	board[Index(13, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFlyingDragon();
	board[Index(1, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFlyingDragon();
	board[Index(13, 11)].Occupy(newPiece);

	//Side Mover
	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(2, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(12, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(2, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(12, 11)].Occupy(newPiece);

	//Vertical Mover
	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(3, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(11, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(3, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(11, 11)].Occupy(newPiece);

	//Bishop
	newPiece = new Piece(1, t);
	newPiece->SetBishop();
	board[Index(4, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetBishop();
	board[Index(10, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBishop();
	board[Index(4, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBishop();
	board[Index(10, 11)].Occupy(newPiece);

	//Dragon Horse
	newPiece = new Piece(1, t);
	newPiece->SetDragonHorse();
	board[Index(5, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetDragonHorse();
	board[Index(9, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonHorse();
	board[Index(5, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonHorse();
	board[Index(9, 11)].Occupy(newPiece);

	//Dragon King
	newPiece = new Piece(1, t);
	newPiece->SetDragonKing();
	board[Index(6, 3)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetDragonKing();
	board[Index(8, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonKing();
	board[Index(6, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonKing();
	board[Index(8, 11)].Occupy(newPiece);

	//Queen
	newPiece = new Piece(1, t);
	newPiece->SetQueen();
	board[Index(7, 3)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetQueen();
	board[Index(7, 11)].Occupy(newPiece);

	//Pawns
	for (int i = 0; i < width; i++)
	{
		newPiece = new Piece(1, t);
		newPiece->SetPawn();
		board[Index(i, 4)].Occupy(newPiece);

		newPiece = new Piece(0, t);
		newPiece->SetPawn();
		board[Index(i, 10)].Occupy(newPiece);
	}

	//Go Between
	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(4, 5)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(10, 5)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(4, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(10, 9)].Occupy(newPiece);
}
