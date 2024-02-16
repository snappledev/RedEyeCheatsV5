#pragma once
#include "cPlayerInventory.h"
#include "interfaces.h"
class inventoryChanger
{

public:
	inventoryChanger() {

	}
	void createItem() {
		if (!interfaceManager::iLocalInventory) return;

		if (!localInventory && interfaceManager::iLocalInventory) {
			localInventory = interfaceManager::iCSInventoryManager->GetLocalPlayerInventory();
		}
		if (localInventory) {
			CEconItem* newItem = Functions::CreateEconItem();
			*newItem->getAccountID() = localInventory->getSteamID();
			*newItem->getDefIndex() = 1;
			*newItem->getItemID() = 49000;
			*newItem->getInventory() = 1;
			*newItem->getFlags() = 0;
			*newItem->getOriginalID() = 0;
			newItem->setOrigin(8);
			newItem->setPaintKit(37);
			newItem->setPaintSeed(0);
			newItem->setPaintWear(0);
			newItem->setInUse(false);
			newItem->setLevel(1);
			newItem->setRarity(ITEM_RARITY_MYTHICAL);
			localInventory->addEconItem(newItem, 1, 0, 1);
		}

		
	}

	cPlayerInventory* localInventory = NULL;
};