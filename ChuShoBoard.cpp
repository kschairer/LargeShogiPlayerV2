#include "ChuShoBoard.h"

ChuShoBoard::ChuShoBoard()
{
	Board();
	width = 10;
	height = 10;
	size = 100;
	name = "ChuSho";

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board.push_back(Space(j * 50 + 275, i * 50 + 247, j, i));
		}
	}

	frame.setSize(Vector2f(50 * width + 5, 50 * height + 5));
	frame.setPosition(Vector2f(247.5, 220));
	frame.setFillColor(Color::Transparent);
	frame.setOutlineThickness(-5);
	frame.setOutlineColor(Color::Black);

}

void ChuShoBoard::SetupPieces(TextureModule * t)
{
	Piece* newPiece;

	//Bishop

	newPiece = new Piece(1, t);
	newPiece->SetBishop();
	board[Index(7, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetBishop();
	board[Index(2, 8)].Occupy(newPiece);

	

	//Drunk Elephant
	newPiece = new Piece(1, t);
	newPiece->SetDrunkElephant();
	board[Index(4, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDrunkElephant();
	board[Index(5, 9)].Occupy(newPiece);

	//Dragon Horse 
	newPiece = new Piece(1, t);
	newPiece->SetDragonHorse();
	board[Index(6, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonHorse();
	board[Index(3, 8)].Occupy(newPiece);

	//Dragon King 
	newPiece = new Piece(1, t);
	newPiece->SetDragonKing();
	board[Index(3, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetDragonKing();
	board[Index(6, 8)].Occupy(newPiece);

	//Ferocious Leopard
	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(1, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetFerociousLeopard();
	board[Index(8, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(1, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetFerociousLeopard();
	board[Index(8, 9)].Occupy(newPiece);

	//Gold General
	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(3, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGold();
	board[Index(6, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(3, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGold();
	board[Index(6, 9)].Occupy(newPiece);

	//Go between
	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(2, 2)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetGoBetween();
	board[Index(7, 2)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(2, 7)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetGoBetween();
	board[Index(7, 7)].Occupy(newPiece);


	//King
	newPiece = new Piece(1, t);
	newPiece->SetKing();
	board[Index(5, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKing();
	board[Index(4, 9)].Occupy(newPiece);

	//Kirin
	newPiece = new Piece(1, t);
	newPiece->SetKirin();
	board[Index(2, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetKirin();
	board[Index(7, 9)].Occupy(newPiece);



	//Lion
	newPiece = new Piece(1, t);
	newPiece->SetLion();
	board[Index(5, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetLion();
	board[Index(4, 8)].Occupy(newPiece);

	//Pheonix
	newPiece = new Piece(1, t);
	newPiece->SetPheonix();
	board[Index(7, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetPheonix();
	board[Index(2, 9)].Occupy(newPiece);

	//Queen
	newPiece = new Piece(1, t);
	newPiece->SetQueen();
	board[Index(4, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetQueen();
	board[Index(5, 8)].Occupy(newPiece);

	//Rook
	newPiece = new Piece(1, t);
	newPiece->SetRook();
	board[Index(2, 1)].Occupy(newPiece);

	
	newPiece = new Piece(0, t);
	newPiece->SetRook();
	board[Index(7, 8)].Occupy(newPiece);

	//Reverse Chariot
	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(0, 0)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetReverseChariot();
	board[Index(9, 0)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(0, 9)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetReverseChariot();
	board[Index(9, 9)].Occupy(newPiece);

	//Side Mover
	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(1, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetSideMover();
	board[Index(8, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(1, 8)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetSideMover();
	board[Index(8, 8)].Occupy(newPiece);

	//Vertical Mover
	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(0, 1)].Occupy(newPiece);

	newPiece = new Piece(1, t);
	newPiece->SetVerticalMover();
	board[Index(9, 1)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(0, 8)].Occupy(newPiece);

	newPiece = new Piece(0, t);
	newPiece->SetVerticalMover();
	board[Index(9, 8)].Occupy(newPiece);

	//Pawns
	for (int i = 0; i < width; i++)
	{
		if (i != 2 && i != 7)
		{
			newPiece = new Piece(1, t);
			newPiece->SetPawn();
			board[Index(i, 2)].Occupy(newPiece);

			newPiece = new Piece(0, t);
			newPiece->SetPawn();
			board[Index(i, 7)].Occupy(newPiece);
		}
	}
}
