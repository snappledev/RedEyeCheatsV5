#include "Game.h"
#include "xor.h"
#include "cEconItem,h.h"
#include "interfaces.h"
uint32_t* CEconItem::getAccountID()
{
	return reinterpret_cast<uint32_t*>(this + 0x1C);
}
uint64_t* CEconItem::getItemID()
{
	return reinterpret_cast<uint64_t*>(this + 0x8);
}

uint64_t* CEconItem::getOriginalID()
{
	return reinterpret_cast<uint64_t*>(this + 0x10);
}

uint16_t* CEconItem::getDefIndex()
{
	return reinterpret_cast<uint16_t*>(this + 0x24);
}

uint32_t* CEconItem::getInventory()
{
	return reinterpret_cast<uint32_t*>(this + 0x20);
}

unsigned char* CEconItem::getFlags()
{
	return reinterpret_cast<unsigned char*>(this + 0x30);
}

unsigned short* CEconItem::getEconItemData()
{
	return reinterpret_cast<unsigned short*>(this + 0x26);
}

void CEconItem::updateEquippedState(unsigned int state)
{
	static auto fnUpdateEquippedState= reinterpret_cast<int(__thiscall*)(CEconItem*, unsigned int)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 8B 45 08 8B D0 C1 EA 10")));
	fnUpdateEquippedState(this, state);
}

void CEconItem::addSticker(int index, int kit, float wear, float scale, float rotation)
{
	SetAttributeValue<int>(113 + 4 * index, kit);
	SetAttributeValue<float>(114 + 4 * index, wear);
	SetAttributeValue<float>(115 + 4 * index, scale);
	SetAttributeValue<float>(116 + 4 * index, rotation);
}

void CEconItem::setStatTrak(int val)
{
	SetAttributeValue<int>(80, val);
	SetAttributeValue<int>(81, 0);
	setQuality(ITEM_QUALITY_STRANGE);
}
template<typename T>
void CEconItem::SetAttributeValue(int index, T val) {
	auto itemSceme = (DWORD*)Functions::GetItemSchema();
	auto itemScemeOffset = 0;//*(DWORD*)(v15[72] + 4 * index);
	static auto fnSetDynamicAttributeValue = reinterpret_cast<int(__thiscall*)(CEconItem*, DWORD, void*)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 83 EC 3C 53 8B 5D 08 56 57 6A 00")));
	fnSetDynamicAttributeValue(this, itemScemeOffset, &val);
}
void CEconItem::setPaintKit(float kit)
{
	SetAttributeValue<float>(6, kit);
}

void CEconItem::setPaintSeed(float seed)
{
	SetAttributeValue<float>(7, seed);
}

void CEconItem::setPaintWear(float wear)
{
	SetAttributeValue<float>(8, wear);
}

void CEconItem::setQuality(ItemQuality quality)
{
	auto data = *getEconItemData();
	*getEconItemData() = data ^ (data ^ 32 * quality) & 0x1E0;
}

void CEconItem::setRarity(ItemRarity rarity)
{
	auto data = *getEconItemData();
	*getEconItemData() = (data ^ (rarity << 11)) & 0x7800 ^ data;
}

void CEconItem::setOrigin(int origin)
{
	auto data = *getEconItemData();
	*getEconItemData() = data ^ ((unsigned __int8)data ^ (unsigned __int8)origin) & 0x1F;
}

void CEconItem::setLevel(int level)
{
	auto data = *getEconItemData();
	*getEconItemData() = data ^ (data ^ (level << 9)) & 0x600;
}

void CEconItem::setInUse(bool in_use)
{
	auto data = *getEconItemData();
	*getEconItemData() = data & 0x7FFF | (in_use << 15);
}

void CEconItem::setCustomName(const char* name)
{
	static auto Address = Functions::signature(interfaceManager::clientModule, xorStr("E8 ? ? ? ? 8B 46 78 C1 E8 0A A8 01 74 13 8B 46 34"));
	static auto functionSetCustomName = reinterpret_cast<CEconItem * (__thiscall*)(void*, const char*)>(*reinterpret_cast<uintptr_t*>(Address + 1) + Address + 5);
	functionSetCustomName(this, name);
}

void CEconItem::setCustomDesc(const char* name)
{
	static auto Address = Functions::signature(interfaceManager::clientModule, xorStr("E8 ? ? ? ? 33 DB 39 5E 3C 7E 5E"));
	static auto functionSetCustomDescription = reinterpret_cast<CEconItem * (__thiscall*)(void*, const char*)>(*reinterpret_cast<uintptr_t*>(Address + 1) + Address + 5);
	functionSetCustomDescription(this, name);
}