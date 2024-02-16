#pragma once
#include "cBaseEntity.h"
#include "IClientNetworkable.h"
#include "CEconItemView.h"
class cBaseAttributableItem : public cBaseEntity
{
public:
	NET(uint64_t, m_OriginalOwnerXuid, xorStr("DT_BaseAttributableItem"), xorStr("m_OriginalOwnerXuidLow"));
	NET(int32_t, m_OriginalOwnerXuidLow, xorStr("DT_BaseAttributableItem"), xorStr("m_OriginalOwnerXuidLow"));
	NET(int32_t, m_OriginalOwnerXuidHigh, xorStr("DT_BaseAttributableItem"), xorStr("m_OriginalOwnerXuidHigh"));
	NET(int32_t, m_nFallbackStatTrak, xorStr("DT_BaseAttributableItem"), xorStr("m_nFallbackStatTrak"));
	NET(int32_t, m_nFallbackPaintKit, xorStr("DT_BaseAttributableItem"), xorStr("m_nFallbackPaintKit"));
	NET(uintptr_t, m_iEntityQuality, xorStr("DT_BaseAttributableItem"), xorStr("m_iEntityQuality"));
	NET(uintptr_t, m_iAccountID, xorStr("DT_BaseAttributableItem"), xorStr("m_iAccountID"));
	NET(int32_t, m_nFallbackSeed, xorStr("DT_BaseAttributableItem"), xorStr("m_nFallbackSeed"));
	NET(float_t, m_flFallbackWear, xorStr("DT_BaseAttributableItem"), xorStr("m_flFallbackWear"));
	NET(ItemDefinitionIndex, m_iItemDefinitionIndex, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemDefinitionIndex"));
	NET(int32_t, m_iItemIDHigh, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemIDHigh"));
	NET(int32_t, m_iItemIDLow, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemIDLow"));
	NET(char*, m_szCustomName, xorStr("DT_BaseAttributableItem"), xorStr("m_szCustomName"));
	NET_OFF(int, Index, xorStr("DT_BaseEntity"), xorStr("m_bIsAutoaimTarget"), 0x4);
	NET(HANDLE, m_hWeaponWorldModel, xorStr("DT_BaseCombatWeapon"), xorStr("m_hWeaponWorldModel"));
	NET(int, m_iViewModelIndex, xorStr("DT_BaseCombatWeapon"), xorStr("m_iViewModelIndex"));
	CEconItemView& m_Item()
	{
		return *(CEconItemView*)this;
	}
	void SetModelIndex(int modelIndex) {
		typedef void(__thiscall * OriginalFn)(PVOID, int);
		return virtualFunction<OriginalFn>(this, 75)(this, modelIndex);
	}
	IClientNetworkable* m_Networkable()
	{
		typedef IClientNetworkable* (__thiscall * GetNetworkableFn)(void*);
		return virtualFunction<GetNetworkableFn>(this, 4)(this);
	}
	ClientClass* m_ClientClass()
	{
		auto Network = m_Networkable();
		typedef ClientClass* (__thiscall * IsDormantFn)(void*);
		return virtualFunction<IsDormantFn>(Network, 2)(Network);
	}
};