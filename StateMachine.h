#pragma once

#include "State.h"

class StateMachine
{
public:
	State * gameState;

	State * stateMenu;
	State * stateGameSelect;
	State * stateGame;
	State * stateBlackWin;
	State * stateWhiteWin;
	State * statePauseMenu;
	State * stateSettings;

    //called on state switch event
    void GotoStartMenu(){gameState->GotoStartMenu();}
	void GotoGame() { gameState->GotoGame(); }
	void GotoBlackWin(){gameState->GotoBlackWin();}
	void GotoWhiteWin(){gameState->GotoWhiteWin();}
	void GotoGameSelect(){gameState->GotoGameSelect();}
	void GotoPauseMenu() { gameState->GotoPauseMenu(); }
	void GotoSettings() { gameState->GotoSettings(); }

    //change state- called by states
	void SetState(State* state)
	{
		gameState = state;
	}

    //gets current
	State* GetState()
	{
		return gameState;
	}

    //gets state comparison
    //
	State* GetGameState()
	{
		return stateGame;
	}
	State* GetGameSelectState()
	{
		return stateGameSelect;
	}
	State* GetMenuState()
	{
		return stateMenu;
	}
	State* GetBlackWinState()
	{
		return stateBlackWin;
	}
	State* GetWhiteWinState(){return stateWhiteWin;}
	State* GetPauseState() { return statePauseMenu; }
	State* GetSettingsState() { return stateSettings; }

	bool CompareState(State* state)
	{
		if (state->stateName == gameState->stateName)
			return true;
		return false;
        
	}
    //
    //
};
