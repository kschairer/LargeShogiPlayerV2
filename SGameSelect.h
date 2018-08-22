#pragma once
#include "State.h"
#include "StateMachine.h"
class SGameSelect : public State
{
public:
	StateMachine* sm;

	SGameSelect(StateMachine* nsm)
	{
		sm = nsm;
		stateName = "game select";

	}

	virtual void GotoStartMenu()
	{
		sm->SetState(sm->GetMenuState());
	}
	virtual void GotoGameSelect()
	{
		//nothing
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
	virtual void GotoSettings() {sm->SetState(sm->GetSettingsState());}
};