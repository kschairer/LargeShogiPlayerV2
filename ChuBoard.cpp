#include "ChuBoard.h"

ChuBoard::ChuBoard()
{
	Board();
	width = 12;
	height = 12;
	size = 144;
	name = "Chu";

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board.push_back(Space(j * 50 + 225, i * 50 + 197, j, i));
		}
	}

	frame.setSize(Vector2f(50*width+5, 50*height+5));
	frame.setPosition(Vector2f(197.5, 170));
	frame.setFillColor(Color::Transparent);
	frame.setOutlineThickness(-5);
	frame.setOutlineColor(Color::Black);
}

void ChuBoard::SetupPieces(TextureModule *t)
{
	Piece* newPiece;

	//Bishop
	newPiece = new Piece(true, t);
	newPiece->SetBishop();
	board[Index(2, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetBishop();
	board[Index(9, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBishop();
	board[Index(2, 10)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBishop();
	board[Index(9, 10)].Occupy(newPiece);

	//Blind Tiger
	newPiece = new Piece(1, t);
	newPiece->SetBlindTiger();
	board[Index(4, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetBlindTiger();
	board[Index(7, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBlindTiger();
	board[Index(4, 10)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBlindTiger();
	board[Index(7, 10)].Occupy(newPiece);



	//Copper General 
	newPiece = new Piece(1, t);
	newPiece->SetCopper();
	board[Index(2, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetCopper();
	board[Index(9, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCopper();
	board[Index(2, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetCopper();
	board[Index(9, 11)].Occupy(newPiece);

	//Drunk Elephant
	newPiece = new Piece(1, t);
	newPiece->SetDrunkElephant();
	board[Index(5, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDrunkElephant();
	board[Index(6, 11)].Occupy(newPiece);

	//Dragon Horse 
	newPiece = new Piece(1, t);
	newPiece->SetDragonHorse();
	board[Index(3, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetDragonHorse();
	board[Index(8, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonHorse();
	board[Index(3, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonHorse();
	board[Index(8, 9)].Occupy(newPiece);

	//Dragon King 
	newPiece = new Piece(1, t);
	newPiece->SetDragonKing();
	board[Index(4, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetDragonKing();
	board[Index(7, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonKing();
	board[Index(4, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonKing();
	board[Index(7, 9)].Occupy(newPiece);

	//Ferocious Leopard
	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(1, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(10, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(1, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(10, 11)].Occupy(newPiece);

	//Gold General
	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(4, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(7, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(4, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(7, 11)].Occupy(newPiece);

	//Go between
	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(3, 4)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(8, 4)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(3, 7)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(8, 7)].Occupy(newPiece);


	//King
	newPiece = new Piece(1, t);
	newPiece->SetKing();
	board[Index(6, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKing();
	board[Index(5, 11)].Occupy(newPiece);

	//Kirin
	newPiece = new Piece(1, t);
	newPiece->SetKirin();
	board[Index(6, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKirin();
	board[Index(5, 10)].Occupy(newPiece);

	//Lance
	newPiece = new Piece(1, t);
	newPiece->SetLance();
	board[Index(0, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetLance();
	board[Index(11, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLance();
	board[Index(0, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLance();
	board[Index(11, 11)].Occupy(newPiece);

	//Lion
	newPiece = new Piece(1, t);
	newPiece->SetLion();
	board[Index(6, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLion();
	board[Index(5, 9)].Occupy(newPiece);

	//Pheonix
	newPiece = new Piece(1, t);
	newPiece->SetPheonix();
	board[Index(5, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetPheonix();
	board[Index(6, 10)].Occupy(newPiece);

	//Queen
	newPiece = new Piece(1, t);
	newPiece->SetQueen();
	board[Index(5, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetQueen();
	board[Index(6, 9)].Occupy(newPiece);

	//Rook
	newPiece = new Piece(1, t);
	newPiece->SetRook();
	board[Index(2, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetRook();
	board[Index(9, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetRook();
	board[Index(2, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetRook();
	board[Index(9, 9)].Occupy(newPiece);

	//Reverse Chariot
	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(0, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(11, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(0, 10)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(11, 10)].Occupy(newPiece);

	//Silver
	newPiece = new Piece(1, t);
	newPiece->SetSilver();
	board[Index(3, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetSilver();
	board[Index(8, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSilver();
	board[Index(3, 11)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSilver();
	board[Index(8, 11)].Occupy(newPiece);

	//Side Mover
	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(1, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(10, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(1, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(10, 9)].Occupy(newPiece);

	//Vertical Mover
	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(0, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(11, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(0, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(11, 9)].Occupy(newPiece);

	//Pawns
	for (int i = 0; i < width; i++)
	{
		newPiece = new Piece(1, t);
		newPiece->SetPawn();
		board[Index(i, 3)].Occupy(newPiece);

		newPiece = new Piece(0, t);
		newPiece->SetPawn();
		board[Index(i, 8)].Occupy(newPiece);
	}
}

