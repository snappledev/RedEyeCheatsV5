#pragma once
#include "cBaseEntity.h"
#include "Game.h"
#include "cBaseCombatWeapon.h"


class cBaseCombatCharacter : public cBaseEntity
{
public:
	NET(HANDLE, m_hActiveWeaponH, xorStr("DT_BaseCombatCharacter"), xorStr("m_hActiveWeapon"));
	NET(cBaseCombatWeapon*, m_hMyWeapons, xorStr("DT_BaseCombatCharacter"), xorStr("m_hMyWeapons"));
	NET(HANDLE*, m_hMyWearables, xorStr("DT_BaseCombatCharacter"), xorStr("m_hMyWearables"));
};