#include "Game.h"
#include "xor.h"
class CEconItemView
{
public:
	NET(int, m_bInitialized, xorStr("DT_BaseAttributableItem"), xorStr("m_bInitialized"));
	NET(short, m_iItemDefinitionIndex, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemDefinitionIndex"));
	NET(int, m_iEntityLevel, xorStr("DT_BaseAttributableItem"), xorStr("m_iEntityLevel"));
	NET(int, m_iAccountID, xorStr("DT_BaseAttributableItem"), xorStr("m_iAccountID"));
	NET(int, m_iItemIDLow, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemIDLow"));
	NET(int, m_iItemIDHigh, xorStr("DT_BaseAttributableItem"), xorStr("m_iItemIDHigh"));
	NET(int, m_iEntityQuality, xorStr("DT_BaseAttributableItem"), xorStr("m_iEntityQuality"));
	CEconItem* GetSOCData() {
		//static auto fn = reinterpret_cast<CEconItem * (__thiscall*)(CEconItemView*)>(Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F0 83 EC 18 56 8B F1 57 8B 86")));
		//return fn(this);
		return 0;
	}

};