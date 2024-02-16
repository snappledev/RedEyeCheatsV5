#pragma once
#include "Game.h"
#include "interfaces.h"
class cPlayerInventory;
class cInventoryManager
{
public:
	cPlayerInventory* GetLocalPlayerInventory()
	{
		//static auto local_inventory_offset = *reinterpret_cast<uintptr_t*>(Functions::signature(interfaceManager::clientModule, xorStr("8B 8B ? ? ? ? E8 ? ? ? ? 89 44 24 18")) + 0x2);
		//return *reinterpret_cast<cPlayerInventory * *>(this + local_inventory_offset);
		return 0;
	}
};