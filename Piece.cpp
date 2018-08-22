#include "Piece.h"

void Piece::Initialize()
{

	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	isWhite = false;
	name = "King";
	abrName = "K";
	abrName2 = "";
	isPromotable = false;
	isPromoted = false;
	didPromoteLastTurn = false;
}

Piece::Piece(bool white1black0, TextureModule * t)
{
	textures = t;
	Initialize();
	isWhite = white1black0;
	TextureSetup();
	SetPosition(Vector2f(0, 0));
}

Piece::Piece(bool white1black0, TextureModule * t, string n)
{
	textures = t;
	Initialize();
	isWhite = white1black0;
	TextureSetup();
	SetPosition(Vector2f(0, 0));

	DeterminePieceType(n, false);

}

//update pieces to keep currently selected textures
void Piece::Update()
{
	pieceName.setFont(*textures->fontSelection);
	pieceName2.setFont(*textures->fontSelection);
	pieceShape.setTexture(*textures->baseShapeSelection);
}

//draw components
void Piece::Draw(RenderWindow * window)
{
	window->draw(pieceShape);
	window->draw(pieceName);
	window->draw(pieceName2);
	for (int i = 0; i < 9; i++)
	{
		window->draw(moveSymbols[i]);
	}
}

//determine how the piece looks based on descriptive strings
void Piece::TextureSetup()
{
	//isPromoted = false;

    //set up name abbreviations
	stringstream ss;
	ss << abrName;
	pieceName.setString(ss.str());
	pieceName.setFont(*textures->fontSelection);
	pieceName.setStyle(sf::Text::Bold);
	pieceName.setCharacterSize(18);
	pieceName.setFillColor(Color::Black);

	ss.str("");
	ss << abrName2;
	pieceName2.setString(ss.str());
	pieceName2.setFont(*textures->fontSelection);
	pieceName2.setStyle(sf::Text::Bold);
	pieceName2.setCharacterSize(18);
	pieceName2.setFillColor(Color::Black);

    //set selected piece texture
	pieceShape.setTexture(*textures->baseShapeSelection);

    //set up move symbols to contain a blank place holder
	for (int i = 0; i < 9; i++)
	{
		moveSymbols[i].setTexture(textures->blank);
		moveSymbols[i].setScale(0.3f, 0.3f);

	}

	//set up move symbols based on movement strings

//Steps
	if (stepMoves.find(" FL ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if(isWhite)
			moveSymbols[5].setTexture(textures->step);
		else
			moveSymbols[7].setTexture(textures->step);
	}
	if (stepMoves.find(" FR ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if (isWhite)
			moveSymbols[3].setTexture(textures->step);
		else
		moveSymbols[1].setTexture(textures->step);

	}
	if (stepMoves.find(" BL ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if (isWhite)
			moveSymbols[7].setTexture(textures->step);
		else
			moveSymbols[5].setTexture(textures->step);
	}
	if (stepMoves.find(" BR ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if (isWhite)
			moveSymbols[1].setTexture(textures->step);
		else
			moveSymbols[3].setTexture(textures->step);
	}
	if (stepMoves.find(" F ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if (isWhite)
			moveSymbols[4].setTexture(textures->step);
		else
			moveSymbols[0].setTexture(textures->step);

	}
	if (stepMoves.find(" L ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		moveSymbols[6].setTexture(textures->step);
	}
	if (stepMoves.find(" R ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		moveSymbols[2].setTexture(textures->step);
	}
	if (stepMoves.find(" B ") != string::npos || stepMoves.find(" K ") != string::npos)
	{
		if (isWhite)
			moveSymbols[0].setTexture(textures->step);
		else
			moveSymbols[4].setTexture(textures->step);
	}

//Ranges
	if (rangeMoves.find(" FL ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[5].setTexture(textures->range);
		else
			moveSymbols[7].setTexture(textures->range);
	}
	if (rangeMoves.find(" FR ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[3].setTexture(textures->range);
		else
			moveSymbols[1].setTexture(textures->range);

	}
	if (rangeMoves.find(" BL ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[7].setTexture(textures->range);
		else
			moveSymbols[5].setTexture(textures->range);
	}
	if (rangeMoves.find(" BR ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[1].setTexture(textures->range);
		else
			moveSymbols[3].setTexture(textures->range);
	}
	if (rangeMoves.find(" F ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[4].setTexture(textures->range);
		else
			moveSymbols[0].setTexture(textures->range);

	}
	if (rangeMoves.find(" L ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		moveSymbols[6].setTexture(textures->range);
	}
	if (rangeMoves.find(" R ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		moveSymbols[2].setTexture(textures->range);
	}
	if (rangeMoves.find(" B ") != string::npos || rangeMoves.find(" Q ") != string::npos)
	{
		if (isWhite)
			moveSymbols[0].setTexture(textures->range);
		else
			moveSymbols[4].setTexture(textures->range);
	}

//Jumps
	if (jumpMoves.find(" FL ") != string::npos)
	{
		if (isWhite)
			moveSymbols[5].setTexture(textures->jump);
		else
			moveSymbols[7].setTexture(textures->jump);
	}
	if (jumpMoves.find(" FR ") != string::npos)
	{
		if (isWhite)
			moveSymbols[3].setTexture(textures->jump);
		else
			moveSymbols[1].setTexture(textures->jump);

	}
	if (jumpMoves.find(" BL ") != string::npos)
	{
		if (isWhite)
			moveSymbols[7].setTexture(textures->jump);
		else
			moveSymbols[5].setTexture(textures->jump);
	}
	if (jumpMoves.find(" BR ") != string::npos)
	{
		if (isWhite)
			moveSymbols[1].setTexture(textures->jump);
		else
			moveSymbols[3].setTexture(textures->jump);
	}
	if (jumpMoves.find(" F ") != string::npos)
	{
		if (isWhite)
			moveSymbols[4].setTexture(textures->jump);
		else
			moveSymbols[0].setTexture(textures->jump);

	}
	if (jumpMoves.find(" L ") != string::npos)
	{
		moveSymbols[6].setTexture(textures->jump);
	}
	if (jumpMoves.find(" R ") != string::npos)
	{
		moveSymbols[2].setTexture(textures->jump);
	}
	if (jumpMoves.find(" B ") != string::npos)
	{
		if (isWhite)
			moveSymbols[0].setTexture(textures->jump);
		else
			moveSymbols[4].setTexture(textures->jump);
	}
	if (jumpMoves.find(" N ") != string::npos)
	{
		moveSymbols[8].setTexture(textures->knight);
		moveSymbols[8].scale(1.5, 1.5);
	}

//Lion
	if (lionMoves.find(" FL ") != string::npos)
	{
		if (isWhite)
			moveSymbols[5].setTexture(textures->directedLion);
		else
			moveSymbols[7].setTexture(textures->directedLion);
	}
	if (lionMoves.find(" FR ") != string::npos)
	{
		if (isWhite)
			moveSymbols[3].setTexture(textures->directedLion);
		else
			moveSymbols[1].setTexture(textures->directedLion);
	}
	if (lionMoves.find(" BL ") != string::npos)
	{
		if (isWhite)
			moveSymbols[7].setTexture(textures->directedLion);
		else
			moveSymbols[5].setTexture(textures->directedLion);
	}
	if (lionMoves.find(" BR ") != string::npos)
	{
		if (isWhite)
			moveSymbols[1].setTexture(textures->directedLion);
		else
			moveSymbols[3].setTexture(textures->directedLion);
	}
	if (lionMoves.find(" F ") != string::npos)
	{
		if (isWhite)
			moveSymbols[4].setTexture(textures->directedLion);
		else
			moveSymbols[0].setTexture(textures->directedLion);
	}

	if (lionMoves.find(" L ") != string::npos)
		moveSymbols[6].setTexture(textures->directedLion);
	if (lionMoves.find(" R ") != string::npos)
		moveSymbols[2].setTexture(textures->directedLion);

	if (lionMoves.find(" B ") != string::npos)
	{
		if (isWhite)
			moveSymbols[0].setTexture(textures->directedLion);
		else
			moveSymbols[4].setTexture(textures->directedLion);
	}
	if (lionMoves.find(" K ") != string::npos)
		moveSymbols[8].setTexture(textures->lion);

    //rotate symbol to face correct direction
	for (int i = 0; i < 9; i++)
		moveSymbols[i].setOrigin(Vector2f(moveSymbols[i].getGlobalBounds().width / 2, moveSymbols[i].getGlobalBounds().height / 2));

	moveSymbols[0].setRotation(0);
	moveSymbols[1].setRotation(45);
	moveSymbols[2].setRotation(90);
	moveSymbols[3].setRotation(135);
	moveSymbols[4].setRotation(180);
	moveSymbols[5].setRotation(225);
	moveSymbols[6].setRotation(270);
	moveSymbols[7].setRotation(315);
}

//sets the positions of the pieces components
void Piece::SetPosition(Vector2f pos)
{
    //set origin to center
	pieceShape.setOrigin(Vector2f(pieceShape.getGlobalBounds().width / 2, pieceShape.getGlobalBounds().height / 2));
    //set position of shape
	pieceShape.setPosition(pos);

    //adjust the abbreviated symbols based on one or two letters
	if (abrName2 == "")
	{
		pieceName.setOrigin(Vector2f(pieceName.getGlobalBounds().width / 2, pieceName.getGlobalBounds().height / 2 + 3));
		pieceName.setPosition(pos);
	}
	else
	{
		pieceName2.setOrigin(Vector2f(pieceName2.getGlobalBounds().width / 2, pieceName2.getGlobalBounds().height / 2 + 3));
		pieceName2.setPosition(Vector2f(pos.x, pos.y - 8));
		pieceName.setOrigin(Vector2f(pieceName.getGlobalBounds().width / 2, pieceName.getGlobalBounds().height / 2 + 3));
		pieceName.setPosition(Vector2f(pos.x, pos.y + 7));
	}

    //set center symbol
	moveSymbols[8].setPosition(Vector2f(pos.x - 5, pos.y));


    //set surrounding symbols based on piece aliegiance
	if (!isWhite)
	{
		int offsety = 20;
		int offsetx = 20;

		pieceShape.setRotation(0);

		moveSymbols[0].setPosition(Vector2f(pos.x - 1, pos.y - offsety));

		moveSymbols[1].setPosition(Vector2f(pos.x + offsetx / 2 + 1, pos.y - offsety / 1.4f));

		moveSymbols[2].setPosition(Vector2f(pos.x + offsetx - 4, pos.y));

		moveSymbols[3].setPosition(Vector2f(pos.x + offsetx - 4, pos.y + offsety - 2));

		moveSymbols[4].setPosition(Vector2f(pos.x +1, pos.y + offsety ));

		moveSymbols[5].setPosition(Vector2f(pos.x - offsetx + 4, pos.y + offsety ));

		moveSymbols[6].setPosition(Vector2f(pos.x - offsetx + 4, pos.y + 2));

		moveSymbols[7].setPosition(Vector2f(pos.x - offsetx / 2 - 2, pos.y - offsety / 1.6f));

		moveSymbols[8].setPosition(Vector2f(pos.x, pos.y - offsety / 2));

		
	}

	else 
	{
		int offsety = 20;
		int offsetx = 20;

		pieceShape.setRotation(180);

		moveSymbols[0].setPosition(Vector2f(pos.x - 1, pos.y - offsety));

		moveSymbols[1].setPosition(Vector2f(pos.x + offsetx - 3, pos.y - offsety - 0.5f));

		moveSymbols[2].setPosition(Vector2f(pos.x + offsetx - 4, pos.y));

		moveSymbols[3].setPosition(Vector2f(pos.x + offsetx - 8, pos.y + offsety - 6.5f));

		moveSymbols[4].setPosition(Vector2f(pos.x + 1, pos.y + offsety));

		moveSymbols[5].setPosition(Vector2f(pos.x - offsetx + 10, pos.y + offsety - 4));

		moveSymbols[6].setPosition(Vector2f(pos.x - offsetx + 4, pos.y + 2));

		moveSymbols[7].setPosition(Vector2f(pos.x - offsetx + 1, pos.y - offsety + 2));

		moveSymbols[8].setPosition(Vector2f(pos.x, pos.y - offsety / 2));
	}
}

//////functions for seting up the piece qualities

void Piece::SetBishop()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = " FL FR BL BR ";
	jumpMoves = "";
	name = "Bishop";
	abrName = "B";
	abrName2 = "";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetBlindTiger()
{
	stepMoves = " FR FL L R BR BL B ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "Blind Tiger";
	abrName = "T";
	abrName2 = "B";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetCopper()
{
	stepMoves = " FR F FL B ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "Copper General";
	abrName = "C";
	abrName2 = "";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetDrunkElephant()
{
	stepMoves = " BL BR L R FL F FR ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "Drunk Elephant";
	abrName = "E";
	abrName2 = "D";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetDragonHorse()
{
	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = " FR FL BR BL ";
	jumpMoves = "";
	name = "Dragon Horse";
	abrName = "H";
	abrName2 = "D";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetDragonKing()
{
	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = " F R L B ";
	jumpMoves = "";
	name = "Dragon King";
	abrName2 = "D";
	abrName = "K";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetFerociousLeopard()
{
	stepMoves = " FR F FL BL B BR ";
	lionMoves = "";
	rangeMoves = " ";
	jumpMoves = "";
	name = "Ferocious Leopard";
	abrName2 = "F";
	abrName = "L";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetGold()
{
	stepMoves = " L FL F FR R B ";
	lionMoves = "";
	rangeMoves = "";
	jumpMoves = "";
	name = "Gold General";
	abrName2 = "";
	abrName = "G";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetGoBetween()
{
	stepMoves = " F B ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "Go Between";
	abrName2 = "G";
	abrName = "B";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetKing()
{
	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "King";
	abrName = "K";
	abrName2 = "";
	isPromotable = false;

	TextureSetup();
}

void Piece::SetKirin()
{
	stepMoves = " FR FL BR BL ";
	lionMoves = "";
	rangeMoves = "";
	jumpMoves = " F L R B ";
	name = "Kirin";
	abrName2 = "";
	abrName = "Kr";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetLance()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = " F ";
	jumpMoves = "  ";
	name = "Lance";
	abrName2 = "";
	abrName = "L";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetLion()
{
	stepMoves = "  ";
	lionMoves = " K ";
	rangeMoves = "";
	jumpMoves = "  ";
	name = "Lion";
	abrName2 = "";
	abrName = "Ln";
	isPromotable = false;

	TextureSetup();
}

void Piece::SetQueen()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = " Q ";
	jumpMoves = "";
	name = "Queen";
	abrName = "Q";
	abrName2 = "";
	isPromotable = false;

	TextureSetup();

}

void Piece::SetRook()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = " F R L B ";
	jumpMoves = "  ";
	name = "Rook";
	abrName2 = "";
	abrName = "R";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetReverseChariot()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = " F B ";
	jumpMoves = "  ";
	name = "Reverse Chariot";
	abrName2 = "R";
	abrName = "C";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetSilver()
{
	stepMoves = " FR FL BR BL F ";
	lionMoves = "";
	rangeMoves = "";
	jumpMoves = "";
	name = "Silver General";
	abrName2 = "";
	abrName = "S";
	isPromotable = true;

	TextureSetup();
}

void Piece::SetSideMover()
{
	stepMoves = " F B ";
	lionMoves = "";
	rangeMoves = " L R ";
	jumpMoves = " ";
	name = "Side Mover";
	abrName2 = "S";
	abrName = "M";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetVerticalMover()
{
	stepMoves = " L R ";
	lionMoves = "";
	rangeMoves = " F B ";
	jumpMoves = " ";
	name = "Vertical Mover";
	abrName2 = "V";
	abrName = "M";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetFlyingStag()
{
	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = " F B ";
	jumpMoves = "";
	name = "Flying Stag";
	abrName = "S";
	abrName2 = "F";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetPrince()
{
	stepMoves = " K ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = " ";
	name = "Prince";
	abrName2 = "";
	abrName = "Pr";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetHornedFalcon()
{
	stepMoves = "  ";
	lionMoves = " F ";
	rangeMoves = " FR R BR B BL L FL ";
	jumpMoves = " ";
	name = "Horned Falcon";
	abrName2 = "H";
	abrName = "F";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetSoaringEagle()
{
	stepMoves = "  ";
	lionMoves = " FR FL ";
	rangeMoves = " F R BR B BL L ";
	jumpMoves = " ";
	name = "Soaring Eagle";
	abrName2 = "S";
	abrName = "E";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetWhiteHorse()
{
	stepMoves = "  ";
	lionMoves = "  ";
	rangeMoves = " F FR B FL ";
	jumpMoves = " ";
	name = "White Horse";
	abrName2 = "W";
	abrName = "H";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetWhale()
{
	stepMoves = "  ";
	lionMoves = "  ";
	rangeMoves = " F BR B BL ";
	jumpMoves = " ";
	name = "Whale";
	abrName2 = "";
	abrName = "W";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetFreeBoar()
{
	stepMoves = "  ";
	lionMoves = "  ";
	rangeMoves = "  BR R FR FL L BL ";
	jumpMoves = " ";
	name = "Free Boar";
	abrName2 = "F";
	abrName = "B";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetFlyingOx()
{
	stepMoves = "  ";
	lionMoves = "  ";
	rangeMoves = "  BR F FR FL B BL ";
	jumpMoves = " ";
	name = "Flying Ox";
	abrName2 = "F";
	abrName = "O";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetKnight()
{
	stepMoves = "  ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = " N ";
	name = "Knight";
	abrName2 = "";
	abrName = "N";
	isPromotable = true;


	TextureSetup();
}
void Piece::SetPawn()
{
	stepMoves = " F ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "";
	name = "Pawn";
	abrName = "P";
	abrName2 = "";
	isPromotable = true;


	TextureSetup();

}

void Piece::SetPheonix()
{
	stepMoves = " F L R B ";
	lionMoves = "";
	rangeMoves = "";
	jumpMoves = " FR FL BR BL ";
	name = "Pheonix";
	abrName2 = "";
	abrName = "Ph";
	isPromotable = true;

	TextureSetup();
}
void Piece::SetStone()
{
	stepMoves = " FL FR ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Stone General";
	abrName2 = "";
	abrName = "St";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetIron()
{
	stepMoves = " FL F FR ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Iron General";
	abrName2 = "";
	abrName = "I";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetCatSword()
{
	stepMoves = " FL FR BR BL ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Cat Sword";
	abrName2 = "C";
	abrName = "S";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetViolentOx()
{
	stepMoves = " 2 F R B L ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Violent Ox";
	abrName2 = "V";
	abrName = "O";
	isPromotable = false;


	TextureSetup();
}

void Piece::SetAngryBoar()
{
	stepMoves = " F R B L ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Angry Boar";
	abrName2 = "A";
	abrName = "B";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetEvilWolf()
{
	stepMoves = " FR F FL R L ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Evil Wolf";
	abrName2 = "E";
	abrName = "W";
	isPromotable = true;


	TextureSetup();
}

void Piece::SetFlyingDragon()
{
	stepMoves = " 2 FL FR BR BL ";
	lionMoves = "";
	rangeMoves = "  ";
	jumpMoves = "  ";
	name = "Flying Dragon";
	abrName2 = "F";
	abrName = "D";
	isPromotable = false;


	TextureSetup();
}

//reset piece properties to new promoted piece
void Piece::Promote()
{
	if (isPromotable && !isPromoted)
	{
		isPromoted = true;
		
		if (name == "Pawn")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Knight")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Evil Wolf")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Angry Boar")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Cat Sword")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Bishop")
		{
			SetDragonHorse();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Stone General")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Iron General")
		{
			SetGold();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Blind Tiger")
		{
			SetFlyingStag();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Copper General")
		{
			SetSideMover();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Drunk Elephant")
		{
			SetPrince();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Dragon Horse")
		{
			SetHornedFalcon();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Dragon King")
		{
			SetSoaringEagle();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Ferocious Leopard")
		{
			SetBishop();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Gold General")
		{
			SetRook();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Kirin")
		{
			SetLion();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Lance")
		{
			SetWhiteHorse();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Pheonix")
		{
			SetQueen();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Rook")
		{
			SetDragonKing();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Go Between")
		{
			SetDrunkElephant();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}

		else if (name == "Reverse Chariot")
		{
			SetWhale();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Silver")
		{
			SetVerticalMover();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Side Mover")
		{
			SetFreeBoar();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
		else if (name == "Vertical Mover")
		{
			SetFlyingOx();
			pieceName.setFillColor(Color::Red);
			pieceName2.setFillColor(Color::Red);
		}
	}
}

//reset the piece to be of the type listed in the history vector
//special logic for peices already promoted so they don't repromote
void Piece::DeterminePieceType(string n, bool promoted)
{
	if (n == "Pawn")
	{
		SetPawn();
		isPromoted = false;

	}
	else if (n == "Bishop" && promoted)
	{
		SetFerociousLeopard();
		isPromoted = false;
		Promote(); 
		
	}
	else if (n == "Bishop" && !promoted)
	{
		SetBishop();
		isPromoted = false;
	}

	else if (n == "Stone General" && !promoted)
	{
		SetStone();
		isPromoted = false;
	}
	else if (n == "Evil Wolf" && !promoted)
	{
		SetEvilWolf();
		isPromoted = false;
	}
	else if (n == "Angry Boar" && !promoted)
	{
		SetAngryBoar();
		isPromoted = false;
	}
	else if (n == "Cat Sword" && !promoted)
	{
		SetCatSword();
		isPromoted = false;
	}
	else if (n == "Violent Ox" && !promoted)
	{
		SetViolentOx();
		isPromoted = false;
	}
	else if (n == "Flying Dragon" && !promoted)
	{
		SetFlyingDragon();
		isPromoted = false;
	}
	else if (n == "Iron General" && !promoted)
	{
		SetIron();
		isPromoted = false;
	}
	else if (n == "Knight" && !promoted)
	{
		SetKnight();
		isPromoted = false;
	}
	else if (n == "Blind Tiger")
	{
		SetBlindTiger();
		isPromoted = false;
	}

	else if (n == "Copper General")
	{
		SetCopper();
		isPromoted = false;
	}

	else if (n == "Drunk Elephant" && promoted)
	{
		SetGoBetween();
		isPromoted = false;
		Promote();
		
	}
	else if (n == "Drunk Elephant" && !promoted)
	{
		SetDrunkElephant();
		isPromoted = false;
	}

	else if (n == "Dragon Horse" && promoted)
	{
		SetBishop();
		isPromoted = false;

		Promote();
	}
	else if (n == "Dragon Horse" && !promoted)
	{
		SetDragonHorse();
		isPromoted = false;
	}
	else if (n == "Dragon King" && promoted)
	{
		SetRook();
		isPromoted = false;
		Promote();

	}

	else if (n == "Dragon King" && !promoted)
	{
		SetDragonKing();
		isPromoted = false;
		
	}
	else if (n == "Ferocious Leopard")
	{
		SetFerociousLeopard();
		isPromoted = false;
	}

	else if (n == "Gold General" && promoted)
	{
		SetPawn(); 
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Gold General" && !promoted)
	{
		SetGold();
		isPromoted = false;
	}


	else if (n == "Kirin")
	{
		SetKirin();
		isPromoted = false;
	}

	else if (n == "Lance")
	{
		SetLance();
		isPromoted = false;
	}

	else if (n == "Lion" && promoted)
	{
		
		SetKirin();
		isPromoted = false;
		Promote();
		
	}
	else if (n == "Lion" && !promoted)
	{
		SetLion();
		isPromoted = false;
	}

	else if (n == "Pheonix")
	{
		SetPheonix();
		isPromoted = false;
	}

	else if (n == "Queen" && promoted)
	{
		SetPheonix();
		isPromoted = false;
		Promote();
	}
	else if (n == "Queen" && !promoted)
	{
		SetQueen();
		isPromoted = false;
	}

	else if (n == "Rook" && promoted)
	{
		SetGold();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Rook" && !promoted)
	{
		SetRook();
		isPromoted = false;
	}

	else if (n == "Go Between" )
	{
		SetGoBetween();
		isPromoted = false;
	}

	else if (n == "Reverse Chariot")
	{
		SetReverseChariot();
		isPromoted = false;
	}
	else if (n == "Silver")
	{
		SetSilver();
		isPromoted = false;
	}
	else if (n == "Side Mover" && promoted)
	{
		SetCopper();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Side Mover" && !promoted)
	{
		SetSideMover();
		isPromoted = false;
	}

	else if (n == "Vertical Mover" && promoted)
	{
		SetSilver();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Vertical Mover" && !promoted)
	{
		SetVerticalMover();	
		isPromoted = false;
	}
	else if (n == "Flying Stag" && promoted)
	{
		SetBlindTiger();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Flying Stag" && !promoted)
	{
		SetFlyingStag();
		isPromoted = false;
	}
	else if (n == "Prince" && promoted)
	{
		SetDrunkElephant();
		isPromoted = false;
		Promote();

	}
	else if (n == "Prince" && !promoted)
	{
		SetPrince();
		isPromoted = false;
	}
	else if (n == "Horned Falcon" && promoted)
	{
		SetDragonHorse();
		isPromoted = false;
		Promote();
	}
	else if (n == "Horned Falcon" && !promoted)
	{
		SetHornedFalcon();
		isPromoted = false;
	}
	else if (n == "Soaring Eagle" && promoted)
	{
		SetDragonKing();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Soaring Eagle" && !promoted)
	{
		SetSoaringEagle();
		isPromoted = false;
	}
	else if (n == "White Horse" && promoted)
	{
		SetLance();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "White Horse" && !promoted)
	{
		SetWhiteHorse();
		isPromoted = false;
	}
	else if (n == "Whale" && promoted)
	{
		SetReverseChariot();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Whale" && !promoted)
	{
		SetWhale();
		isPromoted = false;
	}
	else if (n == "Free Boar" && promoted)
	{
		SetSideMover();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Free Boar" && !promoted)
	{
		SetFreeBoar();
		isPromoted = false;
	}
	else if (n == "Flying Ox" && !promoted)
	{
		SetVerticalMover();
		isPromoted = false;
		Promote(); 
	}
	else if (n == "Flying Ox" && !promoted)
	{
		SetFlyingOx();
		isPromoted = false;
	}
}

