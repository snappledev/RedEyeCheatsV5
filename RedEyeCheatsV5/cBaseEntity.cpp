#pragma once
#include "cBaseEntity.h"
#include "interfaces.h"
#include "cBaseCombatWeapon.h"
#include "classes.h"
Vector cBaseEntity::m_vecBone(int bone) {

	if ( bone < 0 || bone > MAXSTUDIOBONES) { return Vector(0, 0, 0); }
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];
	if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
		return boneMatrix[bone].at(3);
	}
	return Vector(0, 0, 0);
}
cBaseCombatWeapon* cBaseEntity::m_hActiveWeapon()
{
	return (cBaseCombatWeapon*)interfaceManager::ientitylist->getClientEntityFromHandle(m_hActiveWeaponH());
}

cBaseEntity* cBaseEntity::ownerEntity() {
	return interfaceManager::ientitylist->getClientEntityFromHandle(m_hOwnerEntity());
}
Vector cBaseEntity::hitbox(int id)
{
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];
	if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
		auto studio_model = interfaceManager::imodelinfo->GetStudiomodel(GetModel());
		if (studio_model) {
			auto hitbox = studio_model->GetHitboxSet(0)->GetHitbox(id);
			if (hitbox) {
				auto
					min = Vector{},
					max = Vector{};

				Functions::VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min);
				Functions::VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max);

				return (min + max) / 2.0f;
			}
		}
	}
	return Vector{};
}
bool cBaseEntity::OccludedBySmoke(cBaseEntity* player)
{
	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);
	static uint32_t GoesThroughSmokeOffset = (uint32_t)Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 EC 08 8B 15 ?? ?? ?? ?? 0F 57 C0"));
	static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;
	return GoesThroughSmokeFunction(m_vecEye(), player->hitbox(0));
}
bool cBaseEntity::CanFire()
{
	cBaseCombatWeapon* weapon = m_hActiveWeapon();
	if (Functions::is_bad_ptr(weapon)) return false;
	float servertime = m_nTickBase() * interfaceManager::iglobal->interval_per_tick;
	if (weapon->flNextPrimaryAttack() - servertime > 0)
		return false;
	return true;
}
bool cBaseEntity::canSee(Vector pos)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;
	ray.Init(m_vecEye(), pos);
	interfaceManager::itrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);
	return tr.fraction > 0.97f;
}
bool cBaseEntity::canSee(cBaseEntity* player, int hit)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;
	ray.Init(m_vecEye(), player->hitbox(hit));
	interfaceManager::itrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);
	bool m_bVisible = tr.hit_entity == player || tr.fraction > 0.97f;
	if (m_bVisible) {
		if (OccludedBySmoke(player))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
	return false;
}
bool cBaseEntity::canSee(cBaseEntity* player)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;
	ray.Init(m_vecEye(), player->hitbox(0));
	interfaceManager::itrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);
	bool m_bVisible = tr.hit_entity == player || tr.fraction > 0.97f;
	if (m_bVisible) {
		if (OccludedBySmoke(player))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
	return false;
}