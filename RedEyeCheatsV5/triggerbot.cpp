#include "Triggerbot.h"
#include "variables.h"
#include "Interfaces.h"
#include "inputManager.h"
void Triggerbot::Sync(cBasePlayer* local)
{
	if (!Functions::is_bad_ptr(local)) {
		cBaseCombatWeapon* combat = local->m_hActiveWeapon();
		if (combat) {
			ClientClass* client = combat->m_ClientClass();
			if (client) {
				/*We are in the rifle category*/
				if (client->m_ClassID == classid::CWeaponAug || client->m_ClassID == classid::CWeaponM3 || client->m_ClassID == classid::CWeaponM4A1 || client->m_ClassID == classid::CWeaponFamas || client->m_ClassID == classid::CWeaponSG550 || client->m_ClassID == classid::CWeaponSG556 || client->m_ClassID == classid::CWeaponSG552 || client->m_ClassID == classid::CAK47 || client->m_ClassID == classid::CWeaponGalilAR || client->m_ClassID == classid::CWeaponGalil || client->m_ClassID == classid::CWeaponNegev || client->m_ClassID == classid::CWeaponM249) {
					Enabled = variables::aimbot::rifles::triggerbot::enabled;
					Team = variables::aimbot::rifles::triggerbot::team;
					Enemies = variables::aimbot::rifles::triggerbot::enemies;
					Delay = (float)variables::aimbot::rifles::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::rifles::triggerbot::key;
					Head = variables::aimbot::rifles::triggerbot::head;
					UpperBody = variables::aimbot::rifles::triggerbot::upperbody;
					LowerBody = variables::aimbot::rifles::triggerbot::lower;
					Legs = variables::aimbot::rifles::triggerbot::legs;
					Arms = variables::aimbot::rifles::triggerbot::arms;


				}
				else if (client->m_ClassID == classid::CWeaponMAC10 || client->m_ClassID == classid::CWeaponP90 || client->m_ClassID == classid::CWeaponUMP45 || client->m_ClassID == classid::CWeaponBizon || client->m_ClassID == classid::CWeaponMP7 || client->m_ClassID == classid::CWeaponMP9) {
					Enabled = variables::aimbot::smg::triggerbot::enabled;
					Team = variables::aimbot::smg::triggerbot::team;
					Enemies = variables::aimbot::smg::triggerbot::enemies;
					Delay = (float)variables::aimbot::smg::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::smg::triggerbot::key;
					Head = variables::aimbot::smg::triggerbot::head;
					UpperBody = variables::aimbot::smg::triggerbot::upperbody;
					LowerBody = variables::aimbot::smg::triggerbot::lower;
					Legs = variables::aimbot::smg::triggerbot::legs;
					Arms = variables::aimbot::smg::triggerbot::arms;

				}
				else if (client->m_ClassID == classid::CWeaponSCAR20 || client->m_ClassID == classid::CWeaponG3SG1) {
					/* We are in the sniper category (hopefully cx)*/
					Enabled = variables::aimbot::autosniper::triggerbot::enabled;
					Team = variables::aimbot::autosniper::triggerbot::team;
					Enemies = variables::aimbot::autosniper::triggerbot::enemies;
					Delay = (float)variables::aimbot::autosniper::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::autosniper::triggerbot::key;
					Head = variables::aimbot::autosniper::triggerbot::head;
					UpperBody = variables::aimbot::autosniper::triggerbot::upperbody;
					LowerBody = variables::aimbot::autosniper::triggerbot::lower;
					Legs = variables::aimbot::autosniper::triggerbot::legs;
					Arms = variables::aimbot::autosniper::triggerbot::arms;
				}
				else if (client->m_ClassID == classid::CWeaponAWP) {
					Enabled = variables::aimbot::awp::triggerbot::enabled;
					Team = variables::aimbot::awp::triggerbot::team;
					Enemies = variables::aimbot::awp::triggerbot::enemies;
					Delay = (float)variables::aimbot::awp::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::awp::triggerbot::key;
					Head = variables::aimbot::awp::triggerbot::head;
					UpperBody = variables::aimbot::awp::triggerbot::upperbody;
					LowerBody = variables::aimbot::awp::triggerbot::lower;
					Legs = variables::aimbot::awp::triggerbot::legs;
					Arms = variables::aimbot::awp::triggerbot::arms;
				}
				else if (client->m_ClassID == classid::CWeaponSSG08 || client->m_ClassID == classid::CWeaponScout) {
					Enabled = variables::aimbot::scout::triggerbot::enabled;
					Team = variables::aimbot::scout::triggerbot::team;
					Enemies = variables::aimbot::scout::triggerbot::enemies;
					Delay = (float)variables::aimbot::scout::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::scout::triggerbot::key;
					Head = variables::aimbot::scout::triggerbot::head;
					UpperBody = variables::aimbot::scout::triggerbot::upperbody;
					LowerBody = variables::aimbot::scout::triggerbot::lower;
					Legs = variables::aimbot::scout::triggerbot::legs;
					Arms = variables::aimbot::scout::triggerbot::arms;
				}
				else if (client->m_ClassID == classid::CWeaponGlock || client->m_ClassID == classid::CWeaponP250 || client->m_ClassID == classid::CDEagle || client->m_ClassID == classid::CWeaponElite || client->m_ClassID == classid::CWeaponTec9 || client->m_ClassID == classid::CWeaponHKP2000 || client->m_ClassID == classid::CWeaponUSP || client->m_ClassID == classid::CWeaponFiveSeven) {
					Enabled = variables::aimbot::pistols::triggerbot::enabled;
					Team = variables::aimbot::pistols::triggerbot::team;
					Enemies = variables::aimbot::pistols::triggerbot::enemies;
					Delay = (float)variables::aimbot::pistols::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::pistols::triggerbot::key;
					Head = variables::aimbot::pistols::triggerbot::head;
					UpperBody = variables::aimbot::pistols::triggerbot::upperbody;
					LowerBody = variables::aimbot::pistols::triggerbot::lower;
					Legs = variables::aimbot::pistols::triggerbot::legs;
					Arms = variables::aimbot::pistols::triggerbot::arms;
				}
				else if (client->m_ClassID == classid::CWeaponNOVA || client->m_ClassID == classid::CWeaponXM1014 || client->m_ClassID == classid::CWeaponSawedoff || client->m_ClassID == classid::CWeaponMag7) {
					Enabled = variables::aimbot::shotguns::triggerbot::enabled;
					Team = variables::aimbot::shotguns::triggerbot::team;
					Enemies = variables::aimbot::shotguns::triggerbot::enemies;
					Delay = (float)variables::aimbot::shotguns::triggerbot::delay / 100.f;
					m_iKey = variables::aimbot::shotguns::triggerbot::key;
					Head = variables::aimbot::shotguns::triggerbot::head;
					UpperBody = variables::aimbot::shotguns::triggerbot::upperbody;
					LowerBody = variables::aimbot::shotguns::triggerbot::lower;
					Legs = variables::aimbot::shotguns::triggerbot::legs;
					Arms = variables::aimbot::shotguns::triggerbot::arms;
				}
				else {
					Enabled = false;
					Team = false;
					Enemies = true;
				}
			}
		}
	}
}
void Triggerbot::Loop(CUserCmd* cmd)
{
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (!local) return;
	if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;


	Sync(local);
	if (!Enabled) { return; }
	if (Functions::is_bad_ptr(local)) { return; }
	if (local->m_iHealth() <= 0) { return; }
	if (m_iKey != -1 && !inputmanager.hold(m_iKey)) {  return; }
	
	cBaseCombatWeapon* m_LocalWeapon = local->m_hActiveWeapon();
	
	Vector m_qViewAngle = cmd->viewangles + (local->m_aimPunchAngleV() * 2);
	Vector m_vecViewAngle = Functions::AngleToVector(QAngle{ m_qViewAngle.x, m_qViewAngle.y, m_qViewAngle.z });
	
	m_vecViewAngle *= m_LocalWeapon->CSWeaponData()->m_flRange;
	
	Vector m_vecOrigin = local->m_vecEye();
	Vector m_vecTarget = m_vecOrigin + m_vecViewAngle;


	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = local;
	ray.Init(m_vecOrigin, m_vecTarget);
	MessageBoxA(NULL, "2", "2", NULL);
	interfaceManager::itrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
	cBaseEntity* hit = tr.hit_entity;





	if (Functions::is_bad_ptr(hit)) return;
	MessageBoxA(NULL, "3", "3", NULL);
	if (hit->m_ClientClass()->m_ClassID != classid::CCSPlayer) return;
	MessageBoxA(NULL, "4", "4", NULL);
	cBasePlayer* hit_player = (cBasePlayer*)hit;
	if (local->OccludedBySmoke(hit)) return;
	MessageBoxA(NULL, "5", "5", NULL);
	if (tr.hitgroup == 1 && !Head) return;
	MessageBoxA(NULL, "6", "6", NULL);
	if (tr.hitgroup == 2 && !UpperBody) return;
	MessageBoxA(NULL, "7", "7", NULL);
	if (tr.hitgroup == 3 && !LowerBody) return;
	MessageBoxA(NULL, "8", "8", NULL);
	if ((tr.hitgroup == 6 || tr.hitgroup == 7) && !Legs) return;
	MessageBoxA(NULL, "9", "9", NULL);
	if ((tr.hitgroup == 4 || tr.hitgroup == 5) && !Arms) return;
	MessageBoxA(NULL, "10", "10", NULL);
	if (hit_player->m_iHealth() <= 0) return;
	MessageBoxA(NULL, "11", "11", NULL);
	bool isSameTeam = hit_player->sameTeam(local);
	MessageBoxA(NULL, "12", "12", NULL);
	if (isSameTeam && !Team) return;
	if (!isSameTeam && !Enemies) return;
	MessageBoxA(NULL, "13", "13", NULL);
	if (local->CanFire()) {
		MessageBoxA(NULL, "14", "14", NULL);
		cmd->buttons |= IN_ATTACK;
	}

	/*if (Delay == 0) {
		cmd->buttons |= IN_ATTACK;
	}
	else	{
		float TimeSince = Interfaces::globals->curtime - TimeStartedTriggering;
		if (TimeSince > Delay) {

		}
	}*/



}
