#pragma once
#include "virtualFunction.h"
#include "Game.h"
#include "xor.h"
#include "vector.h"
#include "ClientClass.h"
#include "Functions.h"
#include "IVModelInfo.h"
#include "cBaseCombatWeapon.h"
#include "IClientEntity.h"
#define new		new( _NORMAL_BLOCK, __FILE__, __LINE__ )
enum MoveType
{
	MOVETYPE_NONE = 0,            /**< never moves */
	MOVETYPE_ISOMETRIC,            /**< For players */
	MOVETYPE_WALK,                /**< Player only - moving on the ground */
	MOVETYPE_STEP,                /**< gravity, special edge handling -- monsters use this */
	MOVETYPE_FLY,                /**< No gravity, but still collides with stuff */
	MOVETYPE_FLYGRAVITY,        /**< flies through the air + is affected by gravity */
	MOVETYPE_VPHYSICS,            /**< uses VPHYSICS for simulation */
	MOVETYPE_PUSH,                /**< no clip to world, push and crush */
	MOVETYPE_NOCLIP,            /**< No gravity, no collisions, still do velocity/avelocity */
	MOVETYPE_LADDER,            /**< Used by players only when going onto a ladder */
	MOVETYPE_OBSERVER,            /**< Observer movement, depends on player's observer mode */
	MOVETYPE_CUSTOM,            /**< Allows the entity to describe its own physics */
};
struct model_t;
class cBaseEntity : public IClientEntity
{
public:
	
	NET(int32_t, m_nModelIndex, xorStr("DT_BaseEntity"), xorStr("m_nModelIndex"));
	NET(float, m_flSimulationTime, xorStr("DT_BaseEntity"), xorStr("m_flSimulationTime"));
	NET(int, m_iTeamNum, xorStr("DT_BaseEntity"), xorStr("m_iTeamNum"));
	NET(Vector, m_vecOrigin, xorStr("DT_BaseEntity"), xorStr("m_vecOrigin"));
	NET(Vector, m_vecMins, xorStr("DT_BaseEntity"), xorStr("m_vecMins"));
	NET(Vector, m_vecMaxs, xorStr("DT_BaseEntity"), xorStr("m_vecMaxs"));
	NET(HANDLE, m_hActiveWeaponH, xorStr("DT_BaseCombatCharacter"),xorStr("m_hActiveWeapon"));
	NET(int, m_fFlags, xorStr("DT_BasePlayer"), xorStr("m_fFlags"));
	NET(bool, m_bSpotted, xorStr("DT_BaseEntity"), xorStr("m_bSpotted"));
	NET_OFF(int, m_iIndex, xorStr("DT_BaseEntity"), xorStr("m_bIsAutoaimTarget"), 0x4);
	NET(HANDLE, m_hOwnerEntity, xorStr("DT_BaseEntity"), xorStr("m_hOwnerEntity"));
	NET(Vector, m_vecViewOffset, xorStr("DT_BasePlayer"), xorStr("m_vecViewOffset[0]"));
	NET(int, m_nTickBase, xorStr("DT_BasePlayer"), xorStr("m_nTickBase"));
	NET(int32_t, m_bSpottedbyMask, xorStr("DT_BaseEntity"), xorStr("m_bSpottedByMask"));
	
	//NET(int, m_iCompetitiveRanking, xorStr("DT_CSPlayerResource"), xorStr("m_iCompetitiveRanking"));
	//NET(int, m_iCompetitiveWins, xorStr("DT_CSPlayerResource"), xorStr("m_iCompetitiveWins");
	Vector m_vecEye()
	{
		return (m_vecViewOffset() + m_vecOrigin());
	}
	cBaseEntity* ownerEntity();
	
	cBaseCombatWeapon* m_hActiveWeapon();
	IClientNetworkable* m_Networkable() {
		
		typedef IClientNetworkable* (__thiscall* GetNetworkableFn)(void*);
		return virtualFunction<GetNetworkableFn>(this, 4)(this);
	}
	int movetype() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x258);
	}
	bool seenBy(int entity) {
		return (m_bSpottedbyMask() & (0x1 << entity)) != 0;
	}
	ClientClass* m_ClientClass() {
		auto Network = m_Networkable();
		typedef ClientClass*(__thiscall* IsDormantFn)(void*);
		return virtualFunction<IsDormantFn>(Network, 2)(Network);
	}
	
	Vector m_vecBone(int bone);
	int y = 0;
	Vector hitbox(int id);
	bool OccludedBySmoke(cBaseEntity* player);
	bool canSee(cBaseEntity* player);
	bool canSee(cBaseEntity* player, int h);
	bool canSee(Vector pos);
	bool CanFire();
	bool nDormant()
	{
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0xED);
	}
};