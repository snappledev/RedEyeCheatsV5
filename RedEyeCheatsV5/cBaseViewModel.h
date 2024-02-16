#pragma once
#include "cBaseEntity.h"
#include "Game.h"
class cBaseViewModel : public cBaseEntity
{
public:
	NET(int, vm_nModelIndex, xorStr("DT_BaseViewModel"), xorStr("m_iViewModelIndex"));
	NET(HANDLE, m_hOwner, xorStr("DT_BaseViewModel"), xorStr("m_hOwner"));
	NET(HANDLE, m_hWeapon, xorStr("DT_BaseViewModel"), xorStr("m_hWeapon"));
	NETPROP(m_nSequence,xorStr("DT_BaseViewModel"), xorStr("m_nSequence"));
	void SendViewModelMatchingSequence(int sequence)
	{
		typedef  void(__thiscall * OriginalFn)(void*, int);
		return virtualFunction<OriginalFn>(this, 241)(this, sequence);
	}
	void SetModelIndex(int sequence)
	{
		typedef  void(__thiscall * OriginalFn)(void*, int);
		virtualFunction<OriginalFn>(this, 75)(this, sequence);
	}
};