#pragma once
#include "Game.h"
#include "xor.h"
#include "Functions.h"

enum ItemQuality
{
	ITEM_QUALITY_DEFAULT,
	ITEM_QUALITY_GENUINE,
	ITEM_QUALITY_VINTAGE,
	ITEM_QUALITY_UNUSUAL,
	ITEM_QUALITY_SKIN,
	ITEM_QUALITY_COMMUNITY,
	ITEM_QUALITY_DEVELOPER,
	ITEM_QUALITY_SELFMADE,
	ITEM_QUALITY_CUSTOMIZED,
	ITEM_QUALITY_STRANGE,
	ITEM_QUALITY_COMPLETED,
	ITEM_QUALITY_UNK2,
	ITEM_QUALITY_TOURNAMENT
};

enum ItemRarity
{
	ITEM_RARITY_DEFAULT,
	ITEM_RARITY_COMMON,
	ITEM_RARITY_UNCOMMON,
	ITEM_RARITY_RARE,
	ITEM_RARITY_MYTHICAL,
	ITEM_RARITY_LEGENDARY,
	ITEM_RARITY_ANCIENT,
	ITEM_RARITY_IMMORTAL
};

class CEconItem
{
	unsigned short* getEconItemData();
	void updateEquippedState(unsigned int state);
public:
	uint32_t* getInventory();
	uint32_t* getAccountID();
	uint16_t* getDefIndex();
	uint64_t* getItemID();
	uint64_t* getOriginalID();
	unsigned char* getFlags();
	void setQuality(ItemQuality quality);
	void setRarity(ItemRarity rarity);
	void setOrigin(int origin);
	void setLevel(int level);
	void setInUse(bool in_use);
	void setCustomName(const char* name);
	void setCustomDesc(const char* name);
	void setPaintSeed(float seed);
	void setPaintKit(float kit);
	void setPaintWear(float wear);
	void setStatTrak(int val);
	void addSticker(int index, int kit, float wear, float scale, float rotation);

	template<typename T>
	void SetAttributeValue(int index, T val);
};