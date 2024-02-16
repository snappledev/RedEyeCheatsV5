#pragma once
#include "cBaseEntity.h"
class cBaseCSGrenade : public cBaseEntity
{
public:
	NET(float, m_flThrowStrength, xorStr("DT_BaseCSGrenade"), xorStr("m_flThrowStrength"));
	CSWeaponInfo* CSWeaponData()
	{
		typedef CSWeaponInfo* (__thiscall* OriginalFn)(void*);
		return virtualFunction<OriginalFn>(this, 460)(this);
	}
};