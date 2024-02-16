#include "Misc.h"
#include "classes.h"
#include "interfaces.h"
#include "variables.h"
#include "cBaseCombatWeapon.h"
#include "skinchanger.h"
#include "log.h"
#include "crashhandler.h"
Misc misc;


void Misc::Autostrafe(CUserCmd* cmd, cBasePlayer* local) {

	if (!(local->m_fFlags() & FL_ONGROUND) && local->movetype() != MoveType::MOVETYPE_NOCLIP && local->movetype() != MoveType::MOVETYPE_LADDER) {
		if (cmd->mousedx < 0)
			cmd->sidemove = -450.0f;
		if (cmd->mousedx > 0)
			cmd->sidemove = 450.0f;
	}
}

void Misc::clantagRun(CUserCmd* cmd, cBasePlayer* local) {
	
	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) return;
	if (!(cmd->buttons & IN_SCORE)) return;
	static std::string finalSet = "";
	std::string staticClantag = variables::misc::clantag;
	if (finalSet != staticClantag) {
		Functions::changeClantag(staticClantag);
		finalSet = staticClantag;
	}
}
void Misc::Bhop(CUserCmd* cmd, cBasePlayer* local) {
	
	static bool bLastJumped = false;
	static bool bShouldFake = false;
	if (!bLastJumped && bShouldFake) {
		bShouldFake = false;
		cmd->buttons |= IN_JUMP;
	}

	else if (cmd->buttons & IN_JUMP) {
		if (local->m_fFlags() & FL_ONGROUND) {
			bLastJumped = true;
			bShouldFake = true;
		}
		else {
			cmd->buttons &= ~IN_JUMP;
				
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}
void Misc::floatingModels(CUserCmd* cmd, cBasePlayer* local) {
	static ConVar* cl_ragdollgravity = interfaceManager::icvars->FindVar("cl_ragdollgravity");
	static bool bChanged = false;
	if (cl_ragdollgravity) {
		if (bChanged != variables::misc::floating) {
			if (variables::misc::floating)
				cl_ragdollgravity->SetValue(0);
			else
				cl_ragdollgravity->SetValue(600);
			bChanged = variables::misc::floating;
		}
	}
	else {
		if (variables::misc::floating) {
			cl_ragdollgravity = interfaceManager::icvars->FindVar("cl_ragdollgravity");
		}
	}
}

void Misc::LeftHandedKnife(cBasePlayer* local)
{
	if (variables::misc::leftHandedKnife) {
		m_bOldValue = true;
		if (!Functions::is_bad_ptr(local)) {
			if (local->m_iHealth() > 0) {
				cBaseCombatWeapon* weapon = local->m_hActiveWeapon();
				if (!Functions::is_bad_ptr(weapon)) {
					if (skinchanger.IsKnife((int)weapon->m_iItemDefinitionIndex())) {
						if (!m_bLeftHand) {
							m_bLeftHand = true;
							m_bKnifeSwitch = true;
						}

					}
					else {
						if (m_bLeftHand) {
							m_bLeftHand = false;
							m_bKnifeSwitch = true;
						}
					}
				}
			}
		}
	}
	else {
		if (m_bOldValue) {
			m_bKnifeSwitch = true;
			m_bLeftHand = false;
			m_bOldValue = false;
		}
	}

	if (m_bKnifeSwitch && !Functions::is_bad_ptr(interfaceManager::iengine)) {
		if (m_bLeftHand)
			interfaceManager::iengine->ExecuteClientCmd("cl_righthand 0");
		else
			interfaceManager::iengine->ExecuteClientCmd("cl_righthand 1");
		m_bKnifeSwitch = false;
	}

}
void Misc::RevealRanks(CUserCmd* cmd, cBasePlayer* local) {
	if (cmd->buttons & IN_SCORE && variables::misc::revealranks) {
		if (!Functions::is_bad_ptr(local) && !Functions::is_bad_ptr(interfaceManager::ibaseclient)) {
			virtualFunction< bool(__thiscall*)(void*, int, unsigned int, unsigned int, void*) >(interfaceManager::ibaseclient, 38)(interfaceManager::ibaseclient, ECstrike15UserMessages::CS_UM_ServerRankRevealAll, 0, 0, nullptr);
		}
	}
}
void Misc::Autopistol(cBasePlayer* entity, CUserCmd* cmd)
{
	
		if (entity->m_iHealth() <= 0) return;
		cBaseCombatWeapon* weapon = entity->m_hActiveWeapon();
		if (Functions::is_bad_ptr(weapon)) return;
		ItemDefinitionIndex m_iItemDefintionIndex = weapon->m_iItemDefinitionIndex();
		if (m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_CZ75
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_DEAGLE
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_ELITE
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_FIVESEVEN
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_GLOCK
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_P2000
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_P250
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_REVOLVER
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_TEC9
			|| m_iItemDefintionIndex == ItemDefinitionIndex::WEAPON_USPS)
		{
			if (cmd->buttons & IN_ATTACK) {
				if (weapon->flNextPrimaryAttack() < (interfaceManager::iglobal->interval_per_tick * entity->m_nTickBase())) {
					cmd->buttons |= IN_ATTACK;
				}
				else {
					cmd->buttons &= ~IN_ATTACK;
				}

			}
		}
	

}
int shouldPlayEffect = 0;
Vector previousPositions[3] = {};
void Misc::particleEffects(cBasePlayer* local) {
	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame()) return;
	if (variables::misc::trailParticles == 0) return;
	if (local->m_iHealth() == 0) return;
	if (local->m_vecVelocity() == Vector(0, 0, 0)) { 
		previousPositions[0] = previousPositions[1] = previousPositions[2] = Vector(0, 0, 0);
		return; 
	}
	int correctFrame = (10 - (int)round(((float)variables::misc::rateOfParticle / 100.f) * 10)) + 1;
	if (shouldPlayEffect >= correctFrame) {
		shouldPlayEffect = 0;
		Vector position = local->m_vecOrigin(); position.z += 3; Vector direction = local->m_vecVelocity();
		Vector newPositions[3] = { position, previousPositions[0],  previousPositions[1] };
		for (int i = 0; i < 3; i++) {
			if (newPositions[i] == Vector(0, 0, 0)) continue;
			switch (variables::misc::trailParticles) {
			case 1:
				interfaceManager::ieffect->EnergySplash(newPositions[i], direction, false);
				break;
			case 2:
				interfaceManager::ieffect->MuzzleFlash(newPositions[i], QAngle(0, -Game::localRotation, 0), 1, 1);
				break;
			case 3:
				interfaceManager::ieffect->Smoke(newPositions[i], 1, 10, 10);
				break;
			case 4:
				interfaceManager::ieffect->Sparks(newPositions[i]);
				break;
			default:
				break;
			}
			previousPositions[i] = newPositions[i];
		}

	}
	else {
		shouldPlayEffect++;
	}

}

void Misc::Loop(CUserCmd* cmd) {
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local)) return;
	crashhandler.setDebug("CMDMOVE_MISC_1");
	if (variables::misc::autoPistol)
		Autopistol(local, cmd);
	crashhandler.setDebug("CMDMOVE_MISC_2");
	if (variables::misc::autoStrafe)
		Autostrafe(cmd, local);
	crashhandler.setDebug("CMDMOVE_MISC_3");
	if (variables::misc::bhop)
		Bhop(cmd, local);
	crashhandler.setDebug("CMDMOVE_MISC_4");
	if (variables::misc::revealranks)
		RevealRanks(cmd, local);
	crashhandler.setDebug("CMDMOVE_MISC_4");
	if (variables::misc::leftHandedKnife)
		LeftHandedKnife(local);
	crashhandler.setDebug("CMDMOVE_MISC_5");
	floatingModels(cmd, local);
	crashhandler.setDebug("CMDMOVE_MISC_6");
	particleEffects(local);
	clantagRun(cmd, local);
	
}