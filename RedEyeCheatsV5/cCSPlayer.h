#pragma once
#include "interfaces.h"
#include "cBaseEntity.h"
#include "xor.h"
#include "qAngle.h"
#include "cBaseCombatCharacter.h"
class cCSPlayer : public cBaseEntity
{
public:
	NET(QAngle, m_angEyeAngles, xorStr("DT_CSPlayer"), xorStr("m_angEyeAngles[0]"));
	NET(int32_t, m_nSurvivalTeam, xorStr("DT_CSPlayer"), xorStr("m_nSurvivalTeam"));
	NET(bool, m_bGunGameImmunity, xorStr("DT_CSPlayer"), xorStr("m_bGunGameImmunity"));
	NET(int, m_iShotsFired, xorStr("DT_CSPlayer"), xorStr("m_iShotsFired"));
	NET(int, m_iAccount, xorStr("DT_CSPlayer"), xorStr("m_iAccount"));
	NET(int, m_ArmorValue, xorStr("DT_CSPlayer"), xorStr("m_ArmorValue"));
	NET(int, m_bHasDefuser, xorStr("DT_CSPlayer"), xorStr("m_bHasDefuser"));
	//
	NET(bool, m_bIsDefusing, xorStr("DT_CSPlayer"), xorStr("m_bIsDefusing"));
	NET(bool, m_bIsScoped, xorStr("DT_CSPlayer"), xorStr("m_bIsScoped"));
	NET(bool, m_bHasHelmet, xorStr("DT_CSPlayer"), xorStr("m_bHasHelmet"));
	NET(bool, m_bIsGrabbingHostage, xorStr("DT_CSPlayer"), xorStr("m_bIsGrabbingHostage"));
	//m_bIsGrabbingHostage
	cBaseCombatWeapon* m_hActiveWeapon()
	{
		cBaseCombatCharacter* character = (cBaseCombatCharacter*)this;
		return (cBaseCombatWeapon*)interfaceManager::ientitylist->getClientEntityFromHandle(character->m_hActiveWeaponH());
	}
};