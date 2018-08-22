#include "Board.h"

Board::Board()
{
	directions[0] = " FL ";
	directions[1] = " F ";
	directions[2] = " FR ";
	directions[3] = " L ";
	directions[4] = " R ";
	directions[5] = " BL ";
	directions[6] = " B ";
	directions[7] = " BR ";
}
void Board::SetupPieces(TextureModule * t)
{
}
void Board::Reset(TextureModule *t)
{
    // this replaces:
    //
	BoardIterator bi = CreateIterator();
	while (bi.hasNext())
	{
		Space* currItem = (Space*)bi.next();
		if (currItem->isOccupied)
			delete currItem->occupant;
	}
    //this:
    //
	/*for (int i = 0; i < size; i++)
	{
		if (board[i].isOccupied)
			delete board[i].occupant;
	}*/
	SetupPieces(t);
}

void Board::Draw(RenderWindow * window)
{
	BoardIterator bi = CreateIterator();
	while (bi.hasNext())
	{
		Space* currItem = (Space*)bi.next();
		
		currItem->Draw(window);
	}
	window->draw(frame);
	/*for (int i = 0; i < size; i++)
	{
		board[i].Draw(window);
	}*/
}

void Board::Update()
{
	BoardIterator bi = CreateIterator();
	while (bi.hasNext())
	{
		Space* currItem = (Space*)bi.next();

		currItem->Update();
	}
	/*for (int i = 0; i < size; i++)
	{
		board[i].Update();
	}*/
}

void Board::RedDehighlight()
{
	BoardIterator bi = CreateIterator();
	while (bi.hasNext())
	{
		Space* currItem = (Space*)bi.next();

		currItem->isHighlightedRed = false;
	}
	/*for (int i = 0; i < size; i++)
	{
		board[i].isHighlightedRed = false;
	}*/
}

void Board::Dehighlight()
{
	BoardIterator bi = CreateIterator();
	while (bi.hasNext())
	{
		Space* currItem = (Space*)bi.next();

		currItem->isHighlightedBlack = false;
		currItem->isHighlightedWhite = false;
		currItem->HighlightGreen(false, "");
	}
	/*for (int i = 0; i < size; i++)
	{
		board[i].isHighlightedBlack = false;
		board[i].isHighlightedWhite = false;
		board[i].HighlightGreen(false, "");
	}*/
}

void Board::Highlight(int occupantIndex)
{
	Vector2f loc = board[occupantIndex].GetLocation();

	//Black movement
	if (!board[occupantIndex].occupant->isWhite)
	{
		int i = 0;
		for (int offsety = -1; offsety <= 1; offsety++)
		{
			for (int offsetx = -1; offsetx <= 1; offsetx++)
			{
				if (!(offsetx == 0 && offsety == 0))
				{
					//step
					if (board[occupantIndex].occupant->stepMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->stepMoves.find(" K ") != string::npos)
					{
						if (board[occupantIndex].occupant->stepMoves.find(" 2 ") != string::npos)
						{
							int k = 1;
							while ((loc.x + (offsetx * k) < width) && (loc.x + (offsetx * k) >= 0) && (loc.y + (offsety * k) < height) && (loc.y + (offsety * k) >= 0))
							{
								if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isOccupied)
								{
									if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].occupant->isWhite)
									{
										board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedBlack = true;
										k++;
										break;
									}
									else
									{
										k++;
										break;
									}
								}
								else
									board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedBlack = true;
								if (k >= 2)
									break;
								k++;
							}
						}
						else
						{
							if ((loc.x + offsetx < width) && (loc.x + offsetx >= 0) && (loc.y + offsety < height) && (loc.y + offsety >= 0))
							{
								if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
								{
									if (board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
									{
										board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedBlack = true;
									}
								}
								else
									board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedBlack = true;
							}
						}
					}
					//range
					if (board[occupantIndex].occupant->rangeMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->rangeMoves.find(" Q ") != string::npos)
					{
						int k = 1;
						while ((loc.x + (offsetx * k) < width) && (loc.x + (offsetx * k) >= 0) && (loc.y + (offsety * k) < height) && (loc.y + (offsety * k) >= 0))
						{
							if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isOccupied)
							{
								if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].occupant->isWhite)
								{
									board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedBlack = true;
									k++;
									break;
								}
								else
								{
									k++;
									break;
								}
							}
							else
								board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedBlack = true;
							k++;
						}
					}

					//jump
					if (board[occupantIndex].occupant->jumpMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->jumpMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx * 2 <  width) && (loc.x + offsetx * 2 >= 0) && (loc.y + offsety * 2 <  height) && (loc.y + offsety * 2 >= 0))
						{
							if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isOccupied)
							{
								if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].occupant->isWhite)
								{
									board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedBlack = true;
								}
							}
							else
								board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedBlack = true;
						}
					}
					//lion
					if (board[occupantIndex].occupant->lionMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx * 2 <  width) && (loc.x + offsetx * 2 >= 0) && (loc.y + offsety * 2 <  height) && (loc.y + offsety * 2 >= 0))
						{
							if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isOccupied)
							{
								if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].occupant->isWhite)
									board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedBlack = true;
							}
							else
								board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedBlack = true;
						}
						if ((loc.x + offsetx <  width) && (loc.x + offsetx >= 0) && (loc.y + offsety <  height) && (loc.y + offsety >= 0))
						{
							if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
							{
								if (board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
									board[Index(loc.x + offsetx, loc.y + offsety)].HighlightGreen(true, directions[i]);
							}
							else
								board[Index(loc.x + offsetx, loc.y + offsety)].HighlightGreen(true, directions[i]);
						}
					}

					i++;
				}
			}
		}
		int offset = 1;
		
		//shogi knight move
		if (board[occupantIndex].occupant->jumpMoves.find(" N ") != string::npos)
		{
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{

					if ((i == -1 && j == 2) || (i == 1 && j == 2))
					{
						if ((loc.x + i <  width) && (loc.x + i >= 0) && (loc.y - j <  height) && (loc.y - j >= 0))
						{
							if (board[Index(loc.x + i, loc.y - j)].isOccupied)
							{
								if (board[Index(loc.x + i, loc.y - j)].occupant->isWhite)
									board[Index(loc.x + i, loc.y - j)].isHighlightedBlack = true;
							}
							else
								board[Index(loc.x + i, loc.y - j)].isHighlightedBlack = true;
						}
					}
				}
			}

		}

		//lion knightjump moves
		offset = 2;
		if (board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
		{
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{

					if ((i == -2 && (j == -1 || j == 1)) || (i == -1 && (j == -2 || j == 2)) || (i == 1 && (j == -2 || j == 2)) || (i == 2 && (j == -1 || j == 1)))
					{
						if ((loc.x + i <  width) && (loc.x + i >= 0) && (loc.y - j <  height) && (loc.y - j >= 0))
						{
							if (board[Index(loc.x + i, loc.y - j)].isOccupied)
							{
								if (board[Index(loc.x + i, loc.y - j)].occupant->isWhite)
									board[Index(loc.x + i, loc.y - j)].isHighlightedBlack = true;
							}
							else
								board[Index(loc.x + i, loc.y - j)].isHighlightedBlack = true;
						}
					}
				}
			}

		}
		
	}
	//white pieces are upside down
	else
	{
		int i = 0;
		for (int offsety = 1; offsety >= -1; offsety--)
		{
			for (int offsetx = -1; offsetx <= 1; offsetx++)
			{
				if (!(offsetx == 0 && offsety == 0))
				{
					//step
					if (board[occupantIndex].occupant->stepMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->stepMoves.find(" K ") != string::npos)
					{
						if (board[occupantIndex].occupant->stepMoves.find(" 2 ") != string::npos)
						{
							int k = 1;
							while ((loc.x + (offsetx * k) < width) && (loc.x + (offsetx * k) >= 0) && (loc.y + (offsety * k) < height) && (loc.y + (offsety * k) >= 0))
							{
								if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isOccupied)
								{
									if (!board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].occupant->isWhite)
									{
										board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedWhite = true;
										k++;
										break;
									}
									else
									{
										k++;
										break;
									}
								}
								else
									board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedWhite = true;
								if (k >= 2)
									break;
								k++;
							}
						}
						else
						{
							if ((loc.x + offsetx < width) && (loc.x + offsetx >= 0) && (loc.y + offsety < height) && (loc.y + offsety >= 0))
							{
								if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
								{
									if (!board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
									{
										board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedWhite = true;
									}
								}
								else
									board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedWhite = true;
							}
						}
					}
					//range
					if (board[occupantIndex].occupant->rangeMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->rangeMoves.find(" Q ") != string::npos)
					{
						int k = 1;
						while ((loc.x + (offsetx * k) < width) && (loc.x + (offsetx * k) >= 0) && (loc.y + (offsety * k) < height) && (loc.y + (offsety * k) >= 0))
						{
							if (board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isOccupied)
							{
								if (!board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].occupant->isWhite)
								{
									board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedWhite = true;
									k++;
									break;
								}
								else
								{
									k++;
									break;
								}
							}
							else
								board[Index(loc.x + (offsetx * k), loc.y + (offsety * k))].isHighlightedWhite = true;
							k++;
						}
					}

					//jump
					if (board[occupantIndex].occupant->jumpMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->jumpMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx * 2 <  width) && (loc.x + offsetx * 2 >= 0) && (loc.y + offsety * 2 <  height) && (loc.y + offsety * 2 >= 0))
						{
							if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isOccupied)
							{
								if (!board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].occupant->isWhite)
								{
									board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedWhite = true;
								}
							}
							else
								board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedWhite = true;
						}
					}
					//lion
					if (board[occupantIndex].occupant->lionMoves.find(directions[i]) != string::npos || board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx * 2 <  width) && (loc.x + offsetx * 2 >= 0) && (loc.y + offsety * 2 <  height) && (loc.y + offsety * 2 >= 0))
						{
							if (board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isOccupied)
							{
								if (!board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].occupant->isWhite)
									board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedWhite = true;
							}
							else
								board[Index(loc.x + offsetx * 2, loc.y + offsety * 2)].isHighlightedWhite = true;
						}
						if ((loc.x + offsetx <  width) && (loc.x + offsetx >= 0) && (loc.y + offsety <  height) && (loc.y + offsety >= 0))
						{
							if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
							{
								if (!board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
									board[Index(loc.x + offsetx, loc.y + offsety)].HighlightGreen(true, directions[i]);
							}
							else
								board[Index(loc.x + offsetx, loc.y + offsety)].HighlightGreen(true, directions[i]);
						}
					}

					i++;
				}
			}
		}
		int offset = 1;

		//shogi knight move
		if (board[occupantIndex].occupant->jumpMoves.find(" N ") != string::npos)
		{
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{

					if ((i == -1 && j == -2) || (i == 1 && j == -2))
					{
						if ((loc.x + i <  width) && (loc.x + i >= 0) && (loc.y - j <  height) && (loc.y - j >= 0))
						{
							if (board[Index(loc.x + i, loc.y - j)].isOccupied)
							{
								if (!board[Index(loc.x + i, loc.y - j)].occupant->isWhite)
									board[Index(loc.x + i, loc.y - j)].isHighlightedWhite = true;
							}
							else
								board[Index(loc.x + i, loc.y - j)].isHighlightedWhite = true;
						}
					}
				}
			}

		}

		//lion knightjump moves
		offset = -2;
		if (board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
		{
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{

					if ((i == -2 && (j == -1 || j == 1)) || (i == -1 && (j == -2 || j == 2)) || (i == 1 && (j == -2 || j == 2)) || (i == 2 && (j == -1 || j == 1)))
					{
						if ((loc.x + i <  width) && (loc.x + i >= 0) && (loc.y - j <  height) && (loc.y - j >= 0))
						{
							if (board[Index(loc.x + i, loc.y - j)].isOccupied)
							{
								if (!board[Index(loc.x + i, loc.y - j)].occupant->isWhite)
									board[Index(loc.x + i, loc.y - j)].isHighlightedWhite = true;
							}
							else
								board[Index(loc.x + i, loc.y - j)].isHighlightedWhite = true;
						}
					}
				}
			}

		}
		
	}
}

void Board::HighlightLion(int occupantIndex)
{
	Vector2f loc = board[occupantIndex].GetLocation();
	//black
	if (!board[occupantIndex].occupant->isWhite)
	{
		int i = 0;
		for (int offsety = -1; offsety <= 1; offsety++)
		{
			for (int offsetx = -1; offsetx <= 1; offsetx++)
			{
				if (!(offsetx == 0 && offsety == 0))
				{
					

					//step
					if ((board[occupantIndex].occupant->lionMoves.find(directions[i]) != string::npos && board[occupantIndex].GetLionDirection() == directions[i]) || board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx < width) && (loc.x + offsetx >= 0) && (loc.y + offsety < height) && (loc.y + offsety >= 0))
						{
							if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
							{
								if (board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
								{
									board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedBlack = true;
								}

							}
							else
								board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedBlack = true;
						}
						if ((loc.x - offsetx < width) && (loc.x - offsetx >= 0) && (loc.y - offsety < height) && (loc.y - offsety >= 0))
						{
							if (board[Index(loc.x - offsetx, loc.y - offsety)].isOccupied)
							{
								if (board[Index(loc.x - offsetx, loc.y - offsety)].occupant->isWhite)
								{
									board[Index(loc.x - offsetx, loc.y - offsety)].isHighlightedBlack = true;
								}

							}
							else
								board[Index(loc.x - offsetx, loc.y - offsety)].isHighlightedBlack = true;
						}
					}
					

					i++;
				}
			}
		}
		

	
		board[Index(loc.x, loc.y)].isHighlightedBlack = true;
	
	}
	//white
	else if (board[occupantIndex].occupant->isWhite)
	{
		board[Index(loc.x, loc.y)].isHighlightedWhite = true;
		int i = 0;
		for (int offsety = 1; offsety >= -1; offsety--)
		{
			for (int offsetx = -1; offsetx <= 1; offsetx++)
			{
				if (!(offsetx == 0 && offsety == 0))
				{


					//step
					if ((board[occupantIndex].occupant->lionMoves.find(directions[i]) != string::npos && board[occupantIndex].GetLionDirection() == directions[i]) || board[occupantIndex].occupant->lionMoves.find(" K ") != string::npos)
					{
						if ((loc.x + offsetx < width) && (loc.x + offsetx >= 0) && (loc.y + offsety < height) && (loc.y + offsety >= 0))
						{
							if (board[Index(loc.x + offsetx, loc.y + offsety)].isOccupied)
							{
								if (!board[Index(loc.x + offsetx, loc.y + offsety)].occupant->isWhite)
								{
									board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedWhite = true;
								}

							}
							else
								board[Index(loc.x + offsetx, loc.y + offsety)].isHighlightedWhite = true;
						}
						if ((loc.x - offsetx < width) && (loc.x - offsetx >= 0) && (loc.y - offsety < height) && (loc.y - offsety >= 0))
						{
							if (board[Index(loc.x - offsetx, loc.y - offsety)].isOccupied)
							{
								if (!board[Index(loc.x - offsetx, loc.y - offsety)].occupant->isWhite)
								{
									board[Index(loc.x - offsetx, loc.y - offsety)].isHighlightedWhite = true;
								}

							}
							else
								board[Index(loc.x - offsetx, loc.y - offsety)].isHighlightedWhite = true;
						}
					}


					i++;
				}
			}
		}
	}
}

void Board::Occupy(int newIndex, int oldIndex)
{
	RedDehighlight();
	Piece* movingPiece = board[oldIndex].occupant;
	board[oldIndex].Deoccupy();
	board[oldIndex].isHighlightedRed = true;

	board[newIndex].Occupy(movingPiece);
	board[newIndex].isHighlightedRed = true;

	for (int i = 0; i < size; i++)
	{
		if(board[i].isOccupied)
			board[i].occupant->didPromoteLastTurn = false;
	}

	Vector2f loc = board[newIndex].GetLocation();
	if (name == "Chu")
	{
		if (movingPiece->isWhite && loc.y >= 8)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 3)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}
	else if (name == "ChuSho")
	{
		if (movingPiece->isWhite && loc.y >= 7)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 2)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}
	else if (name == "Dai")
	{
		if (movingPiece->isWhite && loc.y >= 10)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 4)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}
}

bool Board::Capture(int newIndex, int oldIndex)
{
	RedDehighlight();

	bool win = true;
	Piece* movingPiece = board[oldIndex].occupant;
	board[oldIndex].Deoccupy();
	board[oldIndex].isHighlightedRed = true;

	if (board[newIndex].occupant->name == "King" || board[newIndex].occupant->name == "Prince")
	{
		Piece* royalPiece = board[newIndex].occupant;

		for (int i = 0; i < size; i++)
		{
			if (i != newIndex)
			{
				if (board[i].isOccupied)
				{
					if ((board[i].occupant->name == "King" || board[i].occupant->name == "Prince") && board[i].occupant->isWhite == royalPiece->isWhite)
					{
						win = false;
					}
				}
			}
		}
	}
	else
		win = false;

	delete board[newIndex].occupant;

	board[newIndex].Occupy(movingPiece);
	board[newIndex].isHighlightedRed = true;



	for (int i = 0; i < size; i++)
	{
		if (board[i].isOccupied)
			board[i].occupant->didPromoteLastTurn = false;
	}

	Vector2f loc = board[newIndex].GetLocation();
	if (name == "Chu")
	{
		if (movingPiece->isWhite && loc.y >= 8)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 3)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}
	else if (name == "ChuSho")
	{
		if (movingPiece->isWhite && loc.y >= 7)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 2)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}
	else if (name == "Dai")
	{
		if (movingPiece->isWhite && loc.y >= 10)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
		else if (!movingPiece->isWhite && loc.y <= 4)
		{
			movingPiece->Promote();
			movingPiece->didPromoteLastTurn = true;

		}
	}

	return win;
}

BoardIterator Board::CreateIterator()
{
	return BoardIterator(&board);
}

