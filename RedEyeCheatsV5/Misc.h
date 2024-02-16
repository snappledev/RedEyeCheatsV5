#pragma once
#include "cBasePlayer.h"
#include "cUserCmd.h"
#include "conv.h"

class Misc
{
public:
	void Autopistol(cBasePlayer* local, CUserCmd* cmd);
	void RevealRanks(CUserCmd* cmd, cBasePlayer* local);
	void LeftHandedKnife(cBasePlayer* local);
	void Bhop(CUserCmd* cmd, cBasePlayer* local);
	void Autostrafe(CUserCmd* cmd, cBasePlayer* local);
	void Loop(CUserCmd* cmd);
	void floatingModels(CUserCmd* cmd, cBasePlayer* local);
	void t();
	void clantagRun(CUserCmd* cmd, cBasePlayer* local);
	void particleEffects(cBasePlayer* local);

	bool m_bLeftHand = false;
	bool m_bKnifeSwitch = false;
	bool m_bOldValue = false;
private:
	ConVar* cl_ragdollgravity;
};
extern Misc misc;