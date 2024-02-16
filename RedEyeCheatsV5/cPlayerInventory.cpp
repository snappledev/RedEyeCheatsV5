#pragma once
#include "cPlayerInventory.h"
#include "cEconItem,h.h"
#include "CEconItemView.h"
#include "interfaces.h"

void cPlayerInventory::removeItem(uint64_t ID)
{
	static auto fnRemoveItem = reinterpret_cast<int(__thiscall*)(void*, int64_t)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 56 57 FF 75 0C 8B F1")));
	fnRemoveItem(this, ID);
}

void cPlayerInventory::removeItem(CEconItem* item)
{
	removeItem(*item->getItemID());
	getBaseTypeCache()->removeObject(item);
}

void cPlayerInventory::clearInventory()
{
	auto BaseTypeCache = this->getBaseTypeCache();
	auto items = BaseTypeCache->getEconItems();
	for (auto item : items)
	{
		removeItem(*item->getItemID());
		BaseTypeCache->removeObject(item);
	}
}

cSharedObjectTypeCache* cPlayerInventory::getBaseTypeCache()
{
	static auto findCache = reinterpret_cast<uintptr_t(__thiscall*)(CClientState*, uint64_t, uint64_t, bool)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 83 EC 1C 0F 10 45 08")));
	static auto fnGCSDK_CSharedObjectCache_CreateBaseTypeCache = reinterpret_cast<cSharedObjectTypeCache * (__thiscall*)(uintptr_t, int)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 51 53 56 8B D9 8D 45 08")));
	auto SOCahce = findCache(interfaceManager::iclientstate + 0x70, *reinterpret_cast<uint64_t*>(this + 0x8), *reinterpret_cast<uint64_t*>(this + 0x10), 0);
	return fnGCSDK_CSharedObjectCache_CreateBaseTypeCache(SOCahce, 1);
}

uint32_t cPlayerInventory::getSteamID()
{
	return *reinterpret_cast<uint32_t*>(this + 0x8);
}

CUtlVector< CEconItemView* >* cPlayerInventory::getInventoryItems()
{
	return reinterpret_cast<CUtlVector<CEconItemView*>*>(this + 0x2C);
}
CEconItemView* cPlayerInventory::getInventoryItemByItemID(int id)
{
	auto items = getInventoryItems();

	for (int i = 0; i < items->Count(); i++)
	{
		auto curElemt = items->Element(i);

		if (!curElemt)
			continue;
		auto socData = curElemt->GetSOCData();

		if (!socData)
			continue;

		if (*socData->getItemID() == id)
			return curElemt;
	}
}
bool cPlayerInventory::addEconItem(CEconItem* item, int a3, int a4, char a5)
{
	static auto functionAddEconItem = reinterpret_cast<CEconItemView * (__thiscall*)(void*, CEconItem*, int, int, char)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 A1 ? ? ? ? 83 EC 14 53 56 57 8B F9 8B 08")));
	getBaseTypeCache()->addObject(item);
	auto ret = functionAddEconItem(this, item, a3, a4, a5);
	/*if (ret) {
		auto i = getInventoryItemByItemID(*item->getItemID());
		*reinterpret_cast<bool*>((uintptr_t)i + 0xA1) = 1;
	}*/
	return false;
}
