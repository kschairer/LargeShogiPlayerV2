#pragma once
#include "State.h"
#include "StateMachine.h"
class SPauseMenu : public State
{
public:
	StateMachine* sm;

	SPauseMenu(StateMachine* nsm)
	{
		sm = nsm;
		stateName = "pause";

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
		sm->SetState(sm->GetGameState());
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
	virtual void GotoSettings() { sm->SetState(sm->GetSettingsState()); }
};