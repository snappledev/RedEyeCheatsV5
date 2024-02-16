#include "DeathMarkers.h"
#include "cBasePlayer.h"
#include "Interfaces.h"
#include "painting.h"
#include "log.h"
#include "crashhandler.h"
void Markers::draw() {
	if (variables::esp::other::DeathFlags) {
		crashhandler.setDebug("MARKERS_1");
		
		if (!marks.empty()) {
			crashhandler.setDebug("MARKERS_2");
			for (int i = 0; i < marks.size(); i++) {
				mark& mrk = marks[i];
				Vector flb, brt, blb, frt, frb, brb, blt, flt;
				Vector min = mrk.Min + mrk.Position;
				Vector max = mrk.Max + mrk.Position;
				crashhandler.setDebug("MARKERS_3");
				Vector points[] = { Vector(min.x, min.y, min.z),
					Vector(min.x, max.y, min.z),
					Vector(max.x, max.y, min.z),
					Vector(max.x, min.y, min.z),
					Vector(max.x, max.y, max.z),
					Vector(min.x, max.y, max.z),
					Vector(min.x, min.y, max.z),
					Vector(max.x, min.y, max.z) };
				crashhandler.setDebug("MARKERS_4");
				if (!Functions::worldToScreen(points[3], flb) || !Functions::worldToScreen(points[5], brt)
					|| !Functions::worldToScreen(points[0], blb) || !Functions::worldToScreen(points[4], frt)
					|| !Functions::worldToScreen(points[2], frb) || !Functions::worldToScreen(points[1], brb)
					|| !Functions::worldToScreen(points[6], blt) || !Functions::worldToScreen(points[7], flt))
					continue;
				crashhandler.setDebug("MARKERS_5");
				Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
				float X = flb.x;
				float Y = flb.y;
				float XW = flb.x;
				float YH = flb.y;
				for (int i = 1; i < 8; i++) {
					if (X > arr[i].x)
						X = arr[i].x;
					if (YH < arr[i].y)
						YH = arr[i].y;
					if (XW < arr[i].x)
						XW = arr[i].x;
					if (Y > arr[i].y)
						Y = arr[i].y;
				}
				crashhandler.setDebug("MARKERS_6");
				float w = Functions::clip(XW - X, 120.f, 9999.f);
				int alpha = Functions::clip((interfaceManager::iglobal->curtime - mrk.curtime) * 510, 0.f, 255.f);
				crashhandler.setDebug("MARKERS_7");
				paint->scalineTriangle(
					X,
					Y - (w / 8),
					X + (w / 2),
					Y - (w / 8),
					X + (w / 4),
					Y, color(20, 20, 20, alpha));
				crashhandler.setDebug("MARKERS_8");
				paint->rectangle(
					X,
					Y - (w / 8) - (w / 4),
					(w / 2),
					(w / 4),
					color(20, 20, 20, alpha));
				crashhandler.setDebug("MARKERS_9");
				paint->scalineTriangle(
					(int)(X + 2),
					(int)(Y - (w / 8)),

					(int)(X + (w / 2) - 2),
					(int)(Y - (w / 8)),

					(int)(X + (w / 4)),
					(int)(Y - 2), mrk.enemy ? color(180, 0, 0, alpha) : color(0, 0, 180, alpha));
				paint->text(X + (w / 4), Y - (w / 4), "DEATH", Glyphs::feature_esp, Anchor::Center, mrk.enemy ? color(180, 0, 0, alpha) : color(0, 0, 180, alpha));
				crashhandler.setDebug("MARKERS_10");
			}
		}
		crashhandler.setDebug("MARKERS_11");
		for (int i = 0; i < marks.size(); i++) {
			mark& mrk = marks[i];
			crashhandler.setDebug("MARKERS_12");
			if (interfaceManager::iglobal->curtime - mrk.curtime > 60.0f) {
				marks.erase(marks.begin() + i);
			}
			crashhandler.setDebug("MARKERS_13");
		}
	}
}
void Markers::update(IGameEvent* _event) {
	
	if (Functions::is_bad_ptr(_event) || !interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) {
		marks.clear();
		return;
	}
	if (strcmp(_event->GetName(), xorStr("round_start")) == 0)
		marks.clear();
	if (variables::esp::other::DeathFlags) {
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (!Functions::is_bad_ptr(local)) {
			if (strcmp(_event->GetName(), xorStr("player_death")) == 0) {
				cBasePlayer* dead = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(_event->GetInt(xorStr("userid"))));
				if (!Functions::is_bad_ptr(dead)) {
					player_info_t pinfo;
					if (interfaceManager::iengine->GetPlayerInfo(dead->m_iIndex(), &pinfo)) {
						marks.push_back({ dead->m_vecOrigin(), dead->m_vecMaxs(), dead->m_vecMins(), pinfo.name, !dead->sameTeam(local), interfaceManager::iglobal->curtime });
					}
				}
			}
		}
	}
}