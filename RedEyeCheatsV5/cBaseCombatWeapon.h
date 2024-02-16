#pragma once
#include "classes.h"
#include "xor.h"
class cBaseCombatWeapon
{
public:
	NET(ItemDefinitionIndex, m_iItemDefinitionIndex, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemDefinitionIndex"));
	NET(int32_t, m_iViewModelIndex, xorStr("DT_BaseCombatWeapon"), xorStr("m_iViewModelIndex"));
	NET(float, flNextPrimaryAttack, xorStr("DT_BaseCombatWeapon"), xorStr("m_flNextPrimaryAttack"));
	NET(HANDLE, m_hWeaponWorldModel, xorStr("DT_BaseCombatWeapon"), xorStr("m_hWeaponWorldModel"));
	NET(int, m_iPrimaryReserveAmmoCount, xorStr("DT_BaseCombatWeapon"), xorStr("m_iPrimaryReserveAmmoCount"));
	NET(bool, m_bInReload, xorStr("DT_BaseCombatWeapon"), xorStr("m_bInReload"));
	NET(int, m_iClip1, xorStr("DT_BaseCombatWeapon"), xorStr("m_iClip1"));
	NET(bool, m_bCanReload, xorStr("DT_BaseCombatWeapon"), xorStr("m_bCanReload"));
	NET(int, m_zoomLevel, xorStr("DT_WeaponCSBaseGun"), xorStr("m_zoomLevel"));
	IClientNetworkable* m_Networkable() {
		typedef IClientNetworkable* (__thiscall * GetNetworkableFn)(void*);
		return virtualFunction<GetNetworkableFn>(this, 4)(this);
	}
	CSWeaponInfo* CSWeaponData()
	{
		typedef CSWeaponInfo* (__thiscall * OriginalFn)(void*);
		return virtualFunction<OriginalFn>(this, 461)(this);
	}
	ClientClass* m_ClientClass() {
		auto Network = m_Networkable();
		typedef ClientClass* (__thiscall * IsDormantFn)(void*);
		return virtualFunction<IsDormantFn>(Network, 2)(Network);
	}

};
