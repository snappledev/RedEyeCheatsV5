#include "Aimbot.h"
#include "inputManager.h"
#include "cCSPlayer.h"
#include "variables.h"
#include "painting.h"
#include "Functions.h"
#include "crashhandler.h"
#define MAXBACKTRACKTICKS (Backtr)
#define TICK_INTERVAL			(interfaceManager::iglobal->interval_per_tick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define GetWeap(a) ((a < 0) ? 0 : (a >= (int)Weapons.size() ? (int)Weapons.size()-1 : a))
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
int SelectedWeapon = 0;
#include "log.h"
enum class weaponTypes
{
	rifles, 
	pistols, 
	shotguns,
	sniper,
	heavy,
	smgs
};
void aimbotFeature::SetSelectedWeapon(bool MenuCheck)
{
	if (variables::gui::bShowMainGui)
	{
		SelectedWeapon = 0;

		if (SelectedWeapon < 0)
			SelectedWeapon = 0;

		/*if (WeaponCustomTypes == 1) // standart
		{
			switch (weapon_type)
			{
			case (int)weaponTypes::rifles: SelectedWeapon = 34; StandartSubSelected = 0; CheckAimCust = true; break;
			case (int)weaponTypes::pistols: SelectedWeapon = 35; StandartSubSelected = 1; CheckAimCust = true;  break;
			case (int)weaponTypes::shotguns: SelectedWeapon = 36; StandartSubSelected = 2; CheckAimCust = true;  break;
			case (int)weaponTypes::sniper: SelectedWeapon = 37; StandartSubSelected = 3; CheckAimCust = true;  break;
			default: SelectedWeapon = -1; CheckAimCust = false;  break;
			}

		}
		else
			CheckAimCust = true;*/
	}
}

float TestSF = 10;

float TestMouse = 0;

Vector OldStandRCS = Vector(0, 0, 0);
bool NextSimpleDisable = false;
bool NextAutoShot = false;
float start = 0;

void aimbotFeature::CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd)
{
	iBestTarget = -1;
	iBestHitBox = -1;
	iSilentBestTarget = -1;
	iSilentBestHitBox = -1;
	if (Functions::is_bad_ptr(pCmd)) return;

	
	if (!CheckOpportWork(pCmd)) {
		FFDelayOCActive = false;
		return;
	}

	
	CurTime = interfaceManager::iglobal->curtime;
	FFDelay.Update(CurTime);
	TSDelay.Update(CurTime);
	if (Functions::is_bad_ptr(pLocalPlayer)) { return; }
	bool IsRevolver = weapon_id ==  (int)ItemDefinitionIndex::WEAPON_REVOLVER && (pCmd->buttons & IN_ATTACK2);
	LpCmd = pCmd;
	StandeloneRCS(pCmd);

	Vector StartAng = pCmd->viewangles;

	AimPunchAngle = pLocalPlayer->m_aimPunchAngleV();
	FovStartAng = pCmd->viewangles + ((AimPunchAngle * (Vector(RCS_X, RCS_Y, 0) / 100.f)) * 2.f);

	if (CanSilent)
	{
	
		if (!GetBestTarget(true))
			CanSilent = false;

		if (CanSilent)
			if (!GetBestHitBox(true))
				CanSilent = false;

		if (!CanSilent && pSilentAutoDelayEnable && FFDelayEnable)
			pSilentAutoDelay = true;
		else
			pSilentAutoDelay = false;
	}
	else
		pSilentAutoDelay = false;

	GetBestTarget(false);
	if (iBestTarget != -1)
		GetBestHitBox(false);

	static ItemDefinitionIndex OldWeapon = (ItemDefinitionIndex)0;

	
	OldWeapon = (ItemDefinitionIndex)weapon_id;

	 
	bool FindedTarg = (iBestTarget != -1 && iBestHitBox != -1) || (iSilentBestTarget != -1 && iSilentBestHitBox != -1);

	if (AutoFire && FindedTarg)
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;
	if (IsSniperClass && FastZoom && !IsZoomed)
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			pCmd->buttons &= ~IN_ATTACK;
			pCmd->buttons |= IN_ZOOM;

			NextAutoShot = true;
		}
		else
			NextAutoShot = false;
	}
	else
		NextAutoShot = false;



	bool PistolPreFire = (IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK));

	if ((IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
		if ((AutoFire) && IsPistol)
			CalcAutoPistol(pCmd, pLocalPlayer);
	bool AnyDelay = (FFDelay.STimer.Active || FFAutoDelay || pSilentAutoDelay);
	static bool FixAttack = false;
	if (FixAttack) {
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;
		FixAttack = false;
	}
	if (FFDelayOCActive && !AnyDelay && FindedTarg && !FFDelayOCDisable) {
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;
		FixAttack = true;
		FFDelayOCDisable = true;
	}
	bool IsAttack = (IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)) || (NextAutoShot && IsSniperClass && FastZoom);
	FFDelayOCActive = FindedTarg && AnyDelay && (IsAttack || FFDelayOCActive) && FFDelayOneClickEnable && !FFDelayOCDisable;
	static bool SetRevolvTime = false;
	static float RevolvStartFire = 0;
	static float RevolvNextFire = 0;
	if ((pCmd->buttons & IN_ATTACK) && !SetRevolvTime ) {
		RevolvNextFire = interfaceManager::iglobal->curtime + 0.20f;
		SetRevolvTime = true;
	}
	if (!(pCmd->buttons & IN_ATTACK))
		SetRevolvTime = false;
	
	if ((((IsAttack || (IsPistol && PistolPreFire)) && FindedTarg) || FFDelayOCActive) && true/*shotgun_check*/)
	{
		if (FFAutoDelayEnable && FFDelayEnable && !FFDelayDisable)
		{
			if (!CanFire(FovStartAng, pCmd, pBestTarget, 1, pLocalPlayer, true))
				FFAutoDelay = true;
			else
			{
				FFAutoDelay = false;
				FFAutoDelayDisable = true;
			}
		}
		else
			FFAutoDelay = false;

		if (!KillStopEnable)
		{
			if (TSDelayEnable && TSDelayTime > 0 && pOldBestTarget)
				if (pOldBestTarget->m_iHealth() == 0)
					TSDelay = CAimTimer(CurTime + TSDelayTime, true);
		}
		else
			if (pOldBestTarget && pOldBestTarget->m_iHealth() == 0)
				KillStop = true;

		if (FFAutoDelay && !FFAutoDelayDisable) {
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;
		}
		
		if (FFDelayEnable && FFDelayTime > 0 && !FFDelayDisable)
			if (!FFDelay.STimer.Enable)
				FFDelay = CAimTimer(CurTime + FFDelayTime, true);

		if (FFDelay.STimer.Active)
			IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;

		CalcFinalVecRcs(false);
		if (CanSilent)
			CalcFinalVecRcs(true);

		if (FFDelay.STimer.Active) {
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;
		}

		if (pSilentAutoDelay && !pSilentAutoDelayDisable && !CanFire(FovStartAng, pCmd, pBestTarget, 1, pLocalPlayer, true)) {
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;
		}
		else
			pSilentAutoDelayDisable = true;

		if ((IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
			FFDelayOCDisable = true;
		
		if (!TSDelay.STimer.Active && !KillStop)
		{
			Vector FinalVec_Temp = Smooth(StartAng, FinalVec, GSmooth, false);
			Vector SilentFinalVec_Temp = Smooth(StartAng, SilentFinalVec, 0, true);
			if (CanSilent)
				CanSilent = (SilentHitchance == 100 ?
					true : ((1 + (rand() % 101)) <= SilentHitchance));
			if (!CanSilent) {
				if (iBestTarget != -1 && iBestHitBox != -1) {
					CreateAssistMove(FinalVec_Temp);
				}
			}

			if (weapon_id == (int)ItemDefinitionIndex::WEAPON_REVOLVER)
			{
				bool FinalEnableSilent = CanSilent;

				if ((weapon_id == (int)ItemDefinitionIndex::WEAPON_REVOLVER) && (pCmd->buttons & IN_ATTACK))
				{
					

					bool TimeDDD = RevolvNextFire - interfaceManager::iglobal->curtime > ((iShotsFired == 0) ? 0.16f : 0.18f);

					if (TimeDDD)
						FinalEnableSilent = false;
					else
						SetRevolvTime = false;
				}

				if (FinalEnableSilent)
				{
					pCmd->viewangles = SilentFinalVec_Temp;
					if (iBestTarget != -1 && iBestHitBox != -1)
						CreateAssistMove(FinalVec_Temp, true);

					bSendPacket = false;
				}
				else
				{
					if (CanSilent)
						if (iBestTarget != -1 && iBestHitBox != -1)
							CreateAssistMove(FinalVec_Temp);
				}
			}
			else
			{
				if (CanSilent)
				{
					pCmd->viewangles = SilentFinalVec_Temp;
					if (iBestTarget != -1 && iBestHitBox != -1) {
						CreateAssistMove(FinalVec_Temp, true);
					}

					bSendPacket = false;
				}
			}
		}
	}
	else
	{
		FFDelay.STimer.Enable = false;
		TSDelay.STimer.Enable = false;
		KillStop = false;
		pSilentAutoDelayDisable = false;
		FFAutoDelay = false;
		FFAutoDelayDisable = false;
		SetSmoothStart = false;
		FFDelayOCDisable = false;
	}


	if (!(IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
		FFDelayDisable = false;
	else
		FFDelayDisable = true;


	if (pBestTarget)
		pOldBestTarget = pBestTarget;
}

void aimbotFeature::SetMainParams()
{

	cBaseEntity* local = interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	cBasePlayer* lp = (cBasePlayer*)local;
	pLocalPlayer = lp;
	
	if (!Functions::is_bad_ptr(local)) {
		cBaseCombatWeapon* combat = local->m_hActiveWeapon();
		
		if (!Functions::is_bad_ptr(combat)) {
			pLocalWeapon = combat;
			iShotsFired = lp->m_iShotsFired();
			weapon_id = (int)combat->m_iItemDefinitionIndex();
			ClientClass* client = combat->m_ClientClass();
			if (!Functions::is_bad_ptr(client)) {
				/*We are in the rifle category*/
				if (client->m_ClassID == classid::CWeaponAug || client->m_ClassID == classid::CWeaponM3 || client->m_ClassID == classid::CWeaponM4A1 || client->m_ClassID == classid::CWeaponFamas || client->m_ClassID == classid::CWeaponSG550 || client->m_ClassID == classid::CWeaponSG556 || client->m_ClassID == classid::CWeaponSG552 || client->m_ClassID == classid::CAK47 || client->m_ClassID == classid::CWeaponGalilAR || client->m_ClassID == classid::CWeaponGalil || client->m_ClassID == classid::CWeaponNegev || client->m_ClassID == classid::CWeaponM249) {
					weapon_type = (int)weaponTypes::rifles;
					Enable = variables::aimbot::rifles::Enabled;
					Enemies = variables::aimbot::rifles::enemies;
					Team = variables::aimbot::rifles::team;
					AimBind = variables::aimbot::rifles::key;

					//KillStopEnable = variables::aimbot::rifles::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::rifles::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::rifles::humanization::firstfiredelayenable;
					//FFDelayTime = (float)((float)variables::aimbot::smg::humanization::firstfiredelay / 100.f);
					//TSDelayEnable = variables::aimbot::rifles::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::rifles::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::rifles::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::rifles::humanization::firstfiredelaysilent;
					//FFAutoDelayEnable = variables::aimbot::rifles::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::rifles::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::rifles::humanization::silent, variables::aimbot::rifles::humanization::silentfov,
						variables::aimbot::rifles::humanization::silenthitchance, variables::aimbot::rifles::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::rifles::humanization::rcsx, variables::aimbot::rifles::humanization::rcsy) && variables::aimbot::rifles::humanization::rcs;
					FovPos = variables::aimbot::rifles::humanization::fovpos;
					SmoothMF = variables::aimbot::rifles::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::rifles::humanization::silentnearest;
					SilentHitBox = variables::aimbot::rifles::humanization::silenthitbox;
					GSilentFov = variables::aimbot::rifles::humanization::silentfov;
					IsNearest = variables::aimbot::rifles::humanization::nearest;
					HitBox = variables::aimbot::rifles::humanization::hitbox;
					GFov = variables::aimbot::rifles::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::rifles::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::rifles::humanization::smooth;
					CanRCSStandelone = variables::aimbot::rifles::humanization::rcsstandalone;
					Backtrack = variables::aimbot::rifles::backtrack::enabled;
					BacktrackTicks = variables::aimbot::rifles::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponMAC10 || client->m_ClassID == classid::CWeaponP90 || client->m_ClassID == classid::CWeaponUMP45 || client->m_ClassID == classid::CWeaponBizon || client->m_ClassID == classid::CWeaponMP7 || client->m_ClassID == classid::CWeaponMP9) {
					weapon_type = (int)weaponTypes::smgs;
					Enable = variables::aimbot::smg::Enabled;
					Enemies = variables::aimbot::smg::enemies;
					Team = variables::aimbot::smg::team;
					AimBind = variables::aimbot::smg::key;

					//KillStopEnable = variables::aimbot::smg::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::smg::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::smg::humanization::firstfiredelayenable;
					//FFDelayTime = (float)((float)variables::aimbot::smg::humanization::firstfiredelay / 100.f);
					//TSDelayEnable = variables::aimbot::smg::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::smg::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::smg::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::smg::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::smg::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::smg::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::smg::humanization::silent, variables::aimbot::smg::humanization::silentfov,
						variables::aimbot::smg::humanization::silenthitchance, variables::aimbot::smg::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::smg::humanization::rcsx, variables::aimbot::smg::humanization::rcsy) && variables::aimbot::rifles::humanization::rcs;;
					FovPos = variables::aimbot::smg::humanization::fovpos;
					SmoothMF = variables::aimbot::smg::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::smg::humanization::silentnearest;
					SilentHitBox = variables::aimbot::smg::humanization::silenthitbox;
					GSilentFov = variables::aimbot::smg::humanization::silentfov;
					IsNearest = variables::aimbot::smg::humanization::nearest;
					HitBox = variables::aimbot::smg::humanization::hitbox;
					GFov = variables::aimbot::smg::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::smg::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::smg::humanization::smooth;
					CanRCSStandelone = variables::aimbot::smg::humanization::rcsstandalone;
					Backtrack = variables::aimbot::smg::backtrack::enabled;
					BacktrackTicks = variables::aimbot::smg::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponSCAR20 || client->m_ClassID == classid::CWeaponG3SG1) {
					weapon_type = (int)weaponTypes::sniper;
					Enable = variables::aimbot::autosniper::Enabled;
					Enemies = variables::aimbot::autosniper::enemies;
					Team = variables::aimbot::autosniper::team;
					AimBind = variables::aimbot::autosniper::key;

					//KillStopEnable = variables::aimbot::autosniper::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::autosniper::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::autosniper::humanization::firstfiredelayenable;
					//FFDelayTime = (float)((float)variables::aimbot::smg::humanization::firstfiredelay / 100.f);
					//TSDelayEnable = variables::aimbot::autosniper::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::autosniper::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::autosniper::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::autosniper::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::autosniper::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::autosniper::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::autosniper::humanization::silent, variables::aimbot::autosniper::humanization::silentfov,
						variables::aimbot::autosniper::humanization::silenthitchance, variables::aimbot::autosniper::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::autosniper::humanization::rcsx, variables::aimbot::autosniper::humanization::rcsy) && variables::aimbot::rifles::humanization::rcs;;
					FovPos = variables::aimbot::autosniper::humanization::fovpos;
					SmoothMF = variables::aimbot::autosniper::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::autosniper::humanization::silentnearest;
					SilentHitBox = variables::aimbot::autosniper::humanization::silenthitbox;
					GSilentFov = variables::aimbot::autosniper::humanization::silentfov;
					IsNearest = variables::aimbot::autosniper::humanization::nearest;
					HitBox = variables::aimbot::autosniper::humanization::hitbox;
					GFov = variables::aimbot::autosniper::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::autosniper::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::autosniper::humanization::smooth;
					CanRCSStandelone = variables::aimbot::autosniper::humanization::rcsstandalone;
					Backtrack = variables::aimbot::autosniper::backtrack::enabled;
					BacktrackTicks = variables::aimbot::autosniper::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponAWP) {
					weapon_type = (int)weaponTypes::sniper;
					Enable = variables::aimbot::awp::Enabled;
					Enemies = variables::aimbot::awp::enemies;
					Team = variables::aimbot::awp::team;
					AimBind = variables::aimbot::awp::key;

					//KillStopEnable = variables::aimbot::awp::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::awp::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::awp::humanization::firstfiredelayenable;
					//FFDelayTime = variables::aimbot::awp::humanization::firstfiredelay;
					//TSDelayEnable = variables::aimbot::awp::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::awp::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::awp::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::awp::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::awp::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::awp::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::awp::humanization::silent, variables::aimbot::awp::humanization::silentfov,
						variables::aimbot::awp::humanization::silenthitchance, variables::aimbot::awp::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::awp::humanization::rcsx, variables::aimbot::awp::humanization::rcsy) && variables::aimbot::awp::humanization::rcs;;
					FovPos = variables::aimbot::awp::humanization::fovpos;
					SmoothMF = variables::aimbot::awp::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::awp::humanization::silentnearest;
					SilentHitBox = variables::aimbot::awp::humanization::silenthitbox;
					GSilentFov = variables::aimbot::awp::humanization::silentfov;
					IsNearest = variables::aimbot::awp::humanization::nearest;
					HitBox = variables::aimbot::awp::humanization::hitbox;
					GFov = variables::aimbot::awp::humanization::fovrcs != 0 && iShotsFired >= 1 ?
						variables::aimbot::awp::humanization::fovrcs : variables::aimbot::awp::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::awp::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::awp::humanization::smooth;
					CanRCSStandelone = variables::aimbot::awp::humanization::rcsstandalone;
					Backtrack = variables::aimbot::awp::backtrack::enabled;
					BacktrackTicks = variables::aimbot::awp::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponSSG08 || client->m_ClassID == classid::CWeaponScout) {
					weapon_type = (int)weaponTypes::sniper;
					Enable = variables::aimbot::scout::Enabled;
					Enemies = variables::aimbot::scout::enemies;
					Team = variables::aimbot::scout::team;
					AimBind = variables::aimbot::scout::key;

					//KillStopEnable = variables::aimbot::scout::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::scout::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::scout::humanization::firstfiredelayenable;
					//FFDelayTime = variables::aimbot::scout::humanization::firstfiredelay;
					//TSDelayEnable = variables::aimbot::scout::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::scout::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::scout::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::scout::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::scout::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::scout::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::scout::humanization::silent, variables::aimbot::scout::humanization::silentfov,
						variables::aimbot::scout::humanization::silenthitchance, variables::aimbot::scout::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::scout::humanization::rcsx, variables::aimbot::scout::humanization::rcsy) && variables::aimbot::scout::humanization::rcs;
					FovPos = variables::aimbot::scout::humanization::fovpos;
					SmoothMF = variables::aimbot::scout::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::scout::humanization::silentnearest;
					SilentHitBox = variables::aimbot::scout::humanization::silenthitbox;
					GSilentFov = variables::aimbot::scout::humanization::silentfov;
					IsNearest = variables::aimbot::scout::humanization::nearest;
					HitBox = variables::aimbot::scout::humanization::hitbox;
					GFov = variables::aimbot::scout::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::scout::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::scout::humanization::smooth;
					CanRCSStandelone = variables::aimbot::scout::humanization::rcsstandalone;
					Backtrack = variables::aimbot::scout::backtrack::enabled;
					BacktrackTicks = variables::aimbot::scout::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponGlock || client->m_ClassID == classid::CWeaponP250 || client->m_ClassID == classid::CDEagle || client->m_ClassID == classid::CWeaponElite || client->m_ClassID == classid::CWeaponTec9 || client->m_ClassID == classid::CWeaponHKP2000 || client->m_ClassID == classid::CWeaponUSP || client->m_ClassID == classid::CWeaponFiveSeven) {
					weapon_type = (int)weaponTypes::pistols;
					Enable = variables::aimbot::pistols::Enabled;
					Enemies = variables::aimbot::pistols::enemies;
					Team = variables::aimbot::pistols::team;
					AimBind = variables::aimbot::pistols::key;

					//KillStopEnable = variables::aimbot::pistols::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::pistols::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::pistols::humanization::firstfiredelayenable;
					//FFDelayTime = variables::aimbot::pistols::humanization::firstfiredelay;
					//TSDelayEnable = variables::aimbot::pistols::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::pistols::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::pistols::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::pistols::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::pistols::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::pistols::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::pistols::humanization::silent, variables::aimbot::pistols::humanization::silentfov,
						variables::aimbot::pistols::humanization::silenthitchance, variables::aimbot::pistols::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::pistols::humanization::rcsx, variables::aimbot::pistols::humanization::rcsy) && variables::aimbot::pistols::humanization::rcs;;
					FovPos = variables::aimbot::pistols::humanization::fovpos;
					SmoothMF = variables::aimbot::pistols::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::pistols::humanization::silentnearest;
					SilentHitBox = variables::aimbot::pistols::humanization::silenthitbox;
					GSilentFov = variables::aimbot::pistols::humanization::silentfov;
					IsNearest = variables::aimbot::pistols::humanization::nearest;
					HitBox = variables::aimbot::pistols::humanization::hitbox;
					GFov = variables::aimbot::pistols::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::pistols::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::pistols::humanization::smooth;
					CanRCSStandelone = variables::aimbot::pistols::humanization::rcsstandalone;
					Backtrack = variables::aimbot::pistols::backtrack::enabled;
					BacktrackTicks = variables::aimbot::pistols::backtrack::ticks;
					FaceItMode = FaceIt;
				}
				else if (client->m_ClassID == classid::CWeaponNOVA || client->m_ClassID == classid::CWeaponXM1014 || client->m_ClassID == classid::CWeaponSawedoff || client->m_ClassID == classid::CWeaponMag7) {
					weapon_type = (int)weaponTypes::shotguns;
					Enable = variables::aimbot::shotguns::Enabled;
					Enemies = variables::aimbot::shotguns::enemies;
					Team = variables::aimbot::shotguns::team;
					AimBind = variables::aimbot::shotguns::key;

					//KillStopEnable = variables::aimbot::shotguns::humanization::killstop;
					//FFDElayOneClickEnable = variables::aimbot::shotguns::humanization::firstfiredelayoneclick;
					//FFDelayEnable = variables::aimbot::shotguns::humanization::firstfiredelayenable;
					//FFDelayTime = variables::aimbot::shotguns::humanization::firstfiredelay;
					//TSDelayEnable = variables::aimbot::shotguns::humanization::targetswitchdelayenable;
					//TSDelayTime = (float)((float)variables::aimbot::shotguns::humanization::targetswitchdelay / 100.f);
					SilentHitchance = variables::aimbot::shotguns::humanization::silenthitchance;
					//pSilentAutoDelayEnable = variables::aimbot::shotguns::humanization::firstfiredelaysilent;
					FFAutoDelayEnable = variables::aimbot::shotguns::humanization::firstfiredelayauto && !EntityAim;
					FastZoom = variables::aimbot::shotguns::humanization::fastzoom;
					CanSilent = IsEnableSilent(variables::aimbot::shotguns::humanization::silent, variables::aimbot::shotguns::humanization::silentfov,
						variables::aimbot::shotguns::humanization::silenthitchance, variables::aimbot::shotguns::humanization::silentstartbullet);
					CanRCS = IsEnableRCS(variables::aimbot::shotguns::humanization::rcsx, variables::aimbot::shotguns::humanization::rcsy) && variables::aimbot::shotguns::humanization::rcs;
					FovPos = variables::aimbot::shotguns::humanization::fovpos;
					SmoothMF = variables::aimbot::shotguns::humanization::smoothmovefactor;
					IsSilentNearest = variables::aimbot::shotguns::humanization::silentnearest;
					SilentHitBox = variables::aimbot::shotguns::humanization::silenthitbox;
					GSilentFov = variables::aimbot::shotguns::humanization::silentfov;
					IsNearest = variables::aimbot::shotguns::humanization::nearest;
					HitBox = variables::aimbot::shotguns::humanization::hitbox;
					GFov =  variables::aimbot::shotguns::humanization::fov;
					if (GDrawRcsFov) {
						GFov = variables::aimbot::shotguns::humanization::fovrcs;
						GDrawRcsFov = false;
					}
					GSmooth = variables::aimbot::shotguns::humanization::smooth;
					CanRCSStandelone = variables::aimbot::shotguns::humanization::rcsstandalone;
					Backtrack = variables::aimbot::shotguns::backtrack::enabled;
					BacktrackTicks = variables::aimbot::shotguns::backtrack::ticks;
					FaceItMode = FaceIt;

				}
				else {
					
					Enable = false;
					weapon_type = 0;
					//KillStopEnable = 0;
					//FFDElayOneClickEnable = 0;
					//FFDelayEnable = 0;
					//FFDelayTime = 0;
					//TSDelayEnable = 0;
					//TSDelayTime = 0;
					SilentHitchance = 0;
					//pSilentAutoDelayEnable = 0;
					FFAutoDelayEnable = 0;
					FastZoom = 0;
					CanSilent = 0;
					CanRCS = 0;
					FovPos = 0;
					SmoothMF = 0;
					IsSilentNearest = 0;
					SilentHitBox = 0;
					GSilentFov = 0;
					IsNearest = 0 && iShotsFired >= 1 ?
						0 : 0;
					HitBox = 0 && iShotsFired >= 1 ?
						0 : 0;
					GFov = 0;
					if (GDrawRcsFov) {
						GFov = 0;
						GDrawRcsFov = false;
					}
					GSmooth = 0;
					CanRCSStandelone = 0;
					FaceItMode = FaceIt;
					Backtrack = false;
				}
			}
		}
	}


}



bool aimbotFeature::CheckOpportWork(CUserCmd* pCmd)
{
	AimWorking = false;
	static bool DisableIfPK = false;

	if (IsNonAimWeapon())
	{
		if ((pCmd->buttons & IN_ATTACK))
			DisableIfPK = true;

		return false;
	}

	if (DisableIfPK && (pCmd->buttons & IN_ATTACK) && AimEndBullet == 1)
		return false;
	else
		DisableIfPK = false;

	if (!inputmanager.hold(AimBind))
		return false;

	pLocalPlayer = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(pLocalPlayer))
		return false;

	if (pLocalPlayer->m_iHealth() <= 0)
		return false;

	pLocalWeapon = pLocalPlayer->m_hActiveWeapon();
	if (Functions::is_bad_ptr(pLocalWeapon))
		return false;

	if (!(pLocalPlayer->m_fFlags() & FL_ONGROUND) && JumpCheck)
		return false;

	//if (pLocalPlayer->IsFlashed() && FlashCheck)
	//	return false;

	if (pLocalWeapon->m_iClip1() == 0)
		return false;


	iShotsFired = pLocalPlayer->m_iShotsFired();

	if (NextAutoShot && iShotsFired != 0)
	{
		NextAutoShot = false;
	}

	if (AimEndBullet != -1 && iShotsFired >= AimEndBullet)
		return false;

	if (weapon_type == (int)weaponTypes::sniper)
		IsSniperClass = true;
	else
		IsSniperClass = false;

	if (IsSniperClass)
		if (pLocalWeapon->m_zoomLevel() == 1 || pLocalWeapon->m_zoomLevel() == 2)
			IsZoomed = true;
		else
			IsZoomed = false;
	else
		IsZoomed = false;


	AimWorking = true;
	return true;
}

float To360(float in)
{
	return (in > 0 ? in : 180 + (180 + in));
}

void aimbotFeature::CreateAssistMove(Vector TargetAng, bool IsSilent)
{
	if (!FaceItMode)
	{
		if (IsSilent) {
			interfaceManager::iengine->SetViewAngles(&TargetAng);
		}
		else
		{
			if (LpCmd)
				LpCmd->viewangles = TargetAng;
			interfaceManager::iengine->SetViewAngles(&TargetAng);
		}
	}
	else if (FaceItMode && !variables::gui::bShowMainGui)
	{
		if (IsSilent)
			interfaceManager::iengine->SetViewAngles(&TargetAng);
		else
		{
			Vector ScreenTargPoint;
			if (LpCmd)
			{
				float diff_x = TargetAng.y - LpCmd->viewangles.y;

				if (LpCmd->viewangles.y > 90 && TargetAng.y < -90)
					diff_x = To360(TargetAng.y) - To360(LpCmd->viewangles.y);

				ScreenTargPoint.x = (ScreenCenterX + ((((ScreenCenterX /  Game::m_FOV) * diff_x)) * -1.f));
				ScreenTargPoint.y = (ScreenCenterY + (((ScreenCenterX /  Game::m_FOV) * (TargetAng.x - LpCmd->viewangles.x))));

				AssistScreenPoint = ScreenTargPoint;
				NewMouseOfstPos = Vector(ScreenTargPoint.x - MousePos.x, ScreenTargPoint.y - MousePos.y, 0);

				if (fabs(NewMouseOfstPos.x) < 1.f)
				{
					if (fabs(NewMouseOfstPos.x) > 0.01f)
					{
						if (NewMouseOfstPos.x > 0.f)
							NewMouseOfstPos.x = 1.f;
						else
							NewMouseOfstPos.x = -1.f;
					}
					else
						NewMouseOfstPos.x = 0.f;
				}

				if (fabs(NewMouseOfstPos.y) < 1.f)
				{
					if (fabs(NewMouseOfstPos.y) > 0.01f)
					{
						if (NewMouseOfstPos.y > 0.f)
							NewMouseOfstPos.y = 1.f;
						else
							NewMouseOfstPos.y = -1.f;
					}
					else
						NewMouseOfstPos.y = 0.f;
				}
				//mouse_event(MOUSEEVENTF_MOVE, (DWORD)NewMouseOfstPos.x, (DWORD)NewMouseOfstPos.y, NULL, NULL);
				mouse_event(MOUSEEVENTF_MOVE, (DWORD)NewMouseOfstPos.x, (DWORD)NewMouseOfstPos.y, NULL, NULL);
			}
		}
	}
}
static void Normalize(Vector& angle) {
	while (angle.x > 89.0f) {
		angle.x -= 180.f;
	}
	while (angle.x < -89.0f) {
		angle.x += 180.f;
	}
	while (angle.y > 180.f) {
		angle.y -= 360.f;
	}
	while (angle.y < -180.f) {
		angle.y += 360.f;
	}
}

Vector aimbotFeature::Smooth(Vector& viewangles, Vector target, float factor, bool silent)
{
	factor /= 100.f;
	Vector delta = target - viewangles;

	if (CCSmooth && factor > 0)
	{
		Vector OldViewAng = viewangles;
		Vector OldTargAng = target;

		TempVec3 = target;

		if (target.x >= 180)
			target.x = (180.f - (180.f - (360.f - target.x))) * -1.f;

		if (target.y >= 180)
			target.y = (180.f - (180.f - (360.f - target.y))) * -1.f;

		TempVec1 = viewangles;
		TempVec2 = target;

		SmoothCurLen = CCSmooth->GetCurLen(viewangles, target);

		if (!SetSmoothStart)
		{
			CCSmooth->StartLen = GFov / 3.f;
			SetSmoothStart = true;
		}

		SmoothCurAngle = CCSmooth->GetCurAngle(SmoothCurLen, viewangles, target);
		SmoothMaxDelta = CCSmooth->GetMaxDelta(CCSmooth->StartLen, SmoothCurAngle, viewangles, target);

		SmoothProgress = (SmoothCurLen / (CCSmooth->StartLen / 100.f));

		viewangles = OldViewAng;
		target = OldTargAng;
	}

	Functions::ClampAngles(delta);

	bool isCurve = false;

	if (!isCurve)
	{
		Vector toChange = Vector(0, 0, 0);
		if (silent)
		{
			Functions::ClampAngles(target);
			return target;
		}

		if (SmoothMF == 0)
		{
			float smooth = powf(factor, 0.27f);

			smooth = min(0.9999999f, smooth);

			toChange = delta - delta * smooth;
		}
		else if (SmoothMF == 1)
		{
			if (factor <= 0)
			{
				Functions::ClampAngles(target);
				return target;
			}

			float smooth = powf(factor, 0.4f);
			smooth = min(0.9999999f, smooth);

			float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
			coeff = min(1.f, coeff);
			toChange = (delta * coeff);
		}

		Vector End = viewangles + toChange;

		Functions::ClampAngles(End);

		return End;
	}

	
	return viewangles;
}

void aimbotFeature::VixViewAng(Vector& VE)
{
	if (VE.y <= -90 && VE.y >= -179)
		VE.y = (90 - ((90 + VE.y) * -1));

	if (VE.x <= -90 && VE.x >= -179)
		VE.x = (90 - ((90 + VE.x) * -1));
}
void aimbotFeature::CalcAutoPistol(CUserCmd* cmd, cBasePlayer* pLocal)
{
	float NextAttack = pLocal->m_hActiveWeapon()->flNextPrimaryAttack();
	float Tick = pLocal->m_nTickBase() * interfaceManager::iglobal->interval_per_tick;

	if (NextAttack < Tick)
		return;

	if (pLocal->m_hActiveWeapon()->m_iItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}
Vector aimbotFeature::PlayerAnglToScreen(Vector Angl)
{
	if (LpCmd)
	{
		Vector viewangles = /*Angl -*/ LpCmd->viewangles;
		float FovFal =  Game::m_FOV;
		return Vector(
			(ScreenCenterX + ((((ScreenCenterX / FovFal) * (Angl.y - viewangles.y))) * -1.f)),
			(ScreenCenterY + (((ScreenCenterX / FovFal) * (Angl.x - viewangles.x)))),
			0);
	}
	else
		return Vector(0, 0, 0);
}

bool aimbotFeature::IsNonAimWeapon()
{
	if (weapon_id == (int)ItemDefinitionIndex::WEAPON_HEGRENADE ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_INC ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_SMOKEGRENADE ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_BAYONET ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_FALCHION ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_FLIP||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_GUT ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_PUSH ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_STILETTO ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_T||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_URSUS ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_CORD ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_CANIS ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_KNIFE_SKELETON ||
		weapon_id == (int)ItemDefinitionIndex::WEAPON_C4)
		return true;

	return false;
}

bool aimbotFeature::CanShoot()
{
	if (Functions::is_bad_ptr(pLocalWeapon)) return false;
	if (pLocalWeapon->m_iClip1() < 1)
		return false;

	float server_time = pLocalPlayer->m_nTickBase() * interfaceManager::iglobal->interval_per_tick;

	float next_shot = pLocalWeapon->flNextPrimaryAttack() - server_time;
	//	ADD_LOG("")
	if (next_shot > 0)
	{
		return false;
	}

	return true;
}

bool aimbotFeature::IsEnableSilent(bool silent, int silentfov, int silenthitchance, int silentstartbullet)
{
	if (FaceIt)
		return false;

	bool ret = false;
	if (silent && silentfov > 0)
	{
		ret = true;
		if (silenthitchance == 0)
			ret = false;
		else
		{
			if (silentstartbullet > 0)
				if (silentstartbullet - 1 > iShotsFired)
					ret = false;

		}
	}

	if (ret)
		ret = CanShoot();


	return ret;
}

bool aimbotFeature::IsEnableRCS(int rcsx, int rcsy)
{
	bool Ret = false;

	RCS_X = rcsx;
	RCS_Y = rcsy;

	bool CheckPistol = (weapon_type == (int)weaponTypes::pistols) ? true : iShotsFired > 1;

	if ((RCS_X > 0 || RCS_Y > 0) && CheckPistol)
		Ret = true;
	else
		Ret = false;

	return Ret;
}

bool aimbotFeature::GetBestTarget(bool _CheckSilent)
{
	float BestFov = _CheckSilent ? GSilentFov : GFov / 3.f;
	int _iBestTarget = -1;
	if (Functions::is_bad_ptr(pLocalPlayer)) return false;
	if (BestFov > 0.1f)
	{
		if (FovPos == 2)
			BestFov = FLT_MAX;

		MyEyeAng = pLocalPlayer->m_vecEye();

		if (!EntityAim)
		{
			for (int i = 0; i < interfaceManager::iengine->GetMaxClients(); i++)
			{
				cBaseEntity* ent = (cBaseEntity*)interfaceManager::ientitylist->getClientEntity(i);

				if (Functions::is_bad_ptr(ent))
					continue;
				cBasePlayer* CheckEntity = (cBasePlayer*)ent;
				if (!pLocalPlayer->canSee(CheckEntity))
					continue;

				if (CheckEntity->nDormant())
					continue;

				if (CheckEntity->m_iHealth() <= 0)
					continue;
			
				if (CheckEntity == pLocalPlayer)
					continue;
				bool isSameTeam = CheckEntity->sameTeam(pLocalPlayer);
				if (!Team && isSameTeam)
					continue;

				if (!Enemies &&  !isSameTeam)
					continue;


				if (!(CheckEntity->m_fFlags() & FL_ONGROUND) && JumpEnemyCheck)
					continue;

				if (_CheckSilent ? IsSilentNearest : IsNearest)
				{
					for (int j(0); j < 17; j++)
					{
						Vector vecHitBox = CheckEntity->hitbox(j);

						if (!pLocalPlayer->canSee(CheckEntity) && WallCheck)
							continue;

						float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

						if (_Fov < BestFov)
						{
							BestFov = _Fov;
							_iBestTarget = i;
							pBestTarget = CheckEntity;
							break;
						}
					}
				}
				else
				{
					int _HitBox = _CheckSilent ? SilentHitBox : HitBox;
					if (_HitBox == 3)
						_HitBox = 4;

					Vector vecHitBox = CheckEntity->hitbox(_HitBox);

					if (!pLocalPlayer->canSee(CheckEntity) && WallCheck)
						continue;

					float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

					if (_Fov < BestFov)
					{
						BestFov = _Fov;
						_iBestTarget = i;
						pBestTarget = CheckEntity;
					}
				}
			}
		}
		else
		{
			for (int EntIndex = 0; EntIndex < interfaceManager::ientitylist->getHighestEntityIndex(); EntIndex++)
			{
				cBaseEntity* pEntity = (cBaseEntity*)interfaceManager::ientitylist->getClientEntity(EntIndex);

				if (Functions::is_bad_ptr(pEntity))
					continue;
				if (pEntity->m_ClientClass()->m_ClassID != classid::CCSPlayer) 
					continue;


				const model_t* pModel = pEntity->GetModel();

				if (pModel)
				{
					const char* pModelName = interfaceManager::imodelinfo->GetModelName(pModel);

					if (pModelName)
					{

						std::string md = pModelName;

						if (md == EntityTargetName)
						{
							Vector vSrc = pLocalPlayer->m_vecEye();
							Vector vEnd = pEntity->m_vecEye();

							float fov = CalcFOV(FovStartAng, MyEyeAng, vEnd);
							if (fov < BestFov)
							{
								BestFov = fov;
								_iBestTarget = EntIndex;
								pBestTarget = (cBasePlayer*)pEntity;
							}
						}
					}
				}

			}
		}
	}

	if (_CheckSilent)
	{
		iSilentBestTarget = _iBestTarget;
		if (iSilentBestTarget == -1)
			return false;
		else
			return true;
	}
	else
	{
		iBestTarget = _iBestTarget;
		if (iBestTarget == -1)
			return false;
		else
			return true;
	}
	return true;
}
bool aimbotFeature::GetBestHitBox(bool _CheckSilent, bool CheckBackTrack)
{
	if (!CheckBackTrack)
		if (Functions::is_bad_ptr(pBestTarget))
			return false;

	float BestFov = _CheckSilent ? GSilentFov : GFov / 3.f;
	int HiddenHitBoxs = 0;
	int _BestHitBox = -1;
	Vector _BestHitBoxPos = Vector(0, 0, 0);

	if (BestFov > 0.1f)
	{
		if (FovPos == 2)
			BestFov = FLT_MAX;

		MyEyeAng = pLocalPlayer->m_vecEye();
		Vector vecHitBox = Vector(0, 0, 0);

		if (!EntityAim)
		{
			if (_CheckSilent ? IsSilentNearest : IsNearest)
			{
				for (int i(0); i < 7; i++)
				{
					if (!CheckBackTrack)
					{
						vecHitBox = pBestTarget->hitbox(i);

						if (!pLocalPlayer->canSee(pBestTarget, i) && WallCheck)
						{
							HiddenHitBoxs++;
							continue;
						}
					}
					float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

					if (_Fov < BestFov)
					{
						BestFov = _Fov;
						_BestHitBox = i;
						_BestHitBoxPos = vecHitBox;
					}
				}
				if (HiddenHitBoxs > 6)
				{
					for (int i(7); i < 17; i++)
					{
						if (!CheckBackTrack)
						{
							vecHitBox = pBestTarget->hitbox(i);
							if (!pLocalPlayer->canSee(pBestTarget, i) && WallCheck)
								continue;
						}
						//else
						//	headPositions[iBackTrackbestTarget][iBackTrackBestSimTime].AimBackTrackHitBoxes[i];

						float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

						if (_Fov < BestFov)
						{
							BestFov = _Fov;
							_BestHitBox = i;
							_BestHitBoxPos = vecHitBox;
						}
					}
				}
			}
			else
			{
				int _HitBox = _CheckSilent ? SilentHitBox : HitBox;

				if (_HitBox == 3)
					_HitBox = 4;

				_BestHitBox = _HitBox;

				if (!CheckBackTrack)
					_BestHitBoxPos = pBestTarget->hitbox(_HitBox);
			}

		}
		else
		{
			for (int EntIndex = 0; EntIndex < interfaceManager::ientitylist->getHighestEntityIndex(); EntIndex++)
			{
				cBaseEntity* ent = (cBaseEntity*)interfaceManager::ientitylist->getClientEntity(EntIndex);

				if (Functions::is_bad_ptr(ent))
					continue;
				if (ent->m_ClientClass()->m_ClassID != classid::CCSPlayer)
					continue;
				cBasePlayer* pEntity = (cBasePlayer*)ent;

				const model_t* pModel = pEntity->GetModel();

				if (pModel)
				{
					const char* pModelName = interfaceManager::imodelinfo->GetModelName(pModel);

					if (pModelName)
					{

						std::string md = pModelName;

						if (md == EntityTargetName)
						{
							Vector vSrc = pLocalPlayer->m_vecEye();
							Vector vEnd = pEntity->m_vecEye();

							float fov = CalcFOV(FovStartAng, MyEyeAng, vEnd);
							if (fov < BestFov)
							{
								BestFov = fov;
								_BestHitBox = 1;
								_BestHitBoxPos = vEnd;
							}
						}
					}
				}

			}
		}

		if (_CheckSilent)
			iLastBestHitBox = _BestHitBox;
		else
			iLastSilentBestHitBox = _BestHitBox;

		if (FovPos == 2)
		{
			float dy = Game::m_iHeight / Game::m_FOV;
			float dx = Game::m_iWidth / Game::m_FOV;

			float iFovVal = 0;
			if (_CheckSilent)
				iFovVal = dx * GSilentFov;
			else
				iFovVal = dx * (GFov / 3.f);

			float base_fov = pow(iFovVal + 30, 2) * Game::m_FOV;;
			BestFov = (base_fov / (pLocalPlayer->hitbox(0).DistTo(_BestHitBoxPos) * Game::m_FOV));
			float fov = CalcFOV(FovStartAng, MyEyeAng, _BestHitBoxPos);
			fov += fov / 8.f;

			TestSF = fov;

			if (fov > (BestFov / 10.f))
				_BestHitBox = -1;
		}
	}
	if (_CheckSilent)
	{
		iSilentBestHitBox = _BestHitBox;
		SilentBestHitBoxPos = _BestHitBoxPos;

		SilentPreVec = CalculateAngle(MyEyeAng, SilentBestHitBoxPos);

		if (iSilentBestHitBox == -1)
			return false;
		else
			return true;
	}
	else
	{
		iBestHitBox = _BestHitBox;
		BestHitBoxPos = _BestHitBoxPos;

		PreVec = CalculateAngle(MyEyeAng, BestHitBoxPos);

		if (iBestHitBox == -1)
			return false;
		else
			return true;
	}
}

void aimbotFeature::CalcFinalVecRcs(bool _CheckSilent)
{
	if (_CheckSilent)
		SilentFinalVec = SilentPreVec - ((AimPunchAngle * (Vector(100.f, 100.f, 0) / 100.f)) * 2.f);
	else
		FinalVec = PreVec - (AimPunchAngle * Vector(RCS_X / 50.f, RCS_Y / 50.f, 0));
}

float aimbotFeature::CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd)
{
	Vector vAng, vAim;

	vAng = CalculateAngle(vSrc, vEnd);
	MakeVector(viewangles, vAim);
	MakeVector(vAng, vAng);

	return Rad2Deg(acos(vAim.Dot(vAng)) / vAim.LengthSqr());
}

void aimbotFeature::MakeVector(const Vector& vIn, Vector& vOut)
{
	float pitch = Deg2Rad(vIn.x);
	float yaw = Deg2Rad(vIn.y);
	float temp = cos(pitch);

	vOut.x = -temp * -cos(yaw);
	vOut.y = sin(yaw) * temp;
	vOut.z = -sin(pitch);
}

void aimbotFeature::StandeloneRCS(CUserCmd* pCmd)
{
	if ((pCmd->buttons & IN_ATTACK) && CanRCS && CanRCSStandelone)
	{
		
		Vector AimPunch = (AimPunchAngle * (Vector(RCS_X, RCS_Y, 0) / 100.f)) * 2.f;
		Vector StartPunch = pCmd->viewangles;
		Vector EndPunch = OldStandRCS - AimPunch;
		Vector BufPunch = StartPunch + EndPunch;
		Vector delta = BufPunch - pCmd->viewangles;
		BufPunch = pCmd->viewangles + (delta * (min(1.f, (fabsf(powf(0.6f, 0.4f) - 1.f) / delta.Length() * 4.f))));
		Functions::ClampAngles(BufPunch);
		pCmd->viewangles = BufPunch;
		interfaceManager::iengine->SetViewAngles(&pCmd->viewangles);
		OldStandRCS = AimPunch;
	}
	else
		OldStandRCS = (AimPunchAngle * (Vector(RCS_X, RCS_Y, 0) / 100.f)) * 2.f;
}

Vector aimbotFeature::CalculateAngle(const Vector& in, Vector out)
{
	Vector ret = Vector();
	Vector delta = in - out;
	double hyp = delta.Length2D();
	ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
	ret.x = (atan(delta.z / hyp) * 57.295779513082f);
	ret[2] = 0.00;

	if (delta.x >= 0.0)
		ret.y += 180.0f;
	return ret;
}

float aimbotFeature::Rad2Deg(float x)
{
	return (x * (180.0f / M_PI));
}

float aimbotFeature::Deg2Rad(float x)
{
	return (x * (M_PI / 180.0f));
}

bool LastShoot = false;
float FireDelay = 0;
void AngleVectors(const Vector& vAngles, Vector& vForward)
{
	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(vAngles[1]));
	cy = cos(DEG2RAD(vAngles[1]));

	sp = sin(DEG2RAD(vAngles[0]));
	cp = cos(DEG2RAD(vAngles[0]));

	vForward.x = cp * cy;
	vForward.y = cp * sy;
	vForward.z = -sp;
}
void aimbotFeature::drawAimbotFOV() {
	if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;
	if (Functions::is_bad_ptr(pLocalPlayer)) return;
	if (Functions::is_bad_ptr(pLocalWeapon)) return;
	cBasePlayer* pPlayer = (cBasePlayer*)pLocalPlayer;
	if (Functions::is_bad_ptr(pPlayer)) return;
	
	if (Functions::is_bad_ptr(pPlayer))
		return;
	if ((variables::esp::other::drawfov || variables::esp::other::drawsilentfov) && pLocalPlayer)
	{
		crashhandler.setDebug("AIMBOT_FOV_1");
		cBasePlayer* pPlayer = (cBasePlayer*)pLocalPlayer;
		crashhandler.setDebug("AIMBOT_FOV_2");
		if (Functions::is_bad_ptr(pPlayer))
			return;
		crashhandler.setDebug("AIMBOT_FOV_3");
		float dy = Game::m_iHeight / Game::m_FOV;
		float dx = Game::m_iWidth / Game::m_FOV;
		crashhandler.setDebug("AIMBOT_FOV_4");
		float x = Game::m_iWidth / 2.f;
		float y = Game::m_iHeight / 2.f;
		color silent_color = color(255, 0, 0, 50);
		color main_color = color(255, 255, 255, 50);
		crashhandler.setDebug("AIMBOT_FOV_5");
		if (AimWorking) {
			main_color = color(255, 255, 255, 255);
			silent_color = color(255, 0, 0, 255);
		}
		crashhandler.setDebug("AIMBOT_FOV_6");
		if (FovPos != 2)
		{
			crashhandler.setDebug("AIMBOT_FOV_7");
			if (!Functions::is_bad_ptr(pPlayer) && !Functions::is_bad_ptr(pLocalWeapon) && pPlayer->m_iHealth() > 0)
			{
				if (FovPos == 0)
				{
					crashhandler.setDebug("AIMBOT_FOV_8");
					if (variables::esp::other::drawfov)
						paint->circleOutline(x, y, (dy * GFov / 3.f), main_color);
					if (CanSilent && variables::esp::other::drawsilentfov)
						paint->circleOutline(x, y, (dy * GSilentFov), silent_color);
					crashhandler.setDebug("AIMBOT_FOV_9");
				}
				else if (FovPos == 1)
				{
					crashhandler.setDebug("AIMBOT_FOV_10");
					if (!Functions::is_bad_ptr(pLocalPlayer)) {
						Vector punchAngle = (pLocalPlayer->m_aimPunchAngleV() * (Vector(100, 100, 0) / 100.f));

						Vector2D pos = Vector2D(
							x - (dx * (punchAngle.y)),
							y + (dy * (punchAngle.x)));
						crashhandler.setDebug("AIMBOT_FOV_11");
						if (variables::esp::other::drawfov)
							paint->circleOutline(pos.x, pos.y, (dy * GFov / 3.f), main_color);
						if (CanSilent && variables::esp::other::drawsilentfov)
							paint->circleOutline(pos.x, pos.y, (dy * GSilentFov), silent_color);
						crashhandler.setDebug("AIMBOT_FOV_12");
					}
				}
			}
		}
		if (FovPos == 2 && pOldBestTarget)
		{
			crashhandler.setDebug("AIMBOT_FOV_13");
			if (variables::esp::other::drawfov && iLastBestHitBox != -1 && pOldBestTarget->m_iHealth() > 0)
			{
				float base_fov = pow((dx * GFov / 3.f) + 30, 2) * Game::m_FOV;
				float iFov = (base_fov / (pLocalPlayer->hitbox(0).DistTo(BestHitBoxPos) * Game::m_FOV));
				crashhandler.setDebug("AIMBOT_FOV_14");
				Vector m_vAimBestHitboxScreen;

				if (Functions::worldToScreen(BestHitBoxPos, m_vAimBestHitboxScreen))
					paint->circleOutline(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y, iFov / (Game::resolution_scale_factor), main_color);
				crashhandler.setDebug("AIMBOT_FOV_15");
			}
			if (variables::esp::other::drawsilentfov && iLastSilentBestHitBox != -1 && pOldBestTarget->m_iHealth() > 0 && CanSilent)
			{
				crashhandler.setDebug("AIMBOT_FOV_16");
				float base_fov = pow((dx * GSilentFov) + 30, 2) * Game::m_FOV;
				float iFov = (base_fov / (pLocalPlayer->hitbox(0).DistTo(SilentBestHitBoxPos) * Game::m_FOV));

				Vector m_vAimBestHitboxScreen;

				if (Functions::worldToScreen(SilentBestHitBoxPos, m_vAimBestHitboxScreen) && CanSilent)
					paint->circleOutline(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y, iFov / (Game::resolution_scale_factor), silent_color);
				crashhandler.setDebug("AIMBOT_FOV_17");
			}
		}
	}
}
bool __declspec(noinline) aimbotFeature::CanFire(Vector mAngle, CUserCmd* pCmd, cBaseEntity* BaseEnt, int BestInd, cBasePlayer* Local, bool AllHitGroup)
{
	if (BestInd != -1 && BaseEnt)
	{
		trace_t Trace;
		Ray_t Ray;
		CTraceFilter Filter;

		Vector vecS = Local->m_vecOrigin() + Local->m_vecViewOffset();
		Vector vecForvard;
		Vector vAngle = Vector(pCmd->viewangles.x + (Local->m_aimPunchAngleV().x * 2),
			pCmd->viewangles.y + (Local->m_aimPunchAngleV().y * 2), 0);

		AngleVectors(vAngle, vecForvard);
		vecForvard *= 8000.0f;

		Ray.Init(vecS, vecS + vecForvard);

		Filter.pSkip = Local;
		interfaceManager::itrace->TraceRay(Ray, (CONTENTS_HITBOX | CONTENTS_MONSTER | CONTENTS_DEBRIS | CONTENTS_MOVEABLE | CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_GRATE), &Filter, &Trace);

		auto CheckEnableHBox = [&](int HBox) -> bool
		{
			return true;
		};

		 
		if (std::string(Trace.surface.name).find("glass") != std::string::npos ||
			std::string(Trace.surface.name).find("GLASS") != std::string::npos ||
			std::string(Trace.surface.name).find("Glass") != std::string::npos)
		{

			trace_t New_Trace;
			Ray_t New_Ray;
			CTraceFilter New_Filter;

			New_Ray.Init(Trace.endpos, vecS + vecForvard);

			New_Filter.pSkip = Trace.hit_entity;
			interfaceManager::itrace->TraceRay(New_Ray, (CONTENTS_HITBOX | CONTENTS_MONSTER | CONTENTS_DEBRIS | CONTENTS_MOVEABLE | CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_GRATE), &New_Filter, &New_Trace);

			if (New_Trace.hit_entity == BaseEnt && (AllHitGroup ? true && New_Trace.hitgroup != 0 : CheckEnableHBox((New_Trace.hitgroup))))
				return true;
		}
		else
			if (Trace.hit_entity == BaseEnt && (AllHitGroup ? true && Trace.hitgroup != 0 : CheckEnableHBox((Trace.hitgroup))))
				return true;

		return false;
	}
	return false;

}


Vector _OldAimPunch = Vector(0, 0, 0);

Vector AngleVector(Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(3.141592654f));
	auto cy = cos(meme.y / 180.f * static_cast<float>(3.141592654f));

	auto sp = sin(meme.x / 180.f * static_cast<float>(3.141592654f));
	auto cp = cos(meme.x / 180.f * static_cast<float>(3.141592654f));

	return Vector(cp * cy, cp * sy, -sp);
}

float DistancePointToLine(Vector Point, Vector LineOrigin, Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

void GetHitBoxSkeleton(int nHitBoxOne, int nHitBoxTwo, cBasePlayer* pEntity, Vector* vOut)
{
	vOut[0] = pEntity->hitbox(nHitBoxOne);
	vOut[1] = pEntity->hitbox(nHitBoxTwo);
}

void aimbotFeature::BacktrackCreateMove(CUserCmd* pCmd)
{
	iBackTrackbestTarget = -1;

	
	if (Backtrack  && BacktrackTicks)
	{
		float bestFov = FLT_MAX;
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (Functions::is_bad_ptr(local)) return;
		player_info_t info;
		for (int i = 0; i < interfaceManager::iengine->GetMaxClients(); i++)
		{
			auto entity = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(i);

			if (Functions::is_bad_ptr(entity) || Functions::is_bad_ptr(local))
				continue;

			if (entity == local)
				continue;

			if (!interfaceManager::iengine->GetPlayerInfo(i, &info))
				continue;

			if (entity->nDormant())
				continue;
			bool isSameTeam = entity->sameTeam(local);

			if (!Team && isSameTeam)
				continue;

			if (!Enemies && !isSameTeam)
				continue;

			if (entity->m_iHealth() > 0)
			{
				float simtime = entity->m_flSimulationTime();
				Vector hitboxPos = entity->hitbox(0 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 16 & 17 & 18 & 19 & 10 & 11);
				if (BacktrackTicks != 0)
				{
					headPositions[i][pCmd->command_number % BacktrackTicks].hitboxPos = hitboxPos;
					headPositions[i][pCmd->command_number % BacktrackTicks].simtime = simtime;
					entity->SetupBones(headPositions[i][pCmd->command_number % BacktrackTicks].boneMatrix, 128, 0x00000100, interfaceManager::iglobal->curtime);
					headPositions[i][pCmd->command_number % BacktrackTicks].newMatrix = true;
					Vector ViewDir = AngleVector(pCmd->viewangles + (local->m_aimPunchAngleV() * 2.f));
					float FOVDistance = DistancePointToLine(hitboxPos, local->m_vecEye(), ViewDir);

					if (bestFov > FOVDistance)
					{
						bestFov = FOVDistance;
						iBackTrackbestTarget = i;
						pBestBacktrTarget = entity;
					}
				}
			}
		}

		float bestTargetSimTime = 0;
		if (iBackTrackbestTarget != -1)
		{
			float tempFloat = FLT_MAX;

			Vector ViewDir = AngleVector(pCmd->viewangles + (local->m_aimPunchAngleV() * 2.f));

			for (int t = 0; t < BacktrackTicks;++t)
			{
				float tempFOVDistance = DistancePointToLine(headPositions[iBackTrackbestTarget][t].hitboxPos, local->m_vecEye(), ViewDir);

				if (tempFloat > tempFOVDistance && headPositions[iBackTrackbestTarget][t].simtime > interfaceManager::iglobal->curtime - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[iBackTrackbestTarget][t].simtime;
					iBackTrackBestSimTime = bestTargetSimTime;
				}
			}

			if (pCmd->buttons & IN_ATTACK)
			{
				pCmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
			}
		}
	}
}



