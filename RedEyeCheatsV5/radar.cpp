#include "radar.h"
#include "painting.h"
#include "cBasePlayer.h"
#include "cCSPlayer.h"
#include "variables.h"
#include "inputManager.h"
#include "crashhandler.h"
void radarFeature::loop() {
	crashhandler.setDebug("RADAR_1");
	update();
	draw();
	crashhandler.setDebug("RADAR_2");
}
void radarFeature::update() {
	if (!variables::esp::enemies::cheatradar && !variables::esp::team::cheatradar) return;
	RECT grabArea = { x, y , w + 8, h + 24 };
	RECT radarArea = { x + 4, y + 20 , w, h };
	if (inputmanager.hold(VK_LBUTTON)) {
		if (inputmanager.inArea(grabArea.left, grabArea.top, grabArea.right, grabArea.bottom)&&
			!inputmanager.inArea(radarArea.left, radarArea.top, radarArea.right, radarArea.bottom))
			holding = true;
	}
	else
		holding = false;

	if (holding) {
		x = inputmanager.cursor.x - rx;
		y = inputmanager.cursor.y - ry;
	}
	else {
		rx = inputmanager.cursor.x - x;
		ry = inputmanager.cursor.y - y;
	}
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + grabArea.right > Game::m_iWidth) x = Game::m_iWidth - grabArea.right;
	if (y + grabArea.bottom > Game::m_iHeight) y = Game::m_iHeight - grabArea.bottom;
}
void radarFeature::draw() {
	if (!variables::esp::enemies::cheatradar && !variables::esp::team::cheatradar) return;
	if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	cCSPlayer* localcs = (cCSPlayer*)local;
	if (Functions::is_bad_ptr(local)) return;
	if (Functions::is_bad_ptr(localcs)) return;
	RECT grabArea = { x, y , w + 8, h + 24 };
	RECT radarArea = { x + 4, y + 20 , w, h };
	paint->rectangle(grabArea.left, grabArea.top, grabArea.right, grabArea.bottom, color(15, 15, 15, 255));
	paint->outline(grabArea.left, grabArea.top, grabArea.right, grabArea.bottom, color(0, 0, 0, 255));
	paint->text(grabArea.left + (grabArea.right / 2), grabArea.top + ((grabArea.bottom - h) / 2), xorStr("Radar"), Glyphs::feature_esp, Anchor::Center, color(255, 255, 255, 255));
	//INSIDE
	paint->rectangle(radarArea.left, radarArea.top, radarArea.right, radarArea.bottom, color(25, 25, 25, 255));
	paint->outline(radarArea.left, radarArea.top, radarArea.right, radarArea.bottom, color(0, 0, 0, 255));
	//LINES

	paint->line(radarArea.left + (radarArea.right / 2), radarArea.top, radarArea.left + (radarArea.right / 2), radarArea.top + radarArea.bottom, color(0, 0, 0, 255));
	paint->line(radarArea.left, radarArea.top + (radarArea.bottom / 2), radarArea.left + radarArea.right, radarArea.top + (radarArea.bottom / 2), color(0, 0, 0, 255));
	for (int i = 1; i < interfaceManager::iengine->GetMaxClients(); i++)
	{
		cBaseEntity* entity = interfaceManager::ientitylist->getClientEntity(i);
		if (Functions::is_bad_ptr(entity)) continue;
		if (entity == local) continue;
		if (entity->nDormant()) continue;
		if (entity->m_ClientClass()->m_ClassID != classid::CCSPlayer) continue;
		cBasePlayer* player = (cBasePlayer*)entity;
		if (Functions::is_bad_ptr(player)) continue;
		if (player->m_iHealth() <= 0) continue;
		bool isSameTeam = player->sameTeam(local);
		if (!isSameTeam && !variables::esp::enemies::cheatradar) continue;
		if (isSameTeam && !variables::esp::team::cheatradar) continue;

		int CenterX = radarArea.left + (radarArea.right / 2);
		int CenterY = radarArea.top + (radarArea.bottom / 2);

		float DeltaX = player->m_vecOrigin().x - local->m_vecOrigin().x;
		float DeltaY = player->m_vecOrigin().y - local->m_vecOrigin().y;
		float Yaw = (localAngle) * (3.14159265359 / 180.0);
		float MainViewAngles_CosYaw = cos(Yaw);
		float MainViewAngles_SinYaw = sin(Yaw);
		float x = DeltaY * (-MainViewAngles_CosYaw) + DeltaX * MainViewAngles_SinYaw;
		float y = DeltaX * (-MainViewAngles_CosYaw) - DeltaY * MainViewAngles_SinYaw;
		float Scale = 1347;
		if (fabs(x) > Scale || fabs(y) > Scale) {
			if (y > x) {
				if (y > -x) {
					x = Scale * x / y;
					y = Scale;
				}
				else {
					y = -Scale * y / x;
					x = -Scale;
				}
			}
			else {
				if (y > -x) {
					y = Scale * y / x;
					x = Scale;
				}
				else {
					x = -Scale * x / y;
					y = -Scale;
				}
			}
		}

		int	ScreenX = CenterX + int(x / Scale * (130));
		int ScreenY = CenterY + int(y / Scale * (130));
		if (!isSameTeam)
			paint->rectangle(ScreenX - 2, ScreenY - 2, 4, 4, color(255, 50, 50, 255));
		else
			paint->rectangle(ScreenX - 2, ScreenY - 2, 4, 4, color(50, 255, 50, 255));
		paint->outline(ScreenX - 2, ScreenY - 2, 4, 4, color(0, 0, 0, 255));

	}

}
void radarFeature::cmdUpdate(CUserCmd* c) {
	if (!variables::esp::enemies::cheatradar && !variables::esp::team::cheatradar) return;
	if (Functions::is_bad_ptr(c)) return;
	localAngle = c->viewangles.y;
	

}