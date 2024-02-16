#include "esp.h"
#include "variables.h"
#include "classes.h"
#include "inputManager.h"
#include "debugmanager.h"
#include "log.h"
#include "crashhandler.h"
#include "edgeAim.h"
void espFeature::loop() {
	crashhandler.setDebug("ESP_GAME_CHECKS");
	if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;
	crashhandler.setDebug("ESP_DEBUG_MAIN3_CHECK");
	if (!variables::debug::main3) return;
	crashhandler.setDebug("ESP_DEFINE_LOCAL");
	cBaseEntity* local = interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	cBasePlayer* localBaseP = (cBasePlayer*)local;
	crashhandler.setDebug("ESP_LOCAL_BAD");
	if (Functions::is_bad_ptr(local)) return;
	crashhandler.setDebug("ESP_BEGIN_LOOP");
	
	for (int i = 0; i < interfaceManager::ientitylist->getHighestEntityIndex(); i++) {
		cBaseEntity* entity = interfaceManager::ientitylist->getClientEntity(i);
		if (Functions::is_bad_ptr(entity)) continue;
		//crashhandler.setDebug("ESP_ENTITY_LOCAL");
		if (entity == local) continue;
		
		//crashhandler.setDebug("ESP_ENTITY_CLIENTCLACSS");
		ClientClass* clientclass = entity->m_ClientClass();
		//crashhandler.setDebug("ESP_ENTITY_BAD_CLIENTCLACSS");
		if (Functions::is_bad_ptr(clientclass)) continue;
		if (!variables::debug::main4) continue;
		Vector origin = entity->m_vecOrigin();
		if ((origin.x == 0 && origin.y == 0 && origin.z == 0)) continue;
		//crashhandler.setDebug("ESP_ENTITY_ISCS");
		if (clientclass->m_ClassID == classid::CCSPlayer && variables::debug::main1) {
			//crashhandler.setDebug("ESP_ENTITY_IS_CS_TRUE");
			cBasePlayer* player = (cBasePlayer*)entity;
			if (Functions::is_bad_ptr(player)) continue;
			//crashhandler.setDebug("ESP_ENTITY_VALIDHP");
			if (player->m_iHealth() <= 0) continue;
			//crashhandler.setDebug("ESP_ENTITY_DORM");
			if (player->nDormant()) continue;

			//crashhandler.setDebug("ESP_MAIN5");
			if (variables::debug::main5) {
				bool isSameTeam = player->sameTeam(localBaseP);
				if (isSameTeam && variables::esp::team::enabled && variables::debug::main6) {
					//crashhandler.setDebug("ESP_LOOP_TEAM");
					team((cCSPlayer*)player, local);
				}
				if (!isSameTeam && variables::esp::enemies::enabled && variables::debug::main18) {
					//crashhandler.setDebug("ESP_LOOP_ENEMIES");
					enemies((cCSPlayer*)player, local);
				}
			}

		}
		/*else if (clientclass->m_ClassID == classid::CC4 && variables::debug::main19) {

			//crashhandler.setDebug("ESP_C4_1");
			CCSBomb* bomb = (CCSBomb*)entity;
			if (!Functions::is_bad_ptr(bomb)) {
				//crashhandler.setDebug("ESP_C4_2");
				if (entity->m_vecOrigin() != Vector{ 0,0,0 }) {
					Box c4_box;
					//crashhandler.setDebug("ESP_C4_3");
					if (!findBounds(true, c4_box, entity, 72, 3.5)) continue;
					if (variables::debug::main20) {
						//crashhandler.setDebug("ESP_C4_4");
						if (variables::esp::C4::name > 0)
							c4_box.AddText(variables::esp::C4::name, 0, xorStr("C4"), color(255, 255, 255, 255));
						//crashhandler.setDebug("ESP_C4_5");
						c4_box.Draw(variables::esp::C4::box, variables::esp::C4::boxOutline, color(255, 255, 255, 255), 1, 1, 0, 0);
						//crashhandler.setDebug("ESP_C4_6");
					}
				}
			}

		}*/
		else if (clientclass->m_ClassID == classid::CPlantedC4 && variables::debug::main21) {

			if (variables::debug::main6) {
				//crashhandler.setDebug("ESP_C4P_1");
				CCSBomb* bomb = (CCSBomb*)entity;
				if (!Functions::is_bad_ptr(bomb)) {
					//crashhandler.setDebug("ESP_C4P_2");
					if (variables::debug::main22) {
						if (variables::esp::other::bombHealth)
							bombDamage(localBaseP, bomb);
						//crashhandler.setDebug("ESP_C4P_3");
						float Time = roundf(max(bomb->m_flC4Blow() - interfaceManager::iglobal->curtime, 0) * 100.0f) / 100.f;
						int g = Time * 6.375; int r = 255 - g;
						color m_cTimeColor = color(r, g, 0, 255);
						char buffer[64];
						sprintf_s(buffer, xorStr("%3.0f"), Time);
						//crashhandler.setDebug("ESP_C4P_4");
						if (variables::debug::main23) {
							Box c4_box;
							//crashhandler.setDebug("ESP_C4P_5");
							if (!findBounds(true, c4_box, entity, 72, 3.5)) continue;
							if (variables::esp::C4::name > 0)
								c4_box.AddText(variables::esp::C4::name, 0, xorStr("C4 - ") + (std::string)buffer, m_cTimeColor);
							//crashhandler.setDebug("ESP_C4P_6");
							c4_box.Draw(variables::esp::C4::box, variables::esp::C4::boxOutline, m_cTimeColor, 1, 1, 0, 0);
							//crashhandler.setDebug("ESP_C4P_7");
						}
						if (variables::debug::main24) {
							c4Infomation(bomb, Time, buffer);
							//crashhandler.setDebug("ESP_C4P_8");
						}
					}

				}
			}
		}
		else if (variables::esp::weapons::enabled || variables::esp::grenades::enabled) {

			std::string networkName = clientclass->m_pNetworkName;
			if (strstr(networkName.c_str(), xorStr("CWeapon")) ||
				strstr(networkName.c_str(), xorStr("CDEagle")) ||
				strstr(networkName.c_str(), xorStr("CAK47"))) {
				if (variables::esp::weapons::enabled) {
					if (Functions::is_bad_ptr(entity->ownerEntity())) {
						std::string name = Functions::gunNameReadable(networkName);
						if (name != xorStr("")) {
							Box gun_box;
							if (!findBounds(true, gun_box, entity, 20, 2)) continue;
							if (variables::esp::weapons::name > 0)
								gun_box.AddText(variables::esp::weapons::name, 0, name, color(255, 255, 255, 255));
							gun_box.Draw(variables::esp::weapons::box, variables::esp::weapons::boxOutline, color(255, 255, 255, 255), 1, 1, 0, 0);
						}
					}
				}
			}
			else if ((strstr(networkName.c_str(), xorStr("Grenade")) ||
				strstr(networkName.c_str(), xorStr("CFlashbang"))) &&
				!strstr(networkName.c_str(), xorStr("Projectile"))) {
				if (variables::esp::grenades::enabled && variables::esp::grenades::dropped) {
					// Dropped grenades
					std::string name = Functions::droppedGrenadeToName(networkName);
					if (name != xorStr("")) {
						Box dropped_box;
						if (!findBounds(true, dropped_box, entity, 20, 2)) continue;
						if (variables::esp::grenades::name > 0)
							dropped_box.AddText(variables::esp::grenades::name, 0, name, color(255, 255, 255, 255));
						dropped_box.Draw(variables::esp::grenades::box, variables::esp::grenades::boxOutline, color(255, 255, 255, 255), 1, 1, 0, 0);
					}
				}
			}
			else if (strstr(networkName.c_str(), xorStr("Projectile"))) {
				// Thrown grenades
			
				if (variables::esp::grenades::enabled && variables::esp::grenades::thrown) {
					// Dropped grenades
					std::string name = Functions::thrownGrenadeToName(entity, networkName);
					if (name != "") {
						Box thrown_box;
						if (!findBounds(true, thrown_box, entity, 20, 2)) continue;
						if (variables::esp::grenades::name > 0)
							thrown_box.AddText(variables::esp::grenades::name, 0, name, color(255, 255, 255, 255));
						thrown_box.Draw(variables::esp::grenades::box, variables::esp::grenades::boxOutline, color(255, 255, 255, 255), 1, 1, 0, 0);
					}
				}
			}
		}
	}
	crashhandler.setDebug("ESP_CROSSHAIRS");
	if (variables::esp::other::crosshairs > 0)
		crosshair((cBasePlayer*)local);
	crashhandler.setDebug("ESP_MAIN_FINAL");
}
color espFeature::grenadeToColor(std::string model)
{
	std::string name = xorStr("");
	if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_smokegrenade_thrown.mdl"))) {
		return color(130, 130, 130, 255);
	}
	else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_flashbang_dropped.mdl"))) {
		return color(255, 255, 255, 255);
		
	}
	else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_fraggrenade_dropped.mdl"))) {
		return color(255, 0, 0, 255);
	}
	else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_decoy_dropped.mdl"))) {
		return color(0, 255, 0, 255);
	}
	else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_incendiarygrenade_dropped.mdl")) || strstr(model.c_str(), xorStr("models/Weapons/w_eq_molotov_dropped.mdl"))) {
		return color(255, 127, 39, 255);
	}
	return color(0, 0, 0, 0);;
}
void espFeature::bombDamage(cBasePlayer* local, CCSBomb* bomb) {
	if (!bomb)return;
	if (!local) return;
	if (local->m_iHealth() <= 0) return;
	cBasePlayer* bombPlayer = (cBasePlayer*)bomb;
	cCSPlayer* csPlayer = (cCSPlayer*)local;


	float damagePercent = 1.0f;
	float defaultDamage = 500.f;
    float flBombRange = defaultDamage * 3.5f;
	float flDistanceToLocalPlayer = Vector(bombPlayer->m_vecOrigin().x - local->m_vecOrigin().x, bombPlayer->m_vecOrigin().y - local->m_vecOrigin().y,bombPlayer->m_vecOrigin().z - local->m_vecOrigin().z).Length();// ((c4bomb origin + viewoffset) - (localplayer origin + viewoffset))
	auto fSigma = flBombRange / 3.0f;
	auto fGaussianFalloff = exp(-flDistanceToLocalPlayer * flDistanceToLocalPlayer / (2.0f * fSigma * fSigma));
	auto flAdjustedDamage = defaultDamage * fGaussianFalloff * damagePercent;
	float drawDamage = flAdjustedDamage;
	if (csPlayer->m_ArmorValue() > 0) {
		float flArmorRatio = 0.5f;
		float flArmorBonus = 0.5f;
		if (csPlayer->m_ArmorValue() > 0) {
			float flNew = flAdjustedDamage * flArmorRatio;
			float flArmor = (flAdjustedDamage - flNew) * flArmorBonus;

			if (flArmor > static_cast<float>(csPlayer->m_ArmorValue())) {
				flArmor = static_cast<float>(csPlayer->m_ArmorValue()) * (1.f / flArmorBonus);
				flNew = drawDamage - flArmor;
			}
			drawDamage = flNew;
		}
	}
	int yPosition = (0.9166 * Game::m_iHeight);
	int hPosition = (0.02314 *Game::m_iHeight);
	int wPosition = (0.1041 * Game::m_iWidth);
	paint->rectangle(0, yPosition, wPosition, hPosition, color(125, 125, 125, 120));
	paint->outline(0, yPosition, wPosition, hPosition, color(125, 125, 125, 180));
	float ticksToExplode = roundf(max(bomb->m_flC4Blow() - interfaceManager::iglobal->curtime, 0) * 100.0f) / 100.f;
	std::string healthLeft = "Health Remaining: " + std::to_string(max((int)local->m_iHealth() - drawDamage, 0));
	std::string timeTilExplosion = "Time Til Explosion: " + std::to_string(roundf(max(bomb->m_flC4Blow() - interfaceManager::iglobal->curtime, 0) * 100.0f) / 100.f);
	paint->text(3, yPosition + (hPosition / 2) - (paint->textSize(healthLeft.c_str(), Glyphs::feature_esp).bottom / 2), healthLeft.c_str(), Glyphs::feature_esp, Anchor::LeftCenter, (drawDamage > local->m_iHealth()) ? color(255, 50, 50, 255) : color(225, 225, 225, 255));
	int g = ticksToExplode * 6.375; int r = 255 - g;
	color TimeColor = color(r, g, 0, 255);
	paint->text(3, yPosition + (hPosition / 2) + (paint->textSize(timeTilExplosion.c_str(), Glyphs::feature_esp).bottom / 2), timeTilExplosion.c_str(), Glyphs::feature_esp, Anchor::LeftCenter, TimeColor);

}

void espFeature::c4Infomation(CCSBomb* c4, int time, const char* time_text)
{
	int g = time * 6.375; int r = 255 - g;
	color TimeColor = color(r, g, 0, 255);
	float m_iBarWidth = Game::m_iWidth / 3;
	if (variables::esp::C4::detonationInfo && time > 0) {
		float m_flC4Width = (((double)time / 40.f) * ((double)m_iBarWidth)) - 2;
		paint->rectangle(m_iBarWidth, 200, m_iBarWidth, 12, color(240, 240, 240, 255));
		paint->rectangle(m_iBarWidth + 2, 202, m_flC4Width, 8,  TimeColor);
		paint->text(m_iBarWidth + (m_iBarWidth / 2), 194, time_text, Glyphs::feature_esp,  Anchor::Center, TimeColor);
	}
	if (!Functions::is_bad_ptr(c4->m_hBombDefuser()) && variables::esp::C4::defuseInfo) {
		cCSPlayer* m_BombDefuser = (cCSPlayer*)interfaceManager::ientitylist->getClientEntityFromHandle(c4->m_hBombDefuser());
		if (!Functions::is_bad_ptr(m_BombDefuser)) {
			float maxdefuse = m_BombDefuser->m_bHasDefuser() ? 5.0 : 10.0;
			float DefuseTime = roundf(max(c4->m_flDefuseCountDown() - interfaceManager::iglobal->curtime, 0) * 100) / 100;
			char defbuffer[64];
			sprintf_s(defbuffer, "%3.0f", DefuseTime);
			float m_flDefusebarWidth = (((double)DefuseTime / maxdefuse) * ((double)m_iBarWidth)) - 2;
			paint->rectangle(m_iBarWidth, 250, m_iBarWidth, 12, color(240, 240, 240, 255));
			paint->rectangle(m_iBarWidth + 2, 252, m_flDefusebarWidth, 8, color(17, 153, 237, 255));
			paint->text(m_iBarWidth + (m_iBarWidth / 2), 244, defbuffer, Glyphs::feature_esp,  Anchor::Center, color(100, 100, 255, 255));
		}
	}
}
void playerRank(cBasePlayer* player) {

}
bool espFeature::findBounds(bool D3D, Box& box, cBaseEntity* entity, int hz, float divide)
{
	int new_x = 0, new_y = 0, new_w = 0, new_h = 0;
	if (D3D) {
		Vector flb, brt, blb, frt, frb, brb, blt, flt;
		Vector min = entity->m_vecMins() + entity->m_vecOrigin();
		Vector max = entity->m_vecMaxs() + entity->m_vecOrigin();
		Vector points[] = { Vector(min.x, min.y, min.z),
			Vector(min.x, max.y, min.z),
			Vector(max.x, max.y, min.z),
			Vector(max.x, min.y, min.z),
			Vector(max.x, max.y, max.z),
			Vector(min.x, max.y, max.z),
			Vector(min.x, min.y, max.z),
			Vector(max.x, min.y, max.z) };
		if (!Functions::worldToScreen(points[3], flb) || !Functions::worldToScreen(points[5], brt)
			|| !Functions::worldToScreen(points[0], blb) || !Functions::worldToScreen(points[4], frt)
			|| !Functions::worldToScreen(points[2], frb) || !Functions::worldToScreen(points[1], brb)
			|| !Functions::worldToScreen(points[6], blt) || !Functions::worldToScreen(points[7], flt))
			return false;
		Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
		box.updatePoints(arr);
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
		new_x = X; new_y = Y; new_w = XW - X; new_h = YH - Y;
	}
	else {
		Vector bottom = entity->m_vecOrigin(); Vector top = {bottom.x, bottom.y, bottom.z + hz};
		Vector bottomScreen;                   Vector topScreen;
		if (!Functions::worldToScreen(bottom, bottomScreen) || !Functions::worldToScreen(top, topScreen))
			return false;
		new_w = ((bottomScreen.y - topScreen.y) / divide) * 2.f;
		new_x = (float)topScreen.x - (new_w / 2); 
		new_y = topScreen.y - ((bottomScreen.y - topScreen.y) / 10);
		new_h = (bottomScreen.y - topScreen.y);
	}
	box.UpdatePosition(new_x, new_y, new_w, new_h);
	return true;
}
std::string espFeature::money(cCSPlayer* entity)
{
	return xorStr("$") + std::to_string(entity->m_iAccount());
}
std::string espFeature::ammunition(cCSPlayer* entity) {
	auto weapon = entity->m_hActiveWeapon();
	if (!Functions::is_bad_ptr(weapon)) {
		return xorStr("(") + std::to_string(Functions::clip(weapon->m_iClip1(), 0, 150)) + xorStr("/") + std::to_string(Functions::clip(weapon->m_iPrimaryReserveAmmoCount(), 0, 150)) + xorStr(")");

	}
	return "";
}
void espFeature::drawHitboxes(cCSPlayer* player, cBaseEntity* local) {
	matrix3x4_t matrix[128];
	
	if (!player->SetupBones(matrix, 128, 0x00000100, interfaceManager::iglobal->curtime))
		return;

	studiohdr_t* hdr = interfaceManager::imodelinfo->GetStudiomodel(player->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

	for (int i = 0; i < set->numhitboxes; i++)
	{
		mstudiobbox_t* hitbox = set->GetHitbox(i);

		if (!hitbox)
			continue;

		Vector vMin, vMax;
		Functions::VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
		Functions::VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
		//interfaceManager::idebug->AddCapsuleOverlay(vMin, vMax, hitbox->m_flRadius /*box + 0x30*/, 255, 255, 0, 255, 1);
	}
}
void espFeature::skeleton(cCSPlayer* entity, color colorsz) {
	const model_t* model = entity->GetModel();
	if (!model) return;
	studiohdr_t* studiomodel = interfaceManager::imodelinfo->GetStudiomodel(model);
	if (!studiomodel) return;
	for (int j = 0; j < studiomodel->numbones; j++) {
		mstudiobone_t* bone = studiomodel->GetBone(j);
		if (bone && (bone->flags & BONE_USED_BY_HITBOX) && bone->parent != -1) {
		
			Vector child = entity->m_vecBone(j); Vector childscreen;

			Vector parent = entity->m_vecBone(bone->parent); Vector parentscreen;
			if (child == Vector(0, 0, 0)) continue;
			if (parent == Vector(0, 0, 0)) continue;
			if (!Functions::worldToScreen(child, childscreen)) continue;
			if (!Functions::worldToScreen(parent, parentscreen)) continue;
			paint->line(childscreen.x, childscreen.y, parentscreen.x, parentscreen.y, colorsz);
		}
	}
	/*std::vector<std::vector<int>> hitboxPositions = { 
		{0, 1, 6, 5, 4, 3, 2, 8, 10, 12}, {14, 17, 6, 15, 13},{11, 9, 7, 2} };
	for (int c = 0; c < hitboxPositions.size(); c++) {
		std::vector<int> positions = hitboxPositions.at(c);
		for (int b = 0; b < positions.size() - 1; b++) {
			Vector current = entity->hitbox(positions.at(b)); Vector current_world;
			Vector future = entity->hitbox(positions.at(b + 1)); Vector future_world;
			if (Functions::worldToScreen(current, current_world) && Functions::worldToScreen(future, future_world)) {
				paint->line(current_world.x, current_world.y, future_world.x, future_world.y, colorsz);
			}
		}
		
	}*/
}
void espFeature::drawBacktrack(cBasePlayer* player) {
	if (!edgeaim.aimbot.Backtrack) return;
	if (player != edgeaim.aimbot.pBestBacktrTarget) return;
	int arraySize = (sizeof(edgeaim.aimbot.headPositions) / sizeof(edgeaim.aimbot.headPositions[0]));
	if (arraySize <= 0) return;
	for (int i = 0; i < edgeaim.aimbot.BacktrackTicks; i += 2) {
		if (i >= arraySize) continue;
		aimbotFeature::backtrackData a = edgeaim.aimbot.headPositions[player->m_iIndex()][i];
		if (a.hitboxPos == NULL) continue;
		if (!a.newMatrix) continue;
		int r = (255.f / edgeaim.aimbot.BacktrackTicks) * i;
		int g = 255 - r;
		Vector m_vecScreen;
		if (Functions::worldToScreen(a.hitboxPos, m_vecScreen)) {
			paint->rectangle(m_vecScreen.x, m_vecScreen.y, 3, 3, color(r, g, 0, 255));
		}
	}
	
}
void espFeature::tracelines(cCSPlayer* entity, color c) {
	cBaseCombatWeapon* m_EntityWeapon = entity->m_hActiveWeapon();
	if (Functions::is_bad_ptr(m_EntityWeapon)) return;
	QAngle m_qViewAngle = entity->m_angEyeAngles();
	Vector m_vecViewAngle = Functions::AngleToVector(m_qViewAngle);
	m_vecViewAngle *= 250;
	Vector m_vecOrigin = entity->m_vecEye();
	Vector endPoint, startPoint;
	bool WorldToScreenEndPos = Functions::worldToScreenNoScreenCut(m_vecOrigin + m_vecViewAngle, endPoint);
	bool WorldToScreenStartPos = Functions::worldToScreenNoScreenCut(m_vecOrigin, startPoint);
	if ((endPoint.x > 0 && endPoint.x < Game::m_iWidth) && (endPoint.y > 0 && endPoint.y < Game::m_iHeight) ||
		((startPoint.x > 0 && startPoint.x < Game::m_iWidth) && (startPoint.y > 0 && startPoint.y < Game::m_iHeight))) {
		paint->line(endPoint.x, endPoint.y, startPoint.x, startPoint.y, c);
		paint->circle(endPoint.x, endPoint.y, 4, c);
	}
}
std::string espFeature::distance(cCSPlayer* entity, cCSPlayer* local) {
	if (!Functions::is_bad_ptr(entity) && !Functions::is_bad_ptr(local)) {
		Vector delta = entity->m_vecOrigin() - local->m_vecOrigin();
		return xorStr("[") + std::to_string((int)(delta.Length() / 100.f)) + xorStr("m]");
	}
	return "";
}
std::string espFeature::weapon(cCSPlayer* entity) {
	auto weapon = entity->m_hActiveWeapon();
	if (!Functions::is_bad_ptr(weapon)) {
		ItemDefinitionIndex id = weapon->m_iItemDefinitionIndex();
		std::string Name = Functions::IDString(id);
		return Name;
		
	}
	return "";
}
std::string  espFeature::reloadWarning(cBasePlayer* player) {
	auto weapon = player->m_hActiveWeapon();
	if (!Functions::is_bad_ptr(weapon)) {
		if (weapon->m_iPrimaryReserveAmmoCount() != 0 && /*weapon->m_bInReload()*/ weapon->m_iClip1() == 0)	
			return xorStr("*reloading*");

	}
	return "";
}
std::string  espFeature::scopedWarning(cCSPlayer* player) {
	if (player->m_bIsScoped())
		return xorStr("*scoped*");

	
	return "";
}
std::string  espFeature::defuseWarning(cCSPlayer* player) {
	if (player->m_bIsDefusing())
		return xorStr("*defusing*");


	return "";
}
std::string  espFeature::hostageWarning(cCSPlayer* player) {
	if (player->m_bIsGrabbingHostage())
		return xorStr("*taking hostage*");


	return "";
}
//m_bHasHelmet
std::string  espFeature::helmetESP(cCSPlayer* player) {
	if (player->m_bHasHelmet())
		return xorStr("H");


	return "";
}
std::string  espFeature::healthValueESP(cBasePlayer* player) {
	return std::to_string(player->m_iHealth());
	return "";
}
color espFeature::armorCol(cCSPlayer* player) {
	int max = 100;
	int value = player->m_ArmorValue();
	float percentage = Functions::clip(value / max, 0, 1);
	float rg = 150 + (50 * percentage);
	return color(rg, rg, 255, 255);
}
color espFeature::healthCol(cBasePlayer* player) {
	int max = player->m_iMaxHealth();
	int value = player->m_iHealth();
	float percentage = Functions::clip(value / max, 0, 1);
	float r = (1 - percentage) * 255;
	float g = (percentage * 255);
	return color(r, g, 0, 255);
}
std::string  espFeature::armourValueESP(cCSPlayer* player) {
	return std::to_string(player->m_ArmorValue());
	return "";
}
std::string espFeature::name(int i) {
	player_info_t info;
	if (Functions::is_bad_ptr(interfaceManager::iengine)) return "";
	interfaceManager::iengine->GetPlayerInfo(i, &info);
	return info.name;
}
void espFeature::radar(cCSPlayer* player) {
	if (!player->m_bSpotted())
		player->m_bSpotted() = true;
}

void espFeature::crosshair(cBasePlayer* local) {

	int x = (int)(Game::m_iWidth / 2);
	int y = (int)(Game::m_iHeight / 2);
	if (variables::esp::other::crosshairs == 1) {
		paint->rectangle(x - 10, y - 1, 20, 1, color(0, 255, 0, 255));
		paint->rectangle(x - 1, y - 10, 1, 20, color(0, 255, 0, 255));
	}
	else if (variables::esp::other::crosshairs == 2) {
		paint->line(x - 5, y + 5, x + 5, y - 5, color(0, 255, 0, 255));
		paint->line(x + 5, y + 5, x - 5, y - 5, color(0, 255, 0, 255));
	}
	else if (variables::esp::other::crosshairs == 3) {
		paint->rectangle(x - 5, y, 10, 1, color(0, 255, 0, 255));
	}
}
void espFeature::healthBar(int hb, Box box, cBasePlayer* entity, color healthcolor)
{
	//Left
	double Health = entity->m_iHealth();
	double MaxHealth = entity->m_iMaxHealth();
	int space = 1;
	if (hb == 1) {
		int healthbarh = (((box.h + 1) / MaxHealth) * Health);
		int healthadd = (box.h + 1) - healthbarh;
		paint->rectangle(box.x - 5 - space, box.y - 1, 3, box.h + 3, color(0, 0, 0, 255));
		paint->rectangle(box.x - 4 - space, box.y + healthadd, 1, healthbarh, healthcolor);
	}
	else if (hb == 2) {
		int healthbarh = (((box.h + 1) / MaxHealth) * Health);
		int healthadd = (box.h + 1) - healthbarh;
		paint->rectangle(box.x + box.w + 3 + space, box.y - 1, 3, box.h + 3, color(0, 0, 0, 255));
		paint->rectangle(box.x + box.w + 4 + space, box.y + healthadd, 1, healthbarh, healthcolor);
	}
	else if (hb == 3) {
		int healthbarw = (((box.w + 1) / MaxHealth) * Health);
		paint->rectangle(box.x - 1, box.y - 5 - space, box.w + 3, 3, color(0, 0, 0, 255));
		paint->rectangle(box.x, box.y - 4 - space, healthbarw, 1, healthcolor);
	}
	else if (hb == 4) {
		int healthbarw = (((box.w + 1) / MaxHealth) * Health);
		paint->rectangle(box.x - 1, box.y + box.h + 3 + space, box.w + 3, 3, color(0, 0, 0, 255));
		paint->rectangle(box.x, box.y + box.h + 4 + space, healthbarw, 1, healthcolor);
	}
}
void espFeature::playerColor(bool visible, cBasePlayer* entity, cBasePlayer* local, color& boxcolor, color& namecolor, color& weaponcolor, color& healthcolor, color& moneycolor, color& ammunitioncolor, color& distancecolor, color& barrelcolor, color& skeletoncolor, color& reloadWarningcolor, color& scopedWarningcolor, color& defuseWarningcolor, color& hostageWarningcolor, color& helmetESPcolor)
{
	if (entity == local) {
		boxcolor = namecolor = weaponcolor = healthcolor = moneycolor = ammunitioncolor = color(255, 255, 255, 255);
	}

	bool isSameTeam = entity->sameTeam(local);
	if (visible) {
		if (isSameTeam) {
			boxcolor = variables::esp::team::boxVisible;
			namecolor = variables::esp::team::nameVisible;
			weaponcolor = variables::esp::team::weaponVisible;
			healthcolor = variables::esp::team::healthVisible;
			moneycolor = variables::esp::team::moneyVisible;
			ammunitioncolor = variables::esp::team::ammunitionVisible;
			distancecolor = variables::esp::team::distanceVisible;
			barrelcolor = variables::esp::team::barrelVisible;
			skeletoncolor = variables::esp::team::skeletonVisible;
			reloadWarningcolor = variables::esp::team::reloadWarningVisible;
			scopedWarningcolor = variables::esp::team::scopedWarningVisible;
			defuseWarningcolor = variables::esp::team::defuseWarningVisible;
			hostageWarningcolor = variables::esp::team::hostageWarningVisible;
			helmetESPcolor = variables::esp::team::helmetESPVisible;
		}
		else {
			boxcolor = variables::esp::enemies::boxVisible;
			namecolor = variables::esp::enemies::nameVisible;
			weaponcolor = variables::esp::enemies::weaponVisible;
			healthcolor = variables::esp::enemies::healthVisible;
			moneycolor = variables::esp::enemies::moneyVisible;
			ammunitioncolor = variables::esp::enemies::ammunitionVisible;
			distancecolor = variables::esp::enemies::distanceVisible;
			barrelcolor = variables::esp::enemies::barrelVisible;
			skeletoncolor = variables::esp::enemies::skeletonVisible;

			reloadWarningcolor = variables::esp::enemies::reloadWarningVisible;
			scopedWarningcolor = variables::esp::enemies::scopedWarningVisible;
			defuseWarningcolor = variables::esp::enemies::defuseWarningVisible;
			hostageWarningcolor = variables::esp::enemies::hostageWarningVisible;
			helmetESPcolor = variables::esp::enemies::helmetESPVisible;
		}
	}
	else {
		if (isSameTeam) {
			boxcolor = variables::esp::team::boxInvisible;
			namecolor = variables::esp::team::nameInvisible;
			weaponcolor = variables::esp::team::weaponInvisible;
			healthcolor = variables::esp::team::healthInvisible;
			moneycolor = variables::esp::team::moneyInvisible;
			ammunitioncolor = variables::esp::team::ammunitionInvisible;
			distancecolor = variables::esp::team::distanceInvisible;
			barrelcolor = variables::esp::team::barrelInvisible;
			skeletoncolor = variables::esp::team::skeletonInvisible;

			reloadWarningcolor = variables::esp::team::reloadWarningInvisible;
			scopedWarningcolor = variables::esp::team::scopedWarningInvisible;
			defuseWarningcolor = variables::esp::team::defuseWarningInvisible;
			hostageWarningcolor = variables::esp::team::hostageWarningInvisible;
			helmetESPcolor = variables::esp::team::helmetESPInvisible;
		}
		else {
			boxcolor = variables::esp::enemies::boxInvisible;
			namecolor = variables::esp::enemies::nameInvisible;
			weaponcolor = variables::esp::enemies::weaponInvisible;
			healthcolor = variables::esp::enemies::healthInvisible;
			moneycolor = variables::esp::enemies::moneyInvisible;
			ammunitioncolor = variables::esp::enemies::ammunitionInvisible;
			distancecolor = variables::esp::enemies::distanceInvisible;
			barrelcolor = variables::esp::enemies::barrelInvisible;
			skeletoncolor = variables::esp::enemies::skeletonInvisible;
			reloadWarningcolor = variables::esp::enemies::reloadWarningInvisible;
			scopedWarningcolor = variables::esp::enemies::scopedWarningInvisible;
			defuseWarningcolor = variables::esp::enemies::defuseWarningInvisible;
			hostageWarningcolor = variables::esp::enemies::hostageWarningInvisible;
			helmetESPcolor = variables::esp::enemies::helmetESPInvisible;

		}
	}
}
void espFeature::lines(cBasePlayer* player, Box box) {
	if (!player) return;
	if (player->m_iHealth() <= 0) return;
	float g = (player->m_iHealth() / 100) * 255;
	float r = 255 - g;
	float a = Vector2D(box.x + (box.w / 2), box.y + box.h).DistTo(Vector2D(Game::m_iWidth / 2, Game::m_iHeight));
	float sizeRelative = Functions::clip(1 - (a / Game::m_iWidth), 0.f, 1.f);;
	float alpha = Functions::clip((float)(120 * sizeRelative), 20.f, 120.f);
	paint->line(box.x + (box.w / 2), box.y + box.h, Game::m_iWidth / 2, Game::m_iHeight, color(r, g, 0, alpha));
	
}
void espFeature::enemies(cCSPlayer* player, cBaseEntity* local) {
	Box entity_box;
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_1");
	if (!findBounds(variables::esp::enemies::box == 4, entity_box, player, 72, 3.5)) return;
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_2");
	if (!variables::debug::main7) return;
	bool Visible = local->canSee(player);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_3");
	if (!variables::debug::main8) return;
	if (!Visible && variables::esp::enemies::visibleOnly) return;
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_4");
	color boxcolor, namecolor, weaponcolor, healthcolor, moneycolor, ammunitioncolor, distancecolor, barrelcolor, skeletoncolor, reloadWarningcolor, scopedWarningcolor, defuseWarningcolor, hostageWarningcolor, helmetESPcolor;;
	//crashhandler.setDebug("ESP_LOOP_TEAM_5");
	playerColor(Visible, (cBasePlayer*)player, (cBasePlayer*)local, boxcolor, namecolor, weaponcolor, healthcolor, moneycolor, ammunitioncolor, distancecolor, barrelcolor, skeletoncolor, reloadWarningcolor, scopedWarningcolor, defuseWarningcolor, hostageWarningcolor, helmetESPcolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_5");
	if (!variables::debug::main9) return;
	
	if (variables::esp::enemies::healthbar)
		healthBar(variables::esp::enemies::healthbar, entity_box, (cBasePlayer*)player, color(0, 255, 0, 255));
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_6");
	if (!variables::debug::main10) return;

	if (variables::esp::enemies::name)
		entity_box.AddText(variables::esp::enemies::name, variables::esp::enemies::healthbar, name(player->m_iIndex()), namecolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_7");
	if (!variables::debug::main11) return;
	if (variables::esp::enemies::weapon)
		entity_box.AddText(variables::esp::enemies::weapon, variables::esp::enemies::healthbar, weapon(player), weaponcolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_8");
	if (!variables::debug::main12) return;
	if (variables::esp::enemies::money)
		entity_box.AddText(variables::esp::enemies::money, variables::esp::enemies::healthbar, money(player), moneycolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_9");
	if (!variables::debug::main13) return;
	if (variables::esp::enemies::ammunition)
		entity_box.AddText(variables::esp::enemies::ammunition, variables::esp::enemies::healthbar, ammunition(player), ammunitioncolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_10");
	
	if (variables::esp::enemies::lines)
		lines((cBasePlayer*)player, entity_box);
	if (variables::esp::enemies::reloadWarning)
		entity_box.AddText(variables::esp::enemies::reloadWarning, variables::esp::enemies::healthbar, reloadWarning((cBasePlayer*)player), reloadWarningcolor);

	if (variables::esp::enemies::scopedWarning)
		entity_box.AddText(variables::esp::enemies::scopedWarning, variables::esp::enemies::healthbar, scopedWarning(player), scopedWarningcolor);
	drawHitboxes(player, local);

	if (variables::esp::enemies::defuseWarning)
		entity_box.AddText(variables::esp::enemies::defuseWarning, variables::esp::enemies::healthbar, defuseWarning(player), defuseWarningcolor);

	if (variables::esp::enemies::hostageWarning)
		entity_box.AddText(variables::esp::enemies::hostageWarning, variables::esp::enemies::healthbar, hostageWarning(player), hostageWarningcolor);

	if (variables::esp::enemies::helmetESP)
		entity_box.AddText(variables::esp::enemies::helmetESP, variables::esp::enemies::healthbar, helmetESP(player), helmetESPcolor);

	if (variables::esp::enemies::healthvalue)
		entity_box.AddText(variables::esp::enemies::healthvalue, variables::esp::enemies::healthbar, healthValueESP((cBasePlayer*)player), healthCol((cBasePlayer*)player));

	if (variables::esp::enemies::armorvalue)
		entity_box.AddText(variables::esp::enemies::armorvalue, variables::esp::enemies::healthbar, armourValueESP(player), armorCol(player));



	if (!variables::debug::main14) return;
	if (variables::esp::enemies::radar)
		radar(player);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_11");
	if (!variables::debug::main15) return;
	if (variables::esp::enemies::skeleton)
		skeleton(player, skeletoncolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_12");
	if (!variables::debug::main16) return;
	if (variables::esp::enemies::barrel)
		tracelines(player, barrelcolor);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_13");
	if (!variables::debug::main17) return;
	if (variables::esp::enemies::distance)
		entity_box.AddText(variables::esp::enemies::distance, variables::esp::enemies::healthbar, distance(player, (cCSPlayer*)local), distancecolor);
	if (variables::esp::enemies::backtrack)
		drawBacktrack((cBasePlayer*)player);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_14");
	entity_box.Draw(variables::esp::enemies::box, variables::esp::enemies::boxOutline, boxcolor, variables::esp::enemies::healthbar == 3 ? 5 : 1, variables::esp::enemies::healthbar == 4 ? 5 : 1, variables::esp::enemies::healthbar == 1 ? 5 : 0, variables::esp::enemies::healthbar == 2 ? 5 : 0);
	//crashhandler.setDebug("ESP_LOOP_ENEMIES_15");

}
void espFeature::testSizeESP(cBasePlayer* player) {
	Vector head = player->hitbox(0);
	float rot = (Game::localRotation * 3.1415) / 180.0f;
	float pixelRadius = 25;
	Vector sidePos = { head.x + pixelRadius * cos(rot + 90),
					   head.y + pixelRadius * sin(rot + 90),
					   head.z };
	Vector sideSecondPos = { head.x + pixelRadius * cos(rot - 90),
					   head.y + pixelRadius * sin(rot - 90),
					   head.z };
	Vector sidePosWorld, sideSecondPosWorld;
	if (Functions::worldToScreen(sidePos, sidePosWorld))
		paint->rectangle(sidePosWorld.x, sidePosWorld.y, 3, 3, color(255, 0, 0, 255));
	if (Functions::worldToScreen(sideSecondPos, sideSecondPosWorld))
		paint->rectangle(sideSecondPosWorld.x, sideSecondPosWorld.y, 3, 3, color(0, 255, 0, 255));
}
void espFeature::team(cCSPlayer* player, cBaseEntity* local) {
	Box entity_box;
	//crashhandler.setDebug("ESP_LOOP_TEAM_1");
	if (!findBounds(variables::esp::team::box == 4, entity_box, player, 72, 3.5)) return;
	//crashhandler.setDebug("ESP_LOOP_TEAM_2");
	if (!variables::debug::main7) return;
	bool Visible = local->canSee(player);
	//crashhandler.setDebug("ESP_LOOP_TEAM_3");
	if (!variables::debug::main8) return;
	if (!Visible && variables::esp::team::visibleOnly) return;
	//crashhandler.setDebug("ESP_LOOP_TEAM_4");
	color boxcolor, namecolor, weaponcolor, healthcolor, moneycolor, ammunitioncolor, distancecolor, barrelcolor, skeletoncolor, reloadWarningcolor, scopedWarningcolor, defuseWarningcolor, hostageWarningcolor, helmetESPcolor;;
	//crashhandler.setDebug("ESP_LOOP_TEAM_5");
	playerColor(Visible, (cBasePlayer*)player, (cBasePlayer*)local, boxcolor, namecolor, weaponcolor, healthcolor, moneycolor, ammunitioncolor, distancecolor, barrelcolor, skeletoncolor, reloadWarningcolor, scopedWarningcolor, defuseWarningcolor, hostageWarningcolor, helmetESPcolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_6");
	if (!variables::debug::main9) return;
	
	if (variables::esp::team::healthbar)
		healthBar(variables::esp::team::healthbar, entity_box, (cBasePlayer*)player, color(0, 255, 0, 255));
	//crashhandler.setDebug("ESP_LOOP_TEAM_7");
	if (!variables::debug::main10) return;

	if (variables::esp::team::name)
		entity_box.AddText(variables::esp::team::name, variables::esp::team::healthbar, name(player->m_iIndex()), namecolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_8");
	if (!variables::debug::main11) return;
	if (variables::esp::team::weapon)
		entity_box.AddText(variables::esp::team::weapon, variables::esp::team::healthbar, weapon(player), weaponcolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_9");
	if (!variables::debug::main12) return;
	if (variables::esp::team::money)
		entity_box.AddText(variables::esp::team::money, variables::esp::team::healthbar, money(player), moneycolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_10");
	if (!variables::debug::main13) return;
	if (variables::esp::team::ammunition)
		entity_box.AddText(variables::esp::team::ammunition, variables::esp::team::healthbar, ammunition(player), ammunitioncolor);

	//
	/*
	
	*/
	if (variables::esp::team::reloadWarning)
		entity_box.AddText(variables::esp::team::reloadWarning, variables::esp::team::healthbar, reloadWarning((cBasePlayer*)player), reloadWarningcolor);

	if (variables::esp::team::scopedWarning)
		entity_box.AddText(variables::esp::team::scopedWarning, variables::esp::team::healthbar, scopedWarning(player), scopedWarningcolor);


	if (variables::esp::team::defuseWarning)
		entity_box.AddText(variables::esp::team::defuseWarning, variables::esp::team::healthbar, defuseWarning(player), defuseWarningcolor);
	
	if (variables::esp::team::hostageWarning)
		entity_box.AddText(variables::esp::team::hostageWarning, variables::esp::team::healthbar, hostageWarning(player), hostageWarningcolor);

	if (variables::esp::team::helmetESP)
		entity_box.AddText(variables::esp::team::helmetESP, variables::esp::team::healthbar, helmetESP(player), helmetESPcolor);


	if (variables::esp::team::healthvalue)
		entity_box.AddText(variables::esp::team::healthvalue, variables::esp::team::healthbar, healthValueESP((cBasePlayer*)player), healthCol((cBasePlayer*)player));

	if (variables::esp::team::armorvalue)
		entity_box.AddText(variables::esp::team::armorvalue, variables::esp::team::healthbar, armourValueESP(player), armorCol(player));

	if (variables::esp::team::lines)
		lines((cBasePlayer*)player, entity_box);
	//crashhandler.setDebug("ESP_LOOP_TEAM_11");
	if (!variables::debug::main14) return;
	if (variables::esp::team::radar)
		radar(player);
	//crashhandler.setDebug("ESP_LOOP_TEAM_12");
	if (!variables::debug::main15) return;
	if (variables::esp::team::skeleton)
		skeleton(player, skeletoncolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_13");
	if (!variables::debug::main16) return;
	if (variables::esp::team::barrel)
		tracelines(player, barrelcolor);
	//crashhandler.setDebug("ESP_LOOP_TEAM_14");
	if (!variables::debug::main17) return;
	if (variables::esp::team::distance)
		entity_box.AddText(variables::esp::team::distance, variables::esp::team::healthbar, distance(player, (cCSPlayer*)local), distancecolor);
	if (variables::esp::team::backtrack)
		drawBacktrack((cBasePlayer*)player);
	//crashhandler.setDebug("ESP_LOOP_TEAM_15");
	entity_box.Draw(variables::esp::team::box, variables::esp::team::boxOutline, boxcolor, variables::esp::team::healthbar == 3 ? 5 : 1, variables::esp::team::healthbar == 4 ? 5 : 1, variables::esp::team::healthbar == 1 ? 5 : 0, variables::esp::team::healthbar == 2 ? 5 : 0);
	//crashhandler.setDebug("ESP_LOOP_TEAM_16");



}