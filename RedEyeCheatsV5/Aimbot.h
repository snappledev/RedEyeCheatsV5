#pragma once
#include "cBaseEntity.h"
#include "cBasePlayer.h"
#include "cCSPlayer.h"
#include "Interfaces.h"
#include "cUserCmd.h"
#include "matrix3x4.h"
#include <math.h>
#include <chrono>


#define _180_PI 57.324840764331210191082802547771
#define PI 3.14159265 

//using namespace Global;

namespace Engine
{
	class CBaseEntity;
	class CPlayer;
	class CBaseWeapon;
}

using namespace Engine;


extern int SelectedWeapon;

class IAimTimer
{
protected:
	virtual void Update(float _CurTime) = 0;
};

class CAimTimer : public IAimTimer
{
public:
	struct _STimer
	{
		bool Enable = false;
		bool Active = false;
		float EndTime = 0;
	}STimer;

	CAimTimer() {}
	CAimTimer(float Delay, bool _Active = false, bool _Enable = true)
	{
		STimer.Enable = _Enable;
		STimer.Active = _Active;
		STimer.EndTime = Delay;
	}
	virtual void Update(float _CurTime)
	{
		if (STimer.EndTime < _CurTime)
			STimer.Active = false;
	}
};

class ICustomSmooth
{
protected:
	virtual float GetCurLen(Vector viewangles, Vector target) = 0;
	virtual float GetCurAngle(float Len, Vector viewangles, Vector target) = 0;
	virtual Vector GetMaxDelta(float Len, float Angl, Vector viewangles, Vector target) = 0;
};

class CCustomSmooth : public ICustomSmooth
{
public:

	float StartLen = 0;

	virtual float GetCurLen(Vector viewangles, Vector target)
	{
		float SmeshX = target.y < 0 && viewangles.y > 0 ? (viewangles.y - target.y * -1.f) : (target.y - viewangles.y);
		float SmeshY = target.x < 0 && viewangles.x > 0 ? (viewangles.x - target.x * -1.f) : (target.x - viewangles.x);

		return sqrtf(powf(SmeshX, 2.f) + powf(SmeshY, 2.f));
	}

	virtual float GetCurAngle(float Len, Vector viewangles, Vector target)
	{

		float SmeshX = (target.y - viewangles.y) * -1.f;
		float SmeshY = (target.x - viewangles.x) * -1.f;
		return atanf(SmeshY / SmeshX) * _180_PI;
	}

	virtual Vector GetMaxDelta(float Len, float Angl, Vector viewangles, Vector target)
	{
		return Vector(
			target.x + ((Len * sin(Angl * PI / 180.f)) * (viewangles.y < target.y ? -1.f : 1.f)),
			target.y + ((Len * cos(Angl * PI / 180.f)) * (viewangles.y < target.y ? -1.f : 1.f)),
			0);
	}

};

class ILegitAim
{
public:
	virtual void SetMainParams() = 0;
protected:
	virtual void BacktrackCreateMove(CUserCmd* pCmd) = 0;
	virtual bool CheckOpportWork(CUserCmd* pCmd) = 0;
	virtual bool GetBestTarget(bool CheckSilent) = 0;
	virtual bool GetBestHitBox(bool CheckSilent, bool CheckBackTrack = false) = 0;
	
	virtual void CalcAutoPistol(CUserCmd* cmd, cBasePlayer* pLocal) = 0;
	virtual void StandeloneRCS(CUserCmd* pCmd) = 0;
	virtual void CalcFinalVecRcs(bool _CheckSilent) = 0;
	virtual void MakeVector(const Vector& vIn, Vector& vOut) = 0;
	virtual void CreateAssistMove(Vector TargetAng, bool IsSilent = false) = 0;
	virtual void VixViewAng(Vector& VE) = 0;
	virtual void CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd) = 0;
	virtual void SetSelectedWeapon(bool MenuCheck = true) = 0;

	virtual bool __declspec(noinline) CanFire(Vector mAngle, CUserCmd* pCmd, cBaseEntity* BaseEnt, int BestInd, cBasePlayer* Local, bool AllHitGroup) = 0;
	virtual float CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd) = 0;
	virtual Vector Smooth(Vector& viewangles, Vector target, float factor, bool silent) = 0;
	virtual Vector PlayerAnglToScreen(Vector Angl) = 0;
	virtual Vector CalculateAngle(const Vector& in, Vector out) = 0;
	virtual float Rad2Deg(float x) = 0;
	virtual float Deg2Rad(float x) = 0;
	virtual bool IsNonAimWeapon() = 0;
	virtual bool CanShoot() = 0;
	virtual bool IsEnableSilent(bool silent, int silentfov, int silenthitchance, int silentstartbullet) = 0;
	virtual bool IsEnableRCS(int rcsx, int rcsy) = 0;
};

class aimbotFeature : public ILegitAim
{
public:
	virtual void CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd);
	virtual void SetSelectedWeapon(bool MenuCheck = true);
	virtual void BacktrackCreateMove(CUserCmd* pCmd);
	
	virtual bool __declspec(noinline) CanFire(Vector mAngle, CUserCmd* pCmd, cBaseEntity* BaseEnt, int BestInd, cBasePlayer* Local, bool AllHitGroup);
	/*NO SAVE*/
	int WeaponCustomTypes = 0;
	bool ShowWeaponList = false;
	int SubTabAimSelected = 0;
	bool GDrawRcsFov = false;
	int iShotsFired = 0;
	bool CanRCSStandelone = false;
	bool CanRCS = false;
	int StandartSubSelected = 0;
	int SelectedSub = 0;
	int SelectedSubAlloc = 0;
	int SelectedSubUnAlloc = 0;
	bool CheckAimCust = false;
	bool AutoDisableAll = false;
	int weapon_type = 0;
	int weapon_id = 0;
	/*=======*/

	bool Deathmatch = false;
	bool FlashCheck = true;
	bool SmokeCheck = true;
	bool AutoFire = false;
	bool JumpCheck = false;
	bool JumpEnemyCheck = false;

	bool WallCheck = true;

	bool DrawFov = false;
	bool DrawSilentFov = false;
	bool ShowSpot = false;

	bool FaceIt = false;
	bool EntityAim = false;
	bool ShowEntitysName = false;
	std::string EntityTargetName = xorStr("<default>");

	int AimBind = VK_LBUTTON;
	bool Debug = false;
	float MouseSense = 1.7f;

	struct backtrackData
	{
		float simtime;
		Vector hitboxPos;
		matrix3x4_t boneMatrix[128];
		bool newMatrix = false;
	};

	backtrackData headPositions[64][12];

	struct CustomSub
	{
		int Idx;
		std::string Name;
		std::vector<std::string> AllocatedWeapon;
	};

	
	std::vector<CustomSub> CustomSubs;
	std::vector<std::string> UnallocatedWeapons;

	bool Enable = false;
	bool Enemies = true;
	bool Team = false;
	int key = VK_LBUTTON;
	void drawAimbotFOV();
	aimbotFeature()
	{
		CCSmooth = std::make_unique<CCustomSmooth>();
		LpCmd = nullptr;
		CCSmooth = nullptr;
		pBestTarget = nullptr;
		pOldBestTarget = nullptr;
		pLocalPlayer = nullptr;
		pLocalWeapon = nullptr;
		pBestBacktrTarget = nullptr;
	}

	cBasePlayer* pTriggerBestTarget;
	cBasePlayer* pBestTarget;
	cBasePlayer* pOldBestTarget;
	cBasePlayer* pLocalPlayer;
	cBaseCombatWeapon* pLocalWeapon;
	cBaseEntity* pBestBacktrTarget;
	int BacktrackTicks = 12;
	bool ShowBacktrack = false;
	bool Backtrack = false;
	virtual float CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd);
	virtual void SetMainParams();
private:

	CUserCmd* LpCmd;
	std::shared_ptr<CCustomSmooth> CCSmooth = nullptr;
	Vector MyEyeAng = Vector(0, 0, 0);
	Vector BestHitBoxPos = Vector(0, 0, 0);
	Vector SilentBestHitBoxPos = Vector(0, 0, 0);
	Vector FinalVec = Vector(0, 0, 0);
	Vector PreVec = Vector(0, 0, 0);
	Vector SilentFinalVec = Vector(0, 0, 0);
	Vector SilentPreVec = Vector(0, 0, 0);
	Vector FovStartAng = Vector(0, 0, 0);
	Vector AimPunchAngle = Vector(0, 0, 0);
	virtual Vector Smooth(Vector& viewangles, Vector target, float factor, bool silent);
	Vector AssistScreenPoint = Vector(0, 0, 0);
	Vector NewMouseOfstPos = Vector(0, 0, 0);
	Vector MousePos = Vector(0, 0, 0);
	Vector SmoothMaxDelta = Vector(0, 0, 0);
	Vector PlayerAnglToScreen(Vector Angl);
	virtual Vector CalculateAngle(const Vector& in, Vector out);

	Vector TempVec1 = Vector(0, 0, 0);
	Vector TempVec2 = Vector(0, 0, 0);
	Vector TempVec3 = Vector(0, 0, 0);

	CAimTimer FFDelay;
	CAimTimer TSDelay;

	int iBestTarget = 0;
	int iBestHitBox = 0;
	int iSilentBestTarget = 0;
	int iSilentBestHitBox = 0;
	int FovPos = 0;
	int iBestBone = 0;
	int CurWeaponID = 0;
	int AimStartBullet = 0;
	int AimEndBullet = -1;
	int SilentHitBox = 0;
	int HitBox = 0;
	int RCS_X = 0;
	int RCS_Y = 0;
	int iLastBestHitBox = 0;
	int iLastSilentBestHitBox = 0;
	int iBackTrackBestSimTime = 0;
	int iBackTrackbestTarget = -1;
	int AimMethod = 0;

	int SmoothMF = 0;

	float GSilentFov = 0;
	float GSmooth = 0;
	float GFov = 0;
	float CurTime = 0;
	float TSDelayTime = 0;
	float FFDelayTime = 0;

	float ScreenCenterX = 0;
	float ScreenCenterY = 0;
	float SmoothCurLen = 0;
	float SmoothCurAngle = 0;
	float SmoothProgress = 0;
	float CurAcceleration = 10.f;
	virtual float Rad2Deg(float x);

	virtual float Deg2Rad(float x);

	
	
	bool IsPistol = false;
	bool IsSniper = false;
	bool IsShotgun = false;
	bool FFAutoDelay = false;
	bool FFAutoDelayEnable = false;
	bool FFAutoDelayDisable = false;
	bool pSilentAutoDelay = false;
	bool pSilentAutoDelayEnable = false;
	bool pSilentAutoDelayDisable = false;
	bool KillStop = false;
	bool KillStopEnable = false;
	bool FFDelayOneClickEnable = false;
	bool FFDelayOCActive = false;
	bool FFDelayOCDisable = false;
	bool FFDelayEnable = false;
	bool FFDelayDisable = false;
	bool TSDelayEnable = false;
	bool CanSilent = false;
	int  SilentHitchance = 100;
	bool IsSilentNearest = false;
	bool IsNearest = false;
	

	bool AimWorking = false;
	virtual bool IsNonAimWeapon();
	virtual bool CanShoot();
	virtual bool IsEnableSilent(bool silent, int silentfov, int silenthitchance, int silentstartbullet);
	virtual bool IsEnableRCS(int rcsx, int rcsy) ;
	virtual bool CheckOpportWork(CUserCmd* pCmd);
	virtual bool GetBestTarget(bool CheckSilent);
	virtual bool GetBestHitBox(bool CheckSilent, bool CheckBackTrack = false);
	bool SetSmoothStart = false;
	bool FaceItMode = false;
	bool FastZoom = false;
	bool IsZoomed = false;
	bool IsSniperClass = false;

	
	virtual void CalcAutoPistol(CUserCmd* cmd, cBasePlayer* pLocal);
	virtual void StandeloneRCS(CUserCmd* pCmd);
	virtual void CalcFinalVecRcs(bool _CheckSilent);
	virtual void MakeVector(const Vector& vIn, Vector& vOut);
	virtual void CreateAssistMove(Vector TargetAng, bool IsSilent = false);
	virtual void VixViewAng(Vector& VE);
};
