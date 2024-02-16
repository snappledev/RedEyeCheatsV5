#pragma once
#include <Windows.h>
#include "virtualFunction.h"
#include "cBaseEntity.h"
class iEntityList
{
public:
	cBaseEntity* getClientEntity(int entnum)
	{
		typedef cBaseEntity* (__thiscall* function)(PVOID, int);
		return virtualFunction<function>(this, 3)(this, entnum);
	}
	cBaseEntity* getClientEntityFromHandle(HANDLE hEnt)
	{
		typedef cBaseEntity* (__thiscall* function)(PVOID, HANDLE);
		return virtualFunction<function>(this, 4)(this, hEnt);
	}
	int getHighestEntityIndex(void)
	{
		typedef int(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 6)(this);
	}
};