#pragma once
#include "cBasePlayer.h"
#include "cBaseViewModel.h"
#include "ClientFrameStage.h"
#include "cBaseAttributableItem.h"
#include "variables.h"
#include <map>
class CCStrike15ItemSchema;
class CCStrike15ItemSystem;
template <typename Key, typename Value>
struct Node_t
{
	int previous_id;		//0x0000
	int next_id;			//0x0004
	void* _unknown_ptr;		//0x0008
	int _unknown;			//0x000C
	Key key;				//0x0010
	Value value;			//0x0014
};

template <typename Key, typename Value>
struct Head_t
{
	Node_t<Key, Value>* memory;		//0x0000
	int allocation_count;			//0x0004
	int grow_size;					//0x0008
	int start_element;				//0x000C
	int next_available;				//0x0010
	int _unknown;					//0x0014
	int last_element;				//0x0018
};
struct String_t
{
	char* buffer;
	int capacity;
	int grow_size;
	int length;
};

struct PaintKit
{
	int id;
	String_t name;
	String_t description;
	String_t item_name;
	String_t material_name;
	String_t image_inventory;
	char pad_0x0054[0x8C];
};
struct Kit
{
	int         m_iIndex;
	std::string m_sName;
};
struct SkinchangerModel
{
	const char* viewmodel;
	const char* icon;
};
struct SkinchangerWeapon
{
	int itemdefinition;
	int m_imenuskin;
	int m_bmenuenabled;
	int m_imenuseed;
	int m_imenustattrack;
	std::string m_smenuname;
	int m_imenuwear;
};

class Skinchanger
{
public:
	void						   Loop(cBasePlayer* local);
	bool					       FindKits();
	SkinchangerWeapon			   WeaponConfigFromIndex(int id);
	const char* ModelConfigFromIndex(int id);
	bool                           IsKnife(int id);
	bool                           IsGlove(int id);
	int                            CorrectSequence(const char* model, int sequence);
	ItemDefinitionIndex            KnifeToIndex();
	ItemDefinitionIndex            GloveToIndex();
	void                           Sync();
	int							   SkinFromIndex(int index);
	int                            GloveSkinFromIndex(int index);
	float                          WearFromIndex(int index);
	void                           CorrectSequences(CRecvProxyData* proxy, cBaseViewModel* model);
	void                           applySkinConfigurations(cBaseAttributableItem* entity, SkinchangerWeapon configuration, const unsigned xuidLow);
	void                           gloveChanger(cBasePlayer* local, uintptr_t xuidLow);
	std::vector<Kit>			   m_vSkins;
	std::vector<Kit>			   m_vGloves;
	std::vector<Kit>		       m_vSticks;
	std::vector<SkinchangerWeapon> m_vSkinchangerWeapons;

private:
};
extern Skinchanger skinchanger;