#pragma once
#include <Windows.h>
#include <stdio.h>
#include "xor.h"
#include <fstream>
#include "Functions.h"
#include "interfaces.h"
class RECStatistics
{
public:
	void syncSavedStatistics() {
		if (path == "") {
			char* appdata = getenv(xorStr("APPDATA"));
			std::string dir = appdata; dir += xorStr("\\VPXA_3432\\");
			path = dir;
		}
		std::string m_sConfiguration = path + xorStr("statistics.ini");
		if (!Functions::FileExists(m_sConfiguration.c_str())) {
			std::ofstream a(m_sConfiguration);
			a.close();
			writeStatistics();
			return;
		}
		variables::misc::statistics::iKills = GetPrivateProfileInt(xorStr("statistics"), xorStr("kills"), 0, m_sConfiguration.c_str());
		variables::misc::statistics::iHeadshots = GetPrivateProfileInt(xorStr("statistics"), xorStr("headshots"), 0, m_sConfiguration.c_str());
		variables::misc::statistics::iDeaths = GetPrivateProfileInt(xorStr("statistics"), xorStr("deaths"), 0, m_sConfiguration.c_str());

	}
	void writeStatistics() {
		if (!newStatistics) return;
		std::string m_sConfiguration = path + xorStr("statistics.ini");
		WritePrivateProfileString(xorStr("statistics"), xorStr("kills"), std::to_string(variables::misc::statistics::iKills).c_str(), m_sConfiguration.c_str());
		WritePrivateProfileString(xorStr("statistics"), xorStr("headshots"), std::to_string(variables::misc::statistics::iHeadshots).c_str(), m_sConfiguration.c_str());
		WritePrivateProfileString(xorStr("statistics"), xorStr("deaths"), std::to_string(variables::misc::statistics::iDeaths).c_str(), m_sConfiguration.c_str());

		newStatistics = false;
	}
	void increaseKills() {
		newStatistics = true;
		variables::misc::statistics::iKills++;
		
	}
	void catchEvents(IGameEvent* _event) {
		if (Functions::is_bad_ptr(_event) || !interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) {
			return;
		}
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (!local) return;
		if (!Functions::is_bad_ptr(local)) {
			if (strcmp(_event->GetName(), xorStr("player_death")) == 0) {
				cBasePlayer* dead = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(_event->GetInt(xorStr("userid"))));
				cBasePlayer* attacker = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(_event->GetInt(xorStr("attacker"))));
				
				if (!Functions::is_bad_ptr(dead) && !Functions::is_bad_ptr(attacker)) {
					if (attacker == local)
						increaseKills();
					if (dead == local)
						increaseDeaths();
				}
			}
			if (strcmp(_event->GetName(), xorStr("player_hurt")) == 0) {
				cBasePlayer* hurt = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(_event->GetInt(xorStr("userid"))));
				cBasePlayer* attacker = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetPlayerForUserID(_event->GetInt(xorStr("attacker"))));
				if (!Functions::is_bad_ptr(hurt) && !Functions::is_bad_ptr(attacker)) {
					if (hurt != local && attacker == local) {
						int hitGroup = _event->GetInt("hitgroup");
						if (hitGroup == 1)
							increaseHeadshots();
					}
				}
			}
		}
	}
	void checkSync() {
		
		bool ingame = interfaceManager::iengine->IsConnected() && interfaceManager::iengine->IsInGame();
		if (ingame != isIngame) {
			writeStatistics();
			isIngame = ingame;
		}
	}
	void increaseHeadshots() {
		newStatistics = true;
		variables::misc::statistics::iHeadshots++;
	}
	void increaseDeaths() {
		newStatistics = true;
		variables::misc::statistics::iDeaths++;
	}
	bool isIngame = false;
	bool newStatistics = false;
	std::string path = "";
};