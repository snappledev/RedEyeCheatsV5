#pragma once
#include "xor.h"
#include "Functions.h"
#include "interfaces.h"
#include "cSharedObjectTypeCache.h"
class CEconItem;
class CEconItemView;
class cPlayerInventory
{
public:

	void removeItem(uint64_t ID);
	void removeItem(CEconItem* item);
	void clearInventory();
	cSharedObjectTypeCache* getBaseTypeCache();
	uint32_t getSteamID();
	CUtlVector< CEconItemView* >* getInventoryItems();
	CEconItemView* getInventoryItemByItemID(int id);
	bool addEconItem(CEconItem* item, int a3, int a4, char a5);
};