#pragma once
#include <Windows.h>
#include "CUserCmd.h"
#include "cBasePlayer.h"
class Triggerbot
{
public:
	void Loop(CUserCmd* cmd);
	void Sync(cBasePlayer* local);
	float TimeStartedTriggering;
private:
	bool Enabled;
	bool Enemies;
	bool Team;
	bool DisableWithKnives;
	int m_iKey;
	float Delay;


	bool All;
	bool Head;
	bool UpperBody;
	bool LowerBody;
	bool Arms;
	bool Legs;
};