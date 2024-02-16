#include "interfaces.h"
#include "cBaseEntity.h"
#include "cBasePlayer.h"
#include "cBaseCSGrenade.h"
#include "iEngineTrace.h"
#include "conv.h"
#include "painting.h"
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195f
#define TICK_INTERVAL			(interfaceManager::iglobal->interval_per_tick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f /  PI) )
#define DEG2RAD( x )  ( (float)(x) * (float)( PI / 180.f) )
class grenadeHelper {
public:
	void loop() {
		if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) return;
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (Functions::is_bad_ptr(local)) return;
		if (local->m_iHealth() <= 0) return;
		cBaseCombatWeapon* weapon = local->m_hActiveWeapon();
		if (Functions::is_bad_ptr(weapon)) return;
		ItemDefinitionIndex index = weapon->m_iItemDefinitionIndex();
		bool shouldReturn = true;
		bool isHE = false;
		switch (index) {
		case ItemDefinitionIndex::WEAPON_HEGRENADE:
			isHE = true;
			shouldReturn = false;
			break;
		case ItemDefinitionIndex::WEAPON_SMOKEGRENADE:
		case ItemDefinitionIndex::WEAPON_INC:
		case ItemDefinitionIndex::WEAPON_FLASHBANG:
			shouldReturn = false;
			break;
		}
		if (shouldReturn) { return; }
		
		if (!molotovThrowDetonateTime)
			molotovThrowDetonateTime = interfaceManager::icvars->FindVar("molotov_throw_detonate_time");
		if (!weaponMolotovMaxdetonateslope)
			weaponMolotovMaxdetonateslope = interfaceManager::icvars->FindVar("weapon_molotov_maxdetonateslope");
		if (!svGravity)
			svGravity = interfaceManager::icvars->FindVar("sv_gravity");
		player_info_t playerInfomation;
		cBaseCSGrenade* grenade = (cBaseCSGrenade*)weapon;
		QAngle throwAngle;
		interfaceManager::iengine->GetViewAngles(&throwAngle);
		Functions::Normalize(throwAngle);
		throwAngle.pitch -= (90.f - abs(throwAngle.pitch)) * 0.11111111f;
		Vector forward = Functions::AngleToVector(throwAngle);
		RecvProp* sequence_prop = Game::network.GetNetvarProp(xorStr("DT_BaseCSGrenade"), xorStr("m_flThrowStrength"));
		
		//ThrowStrength = GetNetPropOffset("DT_BaseCSGrenade", "m_flThrowStrength");
		float throwStrengh = grenade->m_flThrowStrength();
		float throwVelocity = fmin(fmax(750.0f * 0.9f, 15.f), 750.f);

		float throwHeight = (throwStrengh * 12.f) - 12.f;
		float v68 = throwVelocity * ((0.7f * throwStrengh) + 0.3f);

		// NOTE: m_vecEyePosition = GetAbsOrigin + m_vecViewOffset
		Vector startPos = local->m_vecEye()+ Vector(0, 0, throwHeight), endPos = startPos + (forward * 22.f);
		CTraceFilter filter;
		filter.pSkip = local;
		trace_t trace;
		Ray_t ray; ray.Init(startPos, endPos, Vector(-2.f, -2.f, -2.f), Vector(2.f, 2.f, 2.f));
		interfaceManager::itrace->TraceRay(ray, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);

		endPos = trace.endpos - (forward * 6.f);
		auto throwPos = (local->m_vecVelocity() * 1.25f) + (forward * v68);
		Vector startPosWorld, endPosWorld;
		float gravity = (svGravity->GetFloat() * 0.4f);
		int grenadeTime = Functions::grenadeToTime(index, molotovThrowDetonateTime->GetFloat());
		
		if (randomFrame <= 0)
			randomFrame = TIME_TO_TICKS(grenadeTime);
		int alpha = 0;
		for (int ticks = TIME_TO_TICKS(grenadeTime); ticks >= 0; --ticks)
		{
			auto throwDir = Vector(throwPos.x, throwPos.y, (throwPos.z + (throwPos.z - (gravity * interfaceManager::iglobal->interval_per_tick))) * 0.5f);
			auto temp = throwDir * interfaceManager::iglobal->interval_per_tick;
			throwPos.z -= gravity * interfaceManager::iglobal->interval_per_tick;
			auto src = endPos, end = endPos + temp;
			Ray_t ray_t; ray_t.Init(src, end, Vector(-2.f, -2.f, -2.f), Vector(2.f, 2.f, 2.f));
			interfaceManager::itrace->TraceRay(ray_t, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);
			if (trace.allsolid)
				throwPos = Vector(0, 0, 0);
			endPos = trace.endpos;
			Vector screenSrc;
			alpha += (1 / TIME_TO_TICKS(grenadeTime));
			if (alpha > (TIME_TO_TICKS(grenadeTime) / 2))
				alpha -= 2 * (1 / TIME_TO_TICKS(grenadeTime));
			float actualAlpha = (alpha / ((TIME_TO_TICKS(grenadeTime) / 2))) * 255;
			if (Functions::worldToScreen(src, screenSrc) && Functions::worldToScreen(endPos, endPosWorld)) {
				paint->line(screenSrc.x, screenSrc.y, endPosWorld.x, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));
				paint->line(screenSrc.x + 1, screenSrc.y, endPosWorld.x + 1, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));
				paint->line(screenSrc.x - 1, screenSrc.y, endPosWorld.x - 1, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));

			}
			
			if (trace.fraction != 1.f) {
				float surfaceElasticity = 1.f;
				Vector throwPos2;
				Functions::physicsClip(throwPos, trace.plane.normal, throwPos2, 2.f);
				if (trace.hit_entity && interfaceManager::iengine->GetPlayerInfo(trace.hit_entity->EntIndex(), &playerInfomation))
					surfaceElasticity = 0.3f;
				throwPos2 *= Functions::clip(surfaceElasticity * 0.45f, 0.f, 0.9f);
				end = endPos + (throwPos2 * ((1.f - trace.fraction) * interfaceManager::iglobal->interval_per_tick));
				if ((index == ItemDefinitionIndex::WEAPON_MOLOTOV || index == ItemDefinitionIndex::WEAPON_INC) && trace.plane.normal.z >= cos(DEG2RAD(weaponMolotovMaxdetonateslope->GetFloat()))) {
					if (trace.plane.normal.z >= cos(DEG2RAD(weaponMolotovMaxdetonateslope->GetFloat())))
						return;
				}
				if (index == ItemDefinitionIndex::WEAPON_TAGRENADE)
					return;
				Ray_t ray_t2; ray_t2.Init(endPos, end, Vector(-2.f, -2.f, -2.f), Vector(2.f, 2.f, 2.f));
				interfaceManager::itrace->TraceRay(ray_t2, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);
				Vector endScreen;
				if (Functions::worldToScreen(end, endScreen) && Functions::worldToScreen(endPos, endPosWorld)) {
					paint->line(endScreen.x, endScreen.y, endPosWorld.x, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));
					paint->line(endScreen.x + 1, endScreen.y, endPosWorld.x + 1, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));
					paint->line(endScreen.x - 1, endScreen.y, endPosWorld.x - 1, endPosWorld.y, (ticks == randomFrame || ticks == randomFrame - 1 || ticks == randomFrame - 2) ? color(215, 0, 0, 120) : color(205, 205, 205, 120));

				}
				endPos = trace.endpos;
				throwPos = throwPos2;
			}
		}
		randomFrame--;
	}
	bool calculatePoints();
	void drawTradjectory();
private:
	ConVar* molotovThrowDetonateTime;
	ConVar* weaponMolotovMaxdetonateslope;
	ConVar* svGravity;
	int randomFrame = 0;
};