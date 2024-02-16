#pragma once
#include "cBaseEntity.h"
#include "xor.h"
#include "qAngle.h"
#include "vector.h"
using cBaseHandle = unsigned long;
class cBasePlayer : public cBaseEntity
{
public:
	NET(cBaseHandle, m_hViewModel, xorStr("DT_BasePlayer"), xorStr("m_hViewModel[0]"));
	NET(int, m_nTickBase, xorStr("DT_BasePlayer"), xorStr("m_nTickBase"));
	NET(Vector, m_skybox3d, xorStr("DT_BasePlayer"), xorStr("DT_LocalPlayerExclusive"), xorStr("DT_Local"), xorStr("m_skybox3d.origin"));
	NET(int, m_skybox3d_scale, xorStr("DT_BasePlayer"), xorStr("DT_LocalPlayerExclusive"), xorStr("DT_Local"), xorStr("m_skybox3d.scale"));
	NET(HANDLE, m_hObserverTarget, xorStr("DT_BasePlayer"), xorStr("m_hObserverTarget"));
	NET(int, m_iFOV, xorStr("DT_BasePlayer"), xorStr("m_iFOV"));
	NET(int, m_iFOVStart, xorStr("DT_BasePlayer"), xorStr("m_iFOVStart"));
	NET(int, m_fFlags, xorStr("DT_BasePlayer"), xorStr("m_fFlags"));
	NET(int, m_iHealth, xorStr("DT_BasePlayer"), xorStr("m_iHealth"));
	NET(int32_t, m_nSurvivalTeam, xorStr("DT_CSPlayer"), xorStr("m_nSurvivalTeam"));
	NET(cBaseHandle, m_hMyWeapons, xorStr("DT_BaseCombatCharacter"), xorStr("m_hMyWeapons"));
	NET(int, m_iShotsFired, xorStr("DT_CSPlayer"),xorStr("m_iShotsFired"));
	NET(cBaseHandle*, m_hMyWearables, "DT_BaseCombatCharacter", "m_hMyWearables");
	int m_iMaxHealth()
	{
		typedef int(__thiscall *OriginalFn)(void*);
		return virtualFunction<OriginalFn>(this, 122)(this);
	}
	bool sameTeam(cBasePlayer* local) {
		if (Functions::is_bad_ptr(local)) return false;
		if (Functions::isDangerZone())
			return (local->m_nSurvivalTeam() == -1) ? false : (local->m_nSurvivalTeam() == this->m_nSurvivalTeam());
		else
			return this->m_iTeamNum() == local->m_iTeamNum();
		return false;
	}
	NET(Vector, m_vecVelocity, xorStr("DT_BasePlayer"), xorStr("m_vecVelocity[0]"));
	NET(Vector, m_vecViewOffset, xorStr("DT_BasePlayer"), xorStr("m_vecViewOffset[0]"));
	NET(QAngle, m_aimPunchAngle, xorStr("DT_BasePlayer"), xorStr("m_aimPunchAngle"));
	NET(Vector, m_aimPunchAngleV, xorStr("DT_BasePlayer"), xorStr("m_aimPunchAngle"));
};