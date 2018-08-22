#pragma once

#include "State.h"
#include "StateMachine.h"
class SGame : public State
{
public:
	StateMachine* sm;

	SGame(StateMachine* nsm)
	{
		sm = nsm;
		stateName = "game";

	}

	virtual void GotoStartMenu()
	{
		sm->SetState(sm->GetMenuState());

	}
	virtual void GotoGameSelect()
	{
		sm->SetState(sm->GetGameSelectState());
	}
	virtual void GotoGame()
	{
		//nothing
	}
	virtual void GotoBlackWin()
	{
		sm->SetState(sm->GetBlackWinState());

	}
	virtual void GotoWhiteWin()
	{
		sm->SetState(sm->GetWhiteWinState());

	}
	virtual void GotoPauseMenu() { sm->SetState(sm->GetPauseState()); }
	virtual void GotoSettings() {/*nothing*/ }
};
