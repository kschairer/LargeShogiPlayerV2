#pragma once


class State
{
public:
	string stateName;
	virtual void GotoStartMenu() =0;
	virtual void GotoGameSelect() = 0;
	virtual void GotoGame() =0;
	virtual void GotoBlackWin() =0;
	virtual void GotoWhiteWin() =0;
	virtual void GotoPauseMenu() = 0;
	virtual void GotoSettings() = 0;

	//State() {};
};