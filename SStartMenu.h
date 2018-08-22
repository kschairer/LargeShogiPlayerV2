#pragma once

#include "State.h"
#include "StateMachine.h"
class SStartMenu: public State
{
public:
	StateMachine *sm;

	SStartMenu(StateMachine* nsm)
	{
		stateName = "start";
		sm = nsm;
	}

	virtual void GotoStartMenu()
	{
		//nothing
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
	virtual void GotoPauseMenu(){/*nothing*/}
	virtual void GotoSettings() {/*nothing*/ }

};