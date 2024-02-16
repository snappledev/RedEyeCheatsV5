#pragma once
#include "color.h"
#include "variables.h"
#include "interfaces.h"
class iglow {
public:
	color syncColor();
	void applyGlow(bool enemy,int health,  int maxhealth, GlowObjectDefinition_t& object, color col, bool fullbloom) {
		int greenHealth = (health / maxhealth) * 255;
		int redHealth = 255 - greenHealth;
		object.m_flRed = enemy ? (variables::esp::enemies::glowhealth ? (redHealth / 255.0f) : (col.r() / 255.0f)) : (variables::esp::team::glowhealth ? (redHealth / 255.0f) : (col.r() / 255.0f));
		object.m_flGreen = enemy ? (variables::esp::enemies::glowhealth ? (greenHealth / 255.0f) : (col.g() / 255.0f)) : (variables::esp::team::glowhealth ? (greenHealth / 255.0f) : (col.g() / 255.0f));
		object.m_flBlue = enemy ? (variables::esp::enemies::glowhealth ? 0 : (col.b() / 255.0f)) : (variables::esp::team::glowhealth ? 0 : (col.b() / 255.0f));
		object.m_flAlpha = col.a() / 255.0f;
		object.m_bRenderWhenOccluded = true;
		object.m_bRenderWhenUnoccluded = false;
		object.m_bFullBloomRender = fullbloom;
		
	}
	void loop() {
		
		if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected())
			return;
		if (!Game::local) return;
		int localT = Game::local->m_iTeamNum();
		
		for (int i = 0; i < interfaceManager::glowsystem->m_GlowObjectDefinitions.Count(); i++) {
			GlowObjectDefinition_t& object = interfaceManager::glowsystem->m_GlowObjectDefinitions[i];
			if (Functions::is_bad_ptr(&object)) continue;
			cBaseEntity* entity = reinterpret_cast<cBaseEntity*>(object.m_pEntity);
			if (Functions::is_bad_ptr(entity)) continue;
			
			if (entity->IsDormant()) continue;
		
			if (object.IsUnused()) continue;
			classid class_id = entity->m_ClientClass()->m_ClassID;
			
			switch (class_id) {
			case classid::CCSPlayer:
			
				cBasePlayer* player = reinterpret_cast<cBasePlayer*>(entity);

				if (player->m_iHealth() <= 0) continue;
				bool canSee = Game::local->canSee(entity);
				int team = entity->m_iTeamNum();
				
				if (team != localT) {
					if (!variables::esp::enemies::glow) continue;
					if (!canSee && variables::esp::enemies::visibleOnly) continue;
				}
				if (team == localT) {
					if (!variables::esp::team::glow) continue;
					if (!canSee && variables::esp::team::visibleOnly) continue;
				}
				
				color col = (canSee) ? ((team != localT) ? variables::esp::enemies::glowVisible : variables::esp::team::glowVisible) : ((team != localT) ? variables::esp::enemies::glowInvisible : variables::esp::team::glowInvisible);
				applyGlow(team != localT, player->m_iHealth(), player->m_iMaxHealth(), object, col, (team != localT) ? (variables::esp::enemies::glow == 2) : (variables::esp::team::glow == 2));
			}
		}
	}

};