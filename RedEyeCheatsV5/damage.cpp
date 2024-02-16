#include "Damage.h"
#include "variables.h"
#include "painting.h"
#include "log.h"
#include "crashhandler.h"
void Damage::draw()
{
	crashhandler.setDebug("DAMAGES_DEFINE_LOCAL");
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local)) return;
	crashhandler.setDebug("DAMAGES_FIND_CURTIME");
	float CurrentTime = interfaceManager::iglobal->curtime;
	for (int i = 0; i < damage_clouds.size(); i++) {
		crashhandler.setDebug("DAMAGES_1");
		damage_cloud& cloud = damage_clouds[i];
		float TimeDifference = CurrentTime - cloud.Time;
		if (TimeDifference > 3) {
			damage_clouds.erase(damage_clouds.begin() + i);
			continue;
		}
		crashhandler.setDebug("DAMAGES_2");
		cloud.Position.z += TimeDifference / 7;
		Vector ScreenPosition;
		if (Functions::worldToScreen(cloud.Position, ScreenPosition)) {
			crashhandler.setDebug("DAMAGES_3");
			int Alpha = 85 * (3.f - TimeDifference);
			paint->text(ScreenPosition.x, ScreenPosition.y, std::to_string(cloud.Damage).c_str(), Glyphs::feature_esp,  Anchor::Center,cloud.Fatal ? color(255, 0, 0, Alpha) : color(255, 255, 255, Alpha));
		}
		crashhandler.setDebug("DAMAGES_4");
	}
}

void Damage::update(IGameEvent* event)
{
	if (Functions::is_bad_ptr(event)) return;
	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) return;

	if (strcmp(event->GetName(), xorStr("player_hurt")) == 0) {
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (Functions::is_bad_ptr(local)) return;
		if (variables::esp::other::damage) {
			cBasePlayer* hurt = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(event->GetInt(xorStr("userid"))));
			cBasePlayer* attacker = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(event->GetInt(xorStr("attacker"))));
			if (!Functions::is_bad_ptr(hurt) && !Functions::is_bad_ptr(attacker)) {
				if (hurt != local && attacker == local) {
					damage_clouds.push_back({ event->GetInt(xorStr("dmg_health")), interfaceManager::iglobal->curtime, hurt, hurt->hitbox(0), false, event->GetInt(xorStr("dmg_health")) >= hurt->m_iHealth() ? true : false });
				}
			}
		}
	}
}