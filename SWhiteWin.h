#pragma once

#include "State.h"
#include "StateMachine.h"
class SWhiteWin : public State
{
public:
	StateMachine* sm;

	SWhiteWin(StateMachine* nsm)
	{
		sm = nsm;
		stateName = "white win";

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
		//nothing
	}
	virtual void GotoWhiteWin()
	{
		//nothing
	}
	virtual void GotoPauseMenu() {/*nothing*/ }
	virtual void GotoSettings() {/*nothing*/ }
};
