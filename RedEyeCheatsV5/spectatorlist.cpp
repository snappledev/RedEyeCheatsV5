#include "SpectatorList.h"
#include "variables.h"
#include "inputManager.h"
#include "interfaces.h"
#include "painting.h"
#include "crashhandler.h"
void Spectators::Draw()
{
	RECT GrabArea = { x + 22, y, 328, 27 };
	RECT ToggleArea = { x, y, 22, 27 };
	color backcolor = color(0, 0, 0, 0);;
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local) || !interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;
	player_info_t ObservingName;
	interfaceManager::iengine->GetPlayerInfo(interfaceManager::iengine->GetLocalPlayer(), &ObservingName);
	std::string ObserverInfomationName = ObservingName.name;
	int m_iYOffset = 27;
	for (int i = 0; i < interfaceManager::ientitylist->getHighestEntityIndex(); i++) {
		cBaseEntity* ent = interfaceManager::ientitylist->getClientEntity(i);
		if (Functions::is_bad_ptr(ent)) continue;
		if (ent->m_ClientClass()->m_ClassID != classid::CCSPlayer) continue;
		cBasePlayer* entity = (cBasePlayer*)ent;
		player_info_t info;
		if (!interfaceManager::iengine->GetPlayerInfo(entity->m_iIndex(), &info)) continue;
		HANDLE observing = entity->m_hObserverTarget();
		cBaseEntity* m_ObserverTarget = interfaceManager::ientitylist->getClientEntityFromHandle(observing);
		if (Functions::is_bad_ptr(m_ObserverTarget)) continue;
		if (local->m_iHealth() <= 0) {

			HANDLE local_observer = local->m_hObserverTarget();
			cBaseEntity* m_LocalObserverTarget = interfaceManager::ientitylist->getClientEntityFromHandle(local_observer);
			if (Functions::is_bad_ptr(m_LocalObserverTarget)) continue;
			if (m_ObserverTarget != m_LocalObserverTarget) continue;
			player_info_t ObservingName;
			if (interfaceManager::iengine->GetPlayerInfo(m_LocalObserverTarget->m_iIndex(), &ObservingName)) {
				ObserverInfomationName = ObservingName.name;
			}
		}
		else {
			if (m_ObserverTarget != local) continue;
			player_info_t ObservingName;
			if (interfaceManager::iengine->GetPlayerInfo(interfaceManager::iengine->GetLocalPlayer(), &ObservingName)) {
				ObserverInfomationName = ObservingName.name;
			}
		}

		player_info_t Reciever;
		if (interfaceManager::iengine->GetPlayerInfo(entity->m_iIndex(), &Reciever)) {
			if (Open) {
				RECT Name = paint->textSize(Reciever.name, Glyphs::feature_esp);
				paint->text(GrabArea.left, GrabArea.top + 13 + m_iYOffset, Reciever.name, Glyphs::feature_esp, Anchor::LeftCenter,variables::gui::colors::text);
			}

		}

		m_iYOffset += GrabArea.bottom;
	}
	color LineColor = variables::gui::colors::text;
	if (inputmanager.inArea(ToggleArea.left, ToggleArea.top, ToggleArea.right, ToggleArea.bottom))
		LineColor = Functions::coloradd(variables::gui::colors::primary, 20);
	if (Open) {
		paint->line(x + 7, y + 11, x + 12, y + 15, LineColor);
		paint->line(x + 12, y + 15, x + 16, y + 11, LineColor);
	}
	else {
		paint->line(x + 10, y + 9, x + 14, y + 13, LineColor);
		paint->line(x + 14, y + 13, x + 10, y + 18, LineColor);
	}
	std::string word = ObserverInfomationName + xorStr("'s Spectators (") + std::to_string((int)((m_iYOffset - 27) / GrabArea.bottom)) + xorStr(")");
	RECT ObserverNameArea = paint->textSize(word.c_str(), Glyphs::feature_esp);
	paint->line(GrabArea.left + ObserverNameArea.right + 10, GrabArea.top + (GrabArea.bottom / 2), GrabArea.left + ObserverNameArea.right + 10 + (GrabArea.right - (ObserverNameArea.right + 10)), GrabArea.top + (GrabArea.bottom / 2), color(240, 240, 240, 255));
	if (inputmanager.inArea(GrabArea.left, GrabArea.top, GrabArea.right, GrabArea.bottom)) {
		paint->rectangle(GrabArea.left - 22, GrabArea.top, GrabArea.right + 22, GrabArea.bottom, color(229, 243, 255, 45));
		paint->text(GrabArea.left, GrabArea.top + (GrabArea.bottom / 2) - (ObserverNameArea.bottom / 2),word.c_str(), Glyphs::feature_esp,  Anchor::TopLeft, color(variables::gui::colors::text.r() - (variables::gui::colors::primary.r() / 10), variables::gui::colors::text.g() - (variables::gui::colors::primary.g() / 10), variables::gui::colors::text.b() - (variables::gui::colors::primary.b() / 10), 255));
	}
	else {
		paint->text(GrabArea.left, GrabArea.top + (GrabArea.bottom / 2) - (ObserverNameArea.bottom / 2), word.c_str(), Glyphs::feature_esp, Anchor::TopLeft, variables::gui::colors::text);
	}
}
void Spectators::Update()
{
	RECT GrabArea = { x + 22, y, 328, 27 };
	RECT ToggleArea = { x, y, 22, 27 };
	if (inputmanager.inArea(ToggleArea.left, ToggleArea.top, ToggleArea.right, ToggleArea.bottom) && inputmanager.click(VK_LBUTTON))
		Open = !Open;
	if (inputmanager.hold(VK_LBUTTON)) {
		if (inputmanager.inArea(GrabArea.left, GrabArea.top, GrabArea.right, GrabArea.bottom))
			Holding = true;
	}
	else
		Holding = false;

	if (Holding) {
		x = inputmanager.cursor.x - rx;
		y = inputmanager.cursor.y - ry;
	}
	else {
		rx = inputmanager.cursor.x - x;
		ry = inputmanager.cursor.y - y;
	}
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + GrabArea.right > Game::m_iWidth) x = Game::m_iWidth - GrabArea.right;
	if (y + GrabArea.bottom > Game::m_iHeight) y = Game::m_iHeight - GrabArea.bottom;

}
void Spectators::loop() {
	if (variables::esp::other::spectators) {
		crashhandler.setDebug("SPEC_1");
		Update();
		Draw();
		crashhandler.setDebug("SPEC_2");
	}
}