#include "Space.h"

Space::Space()
{
	Initialize();
	pos.x = 0;
	pos.y = 0;
	loc.x = 0;
	loc.y = 0;
}

Space::Space(int x, int y, int gridx, int gridy)
{
	Initialize();
	pos.x = x;
	pos.y = y;
	loc.x = gridx;
	loc.y = gridy;
	frame.setPosition(Vector2f(x , y));
}

void Space::Draw(RenderWindow * window)
{
	window->draw(frame);
	if (isOccupied)
		occupant->Draw(window);
}

//provides the logic for changing colors based on highlighted state
void Space::Update()
{
	if (isHighlightedBlack)
		frame.setFillColor(Color(0, 0, 0, 150));
	else if (isHighlightedWhite)
		frame.setFillColor(Color(255, 255, 255, 150));
	else if (isHighlightedGreen)
		frame.setFillColor(Color(40, 184, 0, 150));
	else
		frame.setFillColor(Color(128,128,128,150));

	if (isHighlightedRed)
	{
		frame.setOutlineColor(Color::Red);
	}
	else
		frame.setOutlineColor(Color::Black);

    //if there is an occupant, update it
	if (isOccupied)
	{
		occupant->SetPosition(pos);
		occupant->Update();
	}
}

//removes current occupant and places new piece
void Space::Capture(Piece * newOccupant)
{
	delete occupant;
	occupant = newOccupant;
	occupant->SetPosition(frame.getPosition());
}

//sets occupant reference to new piece
void Space::Occupy(Piece * newOccupant)
{
	isOccupied = true;
	occupant = newOccupant;
	occupant->SetPosition(frame.getPosition());
}

//provide logic for which side is highlighting green
void Space::HighlightGreen(bool highlighted, string direction)
{
	isHighlightedGreen = highlighted;
	if(direction != "")
		greenDirection = direction;
}

//set up the graphics
void Space::Initialize()
{
	frame.setSize(Vector2f(50, 50));
	frame.setOrigin(Vector2f(50 / 2, 50 / 2));
	frame.setPosition(Vector2f(0, 0));
	frame.setFillColor(Color::Transparent);
	frame.setOutlineThickness(-2);
	frame.setOutlineColor(Color::Black);

	isHighlightedBlack = false;
	isHighlightedWhite = false;
	isHighlightedGreen = false;
	isHighlightedRed = false;
	isOccupied = false;
}
