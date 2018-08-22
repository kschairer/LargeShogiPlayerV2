#include"Game.h"
#include <fstream>

#include"Piece.h"
#include"Board.h"
#include"ChuShoBoard.h"
#include"StateMachineIncludeCheat.h"
#include<cmath>

Game::Game()
{
//window setup
	//seed random
	srand((unsigned int)time(NULL));
	textures = new TextureModule();

	windowSizeX = 1280;
	windowSizeY = 720;
	framerate = 80;

	//generate a window and limit the frames per second
	window = new RenderWindow(VideoMode((unsigned int)windowSizeX, (unsigned int)windowSizeY), "Large Shogi Player", Style::Close | Style::Titlebar | Style::Resize);
	window->setFramerateLimit(framerate);

//basic visual parts setup
	//hide the desktop mouse cursor to prevent confusion with relative window positions
	window->setMouseCursorVisible(false);

	//set up a view for holding background objects
	viewBackground.setCenter(windowSizeX / 2.0f, windowSizeY / 2.0f);
	viewBackground.setSize(windowSizeX, windowSizeY);
	viewBackground.setViewport(FloatRect(0, 0, 1, 1));
	window->setView(viewBackground);

	//and a view for the board
	viewBoard.setSize(windowSizeX, windowSizeY);
	viewBoard.setViewport(FloatRect(0, 0, 1, 1));

	//these represent the relative position of the mouse to the window
	//one cursor is for the background view
	//the other is for the map view (the difference is that the map 
	//view changes the relative position of the mouse with scrolling and zooming
	//causing difficulty with finding where the mouse actually is)
	mouseCursorBackground.setSize(Vector2f(10, 10));
	mouseCursorBackground.setOutlineColor(Color::Black);
	mouseCursorBackground.setOutlineThickness(-2);
	mouseCursorBackground.setFillColor(Color::White);

	mouseCursorBoard.setSize(Vector2f(10, 10));
	mouseCursorBoard.setOutlineColor(Color::White);
	mouseCursorBoard.setOutlineThickness(-2);
	mouseCursorBoard.setFillColor(Color::Black);

	

//first text to appear
	txtStart.setFont(textures->fontArialI);
	txtStart.setString("Large Shogi Player\n\n Programmed by:\n\tKeith Schairer");
	txtStart.setCharacterSize(80);
	txtStart.setFillColor(Color(255, 255, 255, 255));
	txtStart.setPosition(windowSizeX / 2 - txtStart.getGlobalBounds().width / 2, 200);

//win screen
	txtBlackWin.setFont(textures->fontArial);
	txtBlackWin.setString("Congratulations!\n   Black Wins!");
	txtBlackWin.setCharacterSize(80);
	txtBlackWin.setFillColor(Color(0, 0, 0, 255));
	txtBlackWin.setPosition(windowSizeX / 2 - txtBlackWin.getGlobalBounds().width / 2, 200);

	txtWhiteWin.setFont(textures->fontArial);
	txtWhiteWin.setString("Congratulations!\n   White Wins!");
	txtWhiteWin.setCharacterSize(80);
	txtWhiteWin.setFillColor(Color(255, 255, 255, 255));
	txtWhiteWin.setPosition(windowSizeX / 2 - txtWhiteWin.getGlobalBounds().width / 2, 200);

    int btnCharSize = 40;
    
////things for the game select menu:

	menuBoarder.setSize(Vector2f(380, windowSizeY));
	menuBoarder.setOutlineColor(Color::Black);
	menuBoarder.setOutlineThickness(10);
	menuBoarder.setFillColor(Color::Transparent);
	menuBoarder.setPosition(460,0);

	txtNewGame.setFont(textures->fontArial);
	txtNewGame.setString("New Game");
	txtNewGame.setCharacterSize(60);
	txtNewGame.setFillColor(Color(255, 255, 255));
	txtNewGame.setPosition(100, 80);

	txtLoadGame.setFont(textures->fontArial);
	txtLoadGame.setString("Load Game");
	txtLoadGame.setCharacterSize(60);
	txtLoadGame.setFillColor(Color(255, 255, 255));
	txtLoadGame.setPosition(490, 80);

	txtGameSelectMenu.setFont(textures->fontArial);
	txtGameSelectMenu.setString("Main Menu");
	txtGameSelectMenu.setCharacterSize(60);
	txtGameSelectMenu.setFillColor(Color(255, 255, 255));
	txtGameSelectMenu.setPosition(890, 80);

	btnChuStart = new KButton(textures, "    Chu Shogi", Vector2f(100,200), Vector2f(300,60), Color(0, 0, 0, 255));
	btnChuStart->SetCharSize(btnCharSize);
	vectStartBtns.push_back(btnChuStart);

	btnChuShoStart = new KButton(textures, "Little Chu Shogi", Vector2f(100, 320), Vector2f(300, 60), Color(0, 0, 0, 255));
	btnChuShoStart->SetCharSize(btnCharSize);
	vectStartBtns.push_back(btnChuShoStart);

	btnDaiStart = new KButton(textures, "     Dai Shogi", Vector2f(100, 440), Vector2f(300, 60), Color(0, 0, 0, 255));
	btnDaiStart->SetCharSize(btnCharSize);
	vectStartBtns.push_back(btnDaiStart);

	btnLoadAuto = new KButton(textures, "Load Auto Save", Vector2f(500, 560), Vector2f(295, 60), Color(50, 50, 50, 255));
	btnLoadAuto->SetCharSize(btnCharSize);
	vectStartBtns.push_back(btnLoadAuto);
	vectMenuBtns.push_back(btnLoadAuto);
////in game hud
	btnUndo = new KButton(textures, "Undo", Vector2f(windowSizeX - 25*2 - 110*2, 25), Vector2f(110, 60), Color(50, 50, 50, 255));
	btnUndo->SetCharSize(btnCharSize);
	vectGameBtns.push_back(btnUndo);

	btnRedo = new KButton(textures, "Redo", Vector2f(windowSizeX - 25 - 110, 25), Vector2f(110, 60), Color(50, 50, 50, 255));
	btnRedo->SetCharSize(btnCharSize);
	vectGameBtns.push_back(btnRedo);

	btnMenu = new KButton(textures, "Menu", Vector2f(windowSizeX - 25  - 110, 50 + 60), Vector2f(110, 60), Color(0, 0, 0, 255));
	btnMenu->SetCharSize(btnCharSize);
	vectGameBtns.push_back(btnMenu);

	txtTurn.setFont(textures->fontArial);
	txtTurn.setString("Black");
	txtTurn.setCharacterSize(60);
	txtTurn.setFillColor(Color::Black);
	txtTurn.setPosition(windowSizeX - 25*3 - 65*3, 200);

	txtPieceInfo.setFont(textures->fontArial);
	txtPieceInfo.setString("");
	txtPieceInfo.setCharacterSize(60);
	txtPieceInfo.setFillColor(Color::White);
	txtPieceInfo.setPosition(windowSizeX / 2 - txtPieceInfo.getGlobalBounds().width / 2, 600);

//Pause menu hud
	txtSaveGame.setFont(textures->fontArial);
	txtSaveGame.setString("Save Game");
	txtSaveGame.setCharacterSize(60);
	txtSaveGame.setFillColor(Color(255, 255, 255));
	txtSaveGame.setPosition(107, 80);

	txtMenuTitle.setFont(textures->fontArial);
	txtMenuTitle.setString("Pause Menu");
	txtMenuTitle.setCharacterSize(60);
	txtMenuTitle.setFillColor(Color::White);
	txtMenuTitle.setPosition(870, 80);

	btnMenuBack = new KButton(textures, "        Back", Vector2f(900, 320), Vector2f(285, 60), Color(0, 0, 0, 255));
	btnMenuBack->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnMenuBack);

	btnLoad1 = new KButton(textures, "       Load 1", Vector2f(500, 200), Vector2f(295, 60), Color(50, 50, 50, 255));
	btnLoad1->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnLoad1);
	vectStartBtns.push_back(btnLoad1);

	btnLoad2 = new KButton(textures, "       Load 2", Vector2f(500, 320), Vector2f(295, 60), Color(50, 50, 50, 255));
	btnLoad2->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnLoad2);
	vectStartBtns.push_back(btnLoad2);

	btnLoad3 = new KButton(textures, "       Load 3", Vector2f(500, 440), Vector2f(295, 60), Color(50, 50, 50, 255));
	btnLoad3->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnLoad3);
	vectStartBtns.push_back(btnLoad3);

	btnSave1 = new KButton(textures, "       Save 1", Vector2f(120, 200), Vector2f(285, 60), Color(0, 0, 0, 255));
	btnSave1->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnSave1);

	btnSave2 = new KButton(textures, "       Save 2", Vector2f(120, 320), Vector2f(285, 60), Color(0, 0, 0, 255));
	btnSave2->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnSave2);

	btnSave3 = new KButton(textures, "       Save 3", Vector2f(120, 440), Vector2f(285, 60), Color(0, 0, 0, 255));
	btnSave3->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnSave3);

	btnSettings = new KButton(textures, "    Aesthetics", Vector2f(900, 200), Vector2f(285, 60), Color(0, 0, 0, 255));
	btnSettings->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnSettings);
	vectStartBtns.push_back(btnSettings);

	btnNewGame = new KButton(textures, "         Quit", Vector2f(900, 440), Vector2f(285, 60), Color(0,0,0, 255));
	btnNewGame->SetCharSize(btnCharSize);
	vectMenuBtns.push_back(btnNewGame);

//Settings Menu
	txtSettingsTitle.setFont(textures->fontArial);
	txtSettingsTitle.setString("Aesthetics");
	txtSettingsTitle.setCharacterSize(60);
	txtSettingsTitle.setFillColor(Color::White);
	txtSettingsTitle.setPosition(windowSizeX / 2 - txtSettingsTitle.getGlobalBounds().width / 2, 15);

	txtBackgroundOption.setFont(textures->fontArial);
	txtBackgroundOption.setString("Select the board wood type");
	txtBackgroundOption.setCharacterSize(60);
	txtBackgroundOption.setFillColor(Color::White);
	txtBackgroundOption.setPosition(windowSizeX / 2 - txtBackgroundOption.getGlobalBounds().width / 2 , 100);

	

	txtPieceOption.setFont(textures->fontArial);
	txtPieceOption.setString("Select the piece texture type");
	txtPieceOption.setCharacterSize(60);
	txtPieceOption.setFillColor(Color::White);
	txtPieceOption.setPosition(windowSizeX / 2 - txtPieceOption.getGlobalBounds().width / 2, 270);

	txtFontOption.setFont(*textures->fontSelection);
	txtFontOption.setString("Select the font type");
	txtFontOption.setCharacterSize(60);
	txtFontOption.setFillColor(Color::White);
	txtFontOption.setPosition(windowSizeX / 2 - txtFontOption.getGlobalBounds().width / 2, 420);

	btnSettingsBack = new KButton(textures, "Back", Vector2f(windowSizeX / 2 - 65 / 2, 615), Vector2f(100, 60), Color(0, 0, 0, 255));
	btnSettingsBack->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnSettingsBack);

	float spacing = 80;
	btnBGOptionBeech = new KButton(textures, "Beech", Vector2f(windowSizeX / 2 - 155 - spacing, 190), Vector2f(125, 60), Color(70, 70, 70, 255));
	btnBGOptionBeech->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnBGOptionBeech);
	
	btnBGOptionCherry = new KButton(textures, "Cherry", Vector2f(windowSizeX / 2 - 60, 190), Vector2f(135, 60), Color(70, 70, 70, 255));
	btnBGOptionCherry->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnBGOptionCherry);

	btnBGOptionPoplar = new KButton(textures, "Poplar", Vector2f(windowSizeX / 2 + 40 + spacing, 190), Vector2f(130, 60), Color(70, 70, 70, 255));
	btnBGOptionPoplar->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnBGOptionPoplar);

	txtrSampleBoard.setTexture(*textures->bgSelection);
	txtrSampleBoard.setScale(Vector2f(.1f,.1f));
	txtrSampleBoard.setPosition(spacing * 3 + 85 * 3 + 25 , 100);

	btnShapeOptionPlain = new KButton(textures, "Plain", Vector2f(windowSizeX / 2 - 155 - spacing , 360), Vector2f(100, 60), Color(70, 70, 70, 255));
	btnShapeOptionPlain->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnShapeOptionPlain);

	btnShapeOptionDarker = new KButton(textures, "Portal", Vector2f(windowSizeX / 2 - 65, 360), Vector2f(117, 60), Color(70, 70, 70, 255));
	btnShapeOptionDarker->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnShapeOptionDarker);

	btnShapeOptionPattern = new KButton(textures, "Pattern", Vector2f(windowSizeX / 2 + 30 + spacing, 360), Vector2f(140, 60), Color(70, 70, 70, 255));
	btnShapeOptionPattern->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnShapeOptionPattern);

	txtrSamplePiece.setTexture(*textures->baseShapeSelection);
	//txtrSamplePiece.setScale(Vector2f(2, 2));
	txtrSamplePiece.setPosition(windowSizeX / 2 + 88 + 85 + spacing*2, 365);

	btnFontOptionBuxton = new KButton(textures, "Buxton Sketch", Vector2f(windowSizeX / 2 - 150 / 2- spacing*2 - 130, 510), Vector2f(275, 60), Color(70, 70, 70, 255));
	btnFontOptionBuxton->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnFontOptionBuxton);

	btnFontOptionSegoe = new KButton(textures, "Segoe Script", Vector2f(windowSizeX / 2 - 150 / 2 +15, 510), Vector2f(245, 60), Color(70, 70, 70, 255));
	btnFontOptionSegoe->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnFontOptionSegoe);

	btnFontOptionCardinal = new KButton(textures, "Cardinal", Vector2f(windowSizeX / 2 + 135 + spacing, 510), Vector2f(165, 60), Color(70, 70, 70, 255));
	btnFontOptionCardinal->SetCharSize(btnCharSize);
	vectSettingsBtns.push_back(btnFontOptionCardinal);

//general game vars setup
	gameState = "start";

    
    //
    //State Machine instatiation
    //
	stateMachine = new StateMachine();
	StateMachineIncludeCheat smc;
	smc.StateMachineSetup(stateMachine);
	stateMachine->gameState = stateMachine->stateMenu;
    //
    //

	selectionState = "piece";
	isBlacksTurn = true;
	numOfRounds = 0;
	selectedPieceIndex = -1;

	background.setTexture(*textures->bgSelection);
	background.setScale(Vector2f(0.35f, 0.35f));
    
    backgroundImg.setTexture(*textures->bgSelection);
    backgroundImg.setScale(Vector2f(0.35f, 0.35f));

	
	LoadSettings();

	
}

void Game::Run()
{
	//core program driver
	while (window->isOpen())
	{

		// get the current mouse position in the window
		Vector2i pixelPos = Mouse::getPosition(*window);

		// convert it to world coordinates
		Vector2f worldPos = window->mapPixelToCoords(pixelPos, viewBoard);

		mouseCursorBoard.setPosition(worldPos);

		// convert it to world coordinates
		 worldPos = window->mapPixelToCoords(pixelPos, viewBackground);

		mouseCursorBackground.setPosition(worldPos);


		CheckEvents();
		UpdateObjects();

		Draw();

	}
}

//run through all the events (mouse, keyboard, gamepad)
void Game::CheckEvents()
{
	Event event;
	while (window->pollEvent(event))
	{
		//clicking the x on the window
		if (event.type == sf::Event::Closed)
		{
			window->close();
			SaveGame(-1);
		}

		//any button moves the program to the start menu
		if (/*change this: gameState == "start" to this:*/ stateMachine->CompareState(stateMachine->GetMenuState()))
		{
			if ((event.type == sf::Event::KeyPressed) || event.type == sf::Event::MouseButtonPressed)
			{
				gameState = "game select menu";
				stateMachine->GotoGameSelect();
			}
		}
		
		
		else if (/*gameState == "chu game"*/ stateMachine->GetState() == stateMachine->GetGameState())
		{
			//passes control to helping function with collision logic
			if (event.type == sf::Event::MouseButtonPressed)
			{
				CheckBtnCollisions(false);
			}
			//if (sf::Mouse::isButtonPressed(Mouse::Left))
			//{
			//	CheckBtnCollisions(true);
			//}
			if ((event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(Mouse::Left)))
			{
				CheckSpaceCollisions();				
			}
			if ((/*event.type == sf::Event::MouseButtonPressed &&*/ sf::Mouse::isButtonPressed(Mouse::Right)))
			{
				viewBoard.setCenter((float)Mouse::getPosition(*window).x, (float)Mouse::getPosition(*window).y);
			}
			if ((/*event.type == sf::Event::MouseButtonPressed &&*/ sf::Mouse::isButtonPressed(Mouse::Middle)))
			{
				viewBoard.setCenter(windowSizeX/1.5f, windowSizeY/1.5f);
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0)
					viewBoard.zoom(0.97f);
				else
					viewBoard.zoom(1.03f);
			}
		}
		else if (/*gameState == "black win"*/ stateMachine->GetState() == stateMachine->GetBlackWinState())
		{
			if ((event.type == sf::Event::KeyPressed) || event.type == sf::Event::MouseButtonPressed)
			{
				gameState = "game select menu";
				stateMachine->GotoGameSelect();
			}
		}
		else if (/*gameState == "white win"*/stateMachine->GetState() == stateMachine->GetWhiteWinState())
		{
			if ((event.type == sf::Event::KeyPressed) || event.type == sf::Event::MouseButtonPressed)
			{
				gameState = "game select menu";
				stateMachine->GotoGameSelect();
			}
		}
		else 
		{
			//passes control to helping function with collision logic
			if (event.type == sf::Event::MouseButtonPressed)
			{
				CheckBtnCollisions(false);
			}

		}
	}
}

void Game::Draw()
{
	//erase previous frame
	window->clear();
	//set the view to draw things to
	window->setView(viewBackground);
    
    window->draw(backgroundImg);


	////draw objects based on game state
	if (/*gameState == "start"*/ stateMachine->GetState() == stateMachine->GetMenuState())
    {
		window->draw(txtStart);
    }

	if (/*gameState == "white win"*/stateMachine->GetState() == stateMachine->GetWhiteWinState())
    {
		window->draw(txtWhiteWin);

    }
	if (/*gameState == "black win"*/stateMachine->GetState() == stateMachine->GetBlackWinState())
    {
		window->draw(txtBlackWin);
    }

	if (/*gameState == "game select menu"*/stateMachine->GetState() == stateMachine->GetGameSelectState())
	{
		window->draw(txtGameSelectMenu);
		window->draw(txtNewGame);
		window->draw(txtLoadGame);
		window->draw(menuBoarder);
		for (unsigned int i = 0; i < vectStartBtns.size(); i++)
		{
			vectStartBtns[i]->Draw(window);
		}
	}

	if (/*gameState == "menu"*/stateMachine->GetState() == stateMachine->GetPauseState())
	{
		window->draw(txtMenuTitle);
		window->draw(txtSaveGame);
		window->draw(txtLoadGame);
		window->draw(menuBoarder);
		for (unsigned int i = 0; i < vectMenuBtns.size(); i++)
		{
			vectMenuBtns[i]->Draw(window);
		}
	}

	if (/*gameState.find("settings") != string::npos*/stateMachine->GetState() == stateMachine->GetSettingsState())
	{
		//window->draw(txtrSampleBoard);
		window->draw(txtSettingsTitle);
		window->draw(txtBackgroundOption);
		window->draw(txtPieceOption);
		window->draw(txtFontOption);
		window->draw(txtrSamplePiece);

		for (unsigned int i = 0; i < vectSettingsBtns.size(); i++)
		{
			vectSettingsBtns[i]->Draw(window);
		}
	}

	window->draw(mouseCursorBackground);

	if (/*gameState == "chu game"*/ stateMachine->GetState() == stateMachine->GetGameState())
	{

		window->setView(viewBoard);

		gameBoard->Draw(window);
		window->draw(mouseCursorBoard);

		window->setView(viewBackground);

		for (unsigned int i = 0; i < vectGameBtns.size(); i++)
		{
			vectGameBtns[i]->Draw(window);
		}
		window->draw(txtPieceInfo);
		window->draw(txtTurn);
		window->draw(mouseCursorBackground);


	

		
	}

	//update the screen to show changes
	window->display();
}

void Game::UpdateObjects()
{
	background.setTexture(*textures->bgSelection);
    backgroundImg.setTexture(*textures->bgSelection);
	txtrSampleBoard.setTexture(*textures->bgSelection);
	txtrSamplePiece.setTexture(*textures->baseShapeSelection);
    
    txtFontOption.setFont(*textures->fontSelection);

	if (/*gameState == "game select menu"*/ stateMachine->GetState() == stateMachine->GetGameSelectState())
	{
		//update buttons
		for (unsigned int i = 0; i < vectStartBtns.size(); i++)
			vectStartBtns[i]->Update();


	}
	if (/*gameState == "menu"*/stateMachine->GetState() == stateMachine->GetPauseState())
	{
		//update buttons
		for (unsigned int i = 0; i < vectMenuBtns.size(); i++)
			vectMenuBtns[i]->Update();


	}
	if (/*gameState.find("settings") != string::npos*/stateMachine->GetState() == stateMachine->GetSettingsState())
	{
		//update buttons
		for (unsigned int i = 0; i < vectSettingsBtns.size(); i++)
			vectSettingsBtns[i]->Update();

		txtFontOption.setFont(*textures->fontSelection);

	}
	if (/*gameState == "chu game"*/ stateMachine->GetState() == stateMachine->GetGameState())
	{
		//chuBoard.Update();
		gameBoard->Update();
		//update buttons
		for (unsigned int i = 0; i < vectGameBtns.size(); i++)
			vectGameBtns[i]->Update();

		if (isBlacksTurn)
		{
			txtTurn.setString("Black");
			txtTurn.setFillColor(Color::Black);
			mouseCursorBoard.setFillColor(Color::Black);
			mouseCursorBoard.setOutlineColor(Color::White);
		}
		else
		{
			txtTurn.setString("White");
			txtTurn.setFillColor(Color::White);
			mouseCursorBoard.setFillColor(Color::White);
			mouseCursorBoard.setOutlineColor(Color::Black);

		}

		if (selectedPieceIndex >= 0)
		{
			if (gameBoard->board[selectedPieceIndex].isOccupied)
				txtPieceInfo.setString(gameBoard->board[selectedPieceIndex].occupant->name);
			else
				txtPieceInfo.setString("");
		}

		if(selectionState == "piece")
			txtPieceInfo.setString("");

		txtPieceInfo.setPosition(windowSizeX / 2 - txtPieceInfo.getGlobalBounds().width / 2, 635);
	}
}

void Game::CheckBtnCollisions(bool isBtnHeld)
{
	
	if (/*gameState == "game select menu"*/stateMachine->GetState() == stateMachine->GetGameSelectState())
	{
		for (unsigned int i = 0; i < vectStartBtns.size(); i++)
		{
			//if mousecursor intersects the rectangle of the button
			if (mouseCursorBackground.getGlobalBounds().intersects(vectStartBtns[i]->btnBounds.getGlobalBounds()))
			{
				vectStartBtns[i]->Select();
				StartBtnLogic();
			}
		}
	}
	if (/*gameState == "menu"*/stateMachine->GetState() == stateMachine->GetPauseState())
	{
		for (unsigned int i = 0; i < vectMenuBtns.size(); i++)
		{
			//if mousecursor intersects the rectangle of the button
			if (mouseCursorBackground.getGlobalBounds().intersects(vectMenuBtns[i]->btnBounds.getGlobalBounds()))
			{
				vectMenuBtns[i]->Select();
				MenuBtnLogic();
			}
		}
	}
	if (/*gameState.find("settings") != string::npos*/stateMachine->GetState() == stateMachine->GetSettingsState())
	{
		for (unsigned int i = 0; i < vectSettingsBtns.size(); i++)
		{
			//if mousecursor intersects the rectangle of the button
			if (mouseCursorBackground.getGlobalBounds().intersects(vectSettingsBtns[i]->btnBounds.getGlobalBounds()))
			{
				vectSettingsBtns[i]->Select();
				SettingsBtnLogic(vectSettingsBtns[i]);
			}
		}
	}
	if (/*gameState == "chu game"*/stateMachine->GetState() == stateMachine->GetGameState())
	{
		for (unsigned int i = 0; i < vectGameBtns.size(); i++)
		{
			//if mousecursor intersects the rectangle of the button
			if (mouseCursorBackground.getGlobalBounds().intersects(vectGameBtns[i]->btnBounds.getGlobalBounds()))
			{
				vectGameBtns[i]->Select();
				GameBtnLogic();
			}
		}
	}
}

void Game::StartBtnLogic()
{

	if (btnChuStart->IsSelected())
	{
		gameBoard = new ChuBoard();

		btnChuStart->Deselect();
		//progress game state
		gameState = "chu game";
		stateMachine->GotoGame();
		gameType = "Chu";

		//generate a Chu board
		gameBoard->SetupPieces(textures);
		gameBoard->RedDehighlight();

		viewBoard.zoom(1);

		/*Piece* newPiece;

		newPiece = new Piece(1, textures);
		newPiece->SetKnight();
		chuBoard.board[chuBoard.Index(6, 6)].Occupy(newPiece);
		*/
		vectRedoHistory.clear();
		vectHistory.clear();
	}
	if (btnChuShoStart->IsSelected())
	{
		gameBoard = new ChuShoBoard();

		btnChuShoStart->Deselect();
		//progress game state
		gameState = "chu game";
		stateMachine->GotoGame();
		gameType = "ChuSho";

		//generate a Chu Sho board
		gameBoard->SetupPieces(textures);
		gameBoard->RedDehighlight();

		viewBoard.zoom(0.9f);

		vectRedoHistory.clear();
		vectHistory.clear();
	}

	if (btnDaiStart->IsSelected())
	{
		gameBoard = new DaiBoard();

		btnDaiStart->Deselect();
		//progress game state
		gameState = "chu game";
		stateMachine->GotoGame();
		gameType = "Dai";

		//generate a Chu Sho board
		gameBoard->SetupPieces(textures);
		gameBoard->RedDehighlight();

		viewBoard.zoom(1.3f);
		viewBoard.setCenter(600,450);

		vectRedoHistory.clear();
		vectHistory.clear();
	}

	LoadLogic();
	if (btnSettings->IsSelected())
	{
		btnSettings->Deselect();
		gameState = "settings ";
		stateMachine->GotoSettings();
	}
}

void Game::LoadLogic()
{
	if (btnLoadAuto->IsSelected())
	{
		btnLoadAuto->Deselect();


		LoadGame(-1);
	}

	if (btnLoad1->IsSelected())
	{
		btnLoad1->Deselect();


		LoadGame(1);
	}

	if (btnLoad2->IsSelected())
	{
		btnLoad2->Deselect();


		LoadGame(2);

	}

	if (btnLoad3->IsSelected())
	{
		btnLoad3->Deselect();


		LoadGame(3);
	}
}

void Game::GameBtnLogic()
{
	if (btnUndo->IsSelected())
	{
		btnUndo->Deselect();
		Undo();

		//textures->baseShapeSelection = textures->baseShapeDarker;
	}

	if (btnRedo->IsSelected())
	{
		btnRedo->Deselect();
		Redo();

	}

	if (btnMenu->IsSelected())
	{
		btnMenu->Deselect();
		gameState = "menu";
		stateMachine->GotoPauseMenu();
	}
}

void Game::MenuBtnLogic()
{
	if (btnMenuBack->IsSelected())
	{
		btnMenuBack->Deselect();
		gameState = "chu game";
		stateMachine->GotoGame();

	}
	if (btnSettings->IsSelected())
	{
		btnSettings->Deselect();
		gameState = "settings 1";
		stateMachine->GotoSettings();
	}
	LoadLogic();

	if (btnSave1->IsSelected())
	{
		btnSave1->Deselect();
		SaveGame(1);
		gameState = "chu game";
		stateMachine->GotoGame();

	}

	if (btnSave2->IsSelected())
	{
		btnSave2->Deselect();
		SaveGame(2);
		gameState = "chu game";
		stateMachine->GotoGame();

	}

	if (btnSave3->IsSelected())
	{
		btnSave3->Deselect();
		SaveGame(3);
		gameState = "chu game";
		stateMachine->GotoGame();

	}

	if (btnNewGame->IsSelected())
	{
		btnNewGame->Deselect();
		SaveGame(-1);
		viewBoard.zoom(1);
		gameState = "game select menu";
		stateMachine->GotoGameSelect();


	}
}

void Game::SettingsBtnLogic(KButton *clicked)
{
	if (btnSettingsBack->IsSelected())
	{
		btnSettingsBack->Deselect();

		if (gameState == "settings 1")
		{
			gameState = "menu";
			stateMachine->GotoPauseMenu();
		}
		else
		{
			gameState = "game select menu";
			stateMachine->GotoGameSelect();
		}

		SaveSettings();

	}
	
	if (btnBGOptionBeech->IsSelected() && clicked == btnBGOptionBeech)
	{
		btnBGOptionPoplar->Deselect();
		btnBGOptionCherry->Deselect();
		textures->bgSelection = &textures->bgBeech;
	}
	if (btnBGOptionPoplar->IsSelected() && clicked == btnBGOptionPoplar)
	{
		btnBGOptionBeech->Deselect();
		btnBGOptionCherry->Deselect();
		textures->bgSelection = &textures->bgPoplar;
	}
	if (btnBGOptionCherry->IsSelected() && clicked == btnBGOptionCherry)
	{
		btnBGOptionPoplar->Deselect();
		btnBGOptionBeech->Deselect();
		textures->bgSelection = &textures->bgCherry;
	}

	if (btnShapeOptionPlain->IsSelected() && clicked == btnShapeOptionPlain)
	{
		btnShapeOptionDarker->Deselect();
		btnShapeOptionPattern->Deselect();
		textures->baseShapeSelection = &textures->baseShape;
	}
	if (btnShapeOptionDarker->IsSelected() && clicked == btnShapeOptionDarker)
	{
		btnShapeOptionPattern->Deselect();
		btnShapeOptionPlain->Deselect();
		textures->baseShapeSelection = &textures->baseShapeDarker;
	}
	if (btnShapeOptionPattern->IsSelected() && clicked == btnShapeOptionPattern)
	{
		btnShapeOptionPlain->Deselect();
		btnShapeOptionDarker->Deselect();
		textures->baseShapeSelection = &textures->baseShapePattern;
	}

	if (btnFontOptionBuxton->IsSelected() && clicked == btnFontOptionBuxton)
	{
		btnFontOptionCardinal->Deselect();
		btnFontOptionSegoe->Deselect();
		textures->fontSelection = &textures->fontBuxtonSketch;
	}

	if (btnFontOptionSegoe->IsSelected() && clicked == btnFontOptionSegoe)
	{
		btnFontOptionCardinal->Deselect();
		btnFontOptionBuxton->Deselect();
		textures->fontSelection = &textures->segoesc;
	}

	if (btnFontOptionCardinal->IsSelected() && clicked == btnFontOptionCardinal)
	{
		btnFontOptionBuxton->Deselect();
		btnFontOptionSegoe->Deselect();
		textures->fontSelection = &textures->fontCardinal;
	}
}

void Game::CheckSpaceCollisions()
{

	bool win = false;
	for (int i = 0; i < gameBoard->size; i++)
	{
		// if mousecusorBoard intersects a space
		if (mouseCursorBoard.getGlobalBounds().intersects(gameBoard->board[i].GetFrame().getGlobalBounds()))
		{
			//Check selection state and perform different logic

			//no piece selected
			if (selectionState == "piece")
			{
				//if space has a piece
				if (gameBoard->board[i].isOccupied)
				{
					HighlightSpaces(i, false);
					selectionState = "highlight";
				}
				else
					DehighlightSpaces();
			}
			//piece selected, now spaces are highlighted
			else if (selectionState == "highlight")
			{
				//any invalid click will deselect the piece
				selectionState = "piece";
				
				//black highlights(blacks turn)
				if (gameBoard->board[i].isHighlightedBlack && isBlacksTurn)
				{
					isBlacksTurn = false;
					//if highlighted space is occupied
					if (gameBoard->board[i].isOccupied)
					{
						win = LogCapture(i, selectedPieceIndex, 1);
						if (win)
						{
							gameState = "black win";
							stateMachine->GotoBlackWin();

						}
					}
					else
					{
						LogMove(i, selectedPieceIndex, 1);

					}
					//once a space is selected, then it is safe to dehighlight
					DehighlightSpaces();
				}

				//white highlights(whites turn)
				else if (gameBoard->board[i].isHighlightedWhite && !isBlacksTurn)
				{
					isBlacksTurn = true;
					if (gameBoard->board[i].isOccupied)
					{
						win = LogCapture(i, selectedPieceIndex, 1);

						if (win)
						{
							gameState = "white win";
							stateMachine->GotoWhiteWin();

						}
					}
					else
					{
						LogMove(i, selectedPieceIndex, 1);
					}
					DehighlightSpaces();
				}
				//lion special moves(green highlight)(white)
				else if (gameBoard->board[i].IsHighlightedGreen() && !isBlacksTurn && gameBoard->board[selectedPieceIndex].occupant->isWhite)
				{
					//isBlacksTurn = true;
					if (gameBoard->board[i].isOccupied && !gameBoard->board[i].occupant->isWhite)
					{
						win = LogCapture(i, selectedPieceIndex, 0);

						
						if (win)
						{
							gameState = "white win";
							stateMachine->GotoWhiteWin();

						}

						selectionState = "lion highlight";
						HighlightSpaces(i, true);
					}
					else if (!gameBoard->board[i].isOccupied)
					{
						LogMove(i, selectedPieceIndex, 0);

						selectionState = "lion highlight";
						HighlightSpaces(i, true);
					}
					
				}
				//lion special moves(green highlight)(black)
				else if (gameBoard->board[i].IsHighlightedGreen() && isBlacksTurn && !gameBoard->board[selectedPieceIndex].occupant->isWhite)
				{
					//isBlacksTurn = false;
					if (gameBoard->board[i].isOccupied && gameBoard->board[i].occupant->isWhite)
					{
						win = LogCapture(i, selectedPieceIndex, 0);
						if (win)
						{
							gameState = "black win";
							stateMachine->GotoBlackWin();

						}

						selectionState = "lion highlight";
						HighlightSpaces(i, true);
					}
					else if(!gameBoard->board[i].isOccupied)
					{
						LogMove(i, selectedPieceIndex, 0);

						selectionState = "lion highlight";
						HighlightSpaces(i, true);
					}
					
				}
				else if(gameBoard->board[i].isOccupied)
				{
					DehighlightSpaces();
					HighlightSpaces(i, false);
					selectionState = "highlight";
				}
				else
					DehighlightSpaces();
			}
			//lion move second turn(after green highlight was selected)
			else if (selectionState == "lion highlight")
			{
				
				//Black
				if (gameBoard->board[i].isHighlightedBlack && isBlacksTurn)
				{
					isBlacksTurn = false;
					if (gameBoard->board[i].isOccupied && gameBoard->board[i].occupant->isWhite)
					{
						win = LogCapture(i, selectedPieceIndex, 2);
						if (win)
						{
							gameState = "black win";
							stateMachine->GotoBlackWin();

						}
					}
					else if (!gameBoard->board[i].isOccupied)
					{
						LogMove(i, selectedPieceIndex, 2);

					}
					else
						LogMove(i, selectedPieceIndex, 2);
					selectionState = "piece";
					DehighlightSpaces();
				}
				//White
				else if (gameBoard->board[i].isHighlightedWhite && !isBlacksTurn)
				{
					isBlacksTurn = true;
					if (gameBoard->board[i].isOccupied && !gameBoard->board[i].occupant->isWhite)
					{
						win = LogCapture(i, selectedPieceIndex, 2);
						if (win)
						{
							gameState = "white win";
							stateMachine->GotoWhiteWin();

						}
					}
					else if(!gameBoard->board[i].isOccupied)
					{
						LogMove(i, selectedPieceIndex, 2);
					}
					else
						LogMove(i, selectedPieceIndex, 2);
					selectionState = "piece";
					DehighlightSpaces();
				}

			}

			break;
		}
	}
	
}

void Game::HighlightSpaces(int occupantIndex, bool lion)
{
	DehighlightSpaces();
	if (!lion)
		gameBoard->Highlight(occupantIndex);
	else
		gameBoard->HighlightLion(occupantIndex);
	selectedPieceIndex = occupantIndex;
}

void Game::DehighlightSpaces()
{

	gameBoard->Dehighlight();
	//selectedPieceIndex = -1;
}
void Game::Undo()
{
	if (vectHistory.size() > 0)
	{
		DehighlightSpaces();
		selectionState = "piece";
		string moveRecord = vectHistory.back();

		vector<string> splitRecord = split(moveRecord, '_');

		int moveType = stoi(splitRecord.back());
		if (moveType == 1|| moveType == 2)
			isBlacksTurn = !isBlacksTurn;
		int newIndex = stoi(splitRecord[4]);
		int oldIndex = stoi(splitRecord[0]);
		int isWhite = stoi(splitRecord[2]);

		gameBoard->Occupy(oldIndex, newIndex);
		

		if (splitRecord.size() > 6)
		{
			bool isOpponentWhite = stoi(splitRecord[6]);
			bool isOpponentPromoted = stoi(splitRecord[7]);

			string pieceName = splitRecord[5];
			Piece* newPiece = new Piece(isOpponentWhite, textures);
			newPiece->DeterminePieceType(pieceName, isOpponentPromoted);
			gameBoard->board[newIndex].Occupy(newPiece);

			bool isPromoted = stoi(splitRecord[3]);
			gameBoard->board[oldIndex].occupant->DeterminePieceType(splitRecord[1], isPromoted);
		}
		else
		{
			bool isPromoted = stoi(splitRecord[3]);

			gameBoard->board[oldIndex].occupant->DeterminePieceType(splitRecord[1], isPromoted);
		}

		if (moveType == 2)
		{
			selectionState = "lion highlight";
			HighlightSpaces(oldIndex, true);
		}

		vectRedoHistory.push_back(moveRecord);
		vectHistory.pop_back();
	}
	
}

void Game::Redo()
{
	if (vectRedoHistory.size() > 0)
	{
		DehighlightSpaces();
		selectionState = "piece";
		string moveRecord = vectRedoHistory.back();

		vector<string> splitRecord = split(moveRecord, '_');

		if (splitRecord.size() >= 6)
		{
			int moveType = stoi(splitRecord.back());
			if (moveType == 1 || moveType == 2)
				isBlacksTurn = !isBlacksTurn;
			int newIndex = stoi(splitRecord[4]);
			int oldIndex = stoi(splitRecord[0]);
			bool isWhite = stoi(splitRecord[2]);

			if (splitRecord.size() > 6)
			{
				gameBoard->Capture(newIndex, oldIndex);
			}
			else
				gameBoard->Occupy(newIndex, oldIndex);

			if (moveType == 0)
			{
				selectionState = "lion highlight";
				HighlightSpaces(newIndex, true);
			}
			vectHistory.push_back(moveRecord);
		}

		vectRedoHistory.pop_back();
	}

}

void Game::SaveGame(int fileSlot)
{
	string filename;
	if (fileSlot == 1)
		filename = "save_game1.shogi";
	else if (fileSlot == 2)
		filename = "save_game2.shogi";
	else if (fileSlot == 3)
		filename = "save_game3.shogi";
	else if (fileSlot == -1)
		filename = "autosave.shogi";

	ofstream fout;
	fout.open(filename);
	fout << gameType << endl;

	for (unsigned int i = 0; i < vectHistory.size(); i++)
	{
		fout << vectHistory[i] << endl;
	}
	fout.close();

}

void Game::LoadGame(int fileSlot)
{
	vectRedoHistory.clear();
	vectHistory.clear();
	string filename;
	if (fileSlot == 1)
		filename = "save_game1.shogi";
	else if (fileSlot == 2)
		filename = "save_game2.shogi";
	else if (fileSlot == 3)
		filename = "save_game3.shogi";
	else if (fileSlot == -1)
		filename = "autosave.shogi";

	ifstream fin(filename);
	/*fin.close();
	fin.open(filename);*/

	gameBoard = new ChuBoard();
	viewBoard.zoom(1);

	//check for empty file
	if (!fin.fail())
	{
		getline(fin, gameType);

		if (gameType == "Chu")
		{
			gameState = "chu game";
			stateMachine->GotoGame();

			delete gameBoard;
			gameBoard = new ChuBoard();
			gameBoard->Reset(textures);
			viewBoard.zoom(1);

		}
		else if (gameType == "ChuSho")
		{
			gameState = "chu game";
			stateMachine->GotoGame();

			delete gameBoard;
			gameBoard = new ChuShoBoard();
			gameBoard->Reset(textures);
			viewBoard.zoom(0.9f);


		}
		else if (gameType == "Dai")
		{
			gameState = "chu game";
			stateMachine->GotoGame();

			delete gameBoard;
			gameBoard = new DaiBoard();
			gameBoard->Reset(textures);
			viewBoard.zoom(1.2f);


		}

		string record;
		while (!fin.eof())
		{
			getline(fin, record);
			vectRedoHistory.push_back(record);
			Redo();
		}
	}
	else
	{
		gameType = "Chu";
		gameState = "chu game";
		stateMachine->GotoGame();

		delete gameBoard;
		gameBoard = new ChuBoard();
		gameBoard->Reset(textures);
		viewBoard.zoom(1);
	}
	
	fin.close();
}

bool Game::LogCapture(int newIndex, int oldIndex, int moveType)
{
	stringstream moveRecord;
	moveRecord << oldIndex << "_" << gameBoard->board[oldIndex].occupant->name << "_" << gameBoard->board[oldIndex].occupant->isWhite << "_"<< gameBoard->board[oldIndex].occupant->IsPromoted()
		<< "_" << newIndex << "_" << gameBoard->board[newIndex].occupant->name << "_" << gameBoard->board[newIndex].occupant->isWhite << "_" << gameBoard->board[newIndex].occupant->IsPromoted();
	
	bool win = gameBoard->Capture(newIndex, oldIndex);

	moveRecord << "_" << moveType;

	vectHistory.push_back(moveRecord.str());
	vectRedoHistory.clear();
	return win;
}

void Game::LogMove(int newIndex, int oldIndex, int moveType)
{
	stringstream moveRecord;
	moveRecord << oldIndex << "_" << gameBoard->board[oldIndex].occupant->name << "_" << gameBoard->board[oldIndex].occupant->isWhite << "_" << gameBoard->board[oldIndex].occupant->IsPromoted() << "_" << newIndex;
	
	gameBoard->Occupy(newIndex, oldIndex);

	moveRecord << "_" << moveType;

	
	vectHistory.push_back(moveRecord.str());
	vectRedoHistory.clear();
}

void Game::SaveSettings()
{
	ofstream fout;
	fout.open("settings.defaults");
	if (textures->fontSelection == &textures->fontBuxtonSketch)
	{
		fout << "Buxton" << endl;
	}
	if (textures->fontSelection == &textures->fontCardinal)
	{
		fout << "Cardinal" << endl;
	}
	if (textures->fontSelection == &textures->segoesc)
	{
		fout << "Segoesc" << endl;
	}

	if (textures->bgSelection == &textures->bgBeech)
	{
		fout << "Beech" << endl;
	}
	if (textures->bgSelection == &textures->bgCherry)
	{
		fout << "Cherry" << endl;
	}
	if (textures->bgSelection == &textures->bgPoplar)
	{
		fout << "Poplar" << endl;
	}

	if (textures->baseShapeSelection == &textures->baseShape)
	{
		fout << "Plain" << endl;
	}
	if (textures->baseShapeSelection == &textures->baseShapeDarker)
	{
		fout << "Portal" << endl;
	}
	if (textures->baseShapeSelection == &textures->baseShapePattern)
	{
		fout << "Pattern" << endl;
	}
	
	fout.close();
}

void Game::LoadSettings()
{
	ifstream fin;
	fin.open("settings.defaults");
	if (!fin.fail())
	{
		string setting;
		fin >> setting;
		if (setting == "Buxton")
			textures->fontSelection = &textures->fontBuxtonSketch;

		if (setting == "Cardinal")
			textures->fontSelection = &textures->fontCardinal;

		if (setting == "Segoesc")
			textures->fontSelection = &textures->segoesc;

		fin >> setting;
		if (setting == "Beech")
			textures->bgSelection = &textures->bgBeech;

		if (setting == "Cherry")
			textures->bgSelection = &textures->bgCherry;

		if (setting == "Poplar")
			textures->bgSelection = &textures->bgPoplar;

		fin >> setting;
		if (setting == "Plain")
			textures->baseShapeSelection = &textures->baseShape;

		if (setting == "Portal")
			textures->baseShapeSelection = &textures->baseShapeDarker;

		if (setting == "Pattern")
			textures->baseShapeSelection = &textures->baseShapePattern;
	}

	fin.close();
}




