#pragma once

#include "StateMachine.h"
#include "SBlackWin.h"
#include "SGame.h"
#include "SGameSelect.h"
#include "SStartMenu.h"
#include "SWhiteWin.h"
#include "SPauseMenu.h"
#include "SSettings.h"


//this class is needed to circumvent the circular inclusion problem that results from the states includeing the state machine but the state machine includeing the states. Call this function when constructing the state machine

class StateMachineIncludeCheat
{
public:

	void StateMachineSetup(StateMachine* sm)
	{
		sm->stateMenu = new SStartMenu(sm);
		sm->stateGame = new SGame(sm);
		sm->stateBlackWin = new SBlackWin(sm);
		sm->stateWhiteWin = new SWhiteWin(sm);
		sm->stateGameSelect = new SGameSelect(sm);
		sm->statePauseMenu = new SPauseMenu(sm);
		sm->stateSettings = new SSettings(sm);
	}
	
};
