#pragma once
#include "painting.h"
#include "Game.h"
#include "interfaces.h"
#include "Hooks.h"
#include "esp.h"
#include "Aimbot.h"
#include "edgeGui.h"
#include "Nightmode.h"
#include "skinchanger.h"
#include "spectatorlist.h"
#include "deathmarkers.h"
#include "damage.h"
#include "Chams.h"
#include "log.h"
#include "Que.h"
#include "Misc.h"
#include "triggerbot.h"
#include "debugmanager.h"
#include "radar.h"
#include "crashhandler.h"
#include "whocansee.h"
#include "viewmodifier.h"
#include "glow.h"
#include "RECStatistics.h"
#include "Asus.h"
#include "grenadehelper.h"
#include "InventoryChanger.h"
/*
class edgeWeapon
{
public:
	int ammo = 0;
	int reserve = 0;
	std::string name = "";
};
class edgeEntity
{
public:
	void syncVariables(cBaseEntity* local, cBaseEntity* ent, cBasePlayer* pla = nullptr, ) {
		if (!Functions::is_bad_ptr(ent)) {
			m_originPosition = ent->m_vecOrigin();
			m_classID = ent->m_ClientClass()->m_ClassID;
			m_iTeam = ent->m_iTeamNum();
			m_nModelIndex = ent->m_nModelIndex();
			m_flSimulationTime = ent->m_flSimulationTime();
			m_vecMaxs = ent->m_vecMaxs();
			m_vecMins = ent->m_vecMins();
			m_fFlags = ent->m_fFlags();
			m_bSpotted = ent->m_bSpotted();
			m_iIndex = ent->m_iIndex();
			m_hOwnerEntity = ent->m_hOwnerEntity();
			m_vecViewOffset = ent->m_vecViewOffset();
			m_nTickBase = ent->m_nTickBase();
			m_bSpottedbyMask = ent->m_bSpottedbyMask();
			m_vecEye = ent->m_vecEye();
			m_hActiveWeapon = ent->m_hActiveWeapon();
			//cBaseEntity* ownerEntity();
			movetype = ent->movetype();
			m_visibleByLocal = local->canSee(ent);
			nDormant = ent->nDormant();
			CanFire = ent->CanFire();
			
			matrix3x4_t boneMatrix[MAXSTUDIOBONES];
			if (ent->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
				for (int bone = 0; bone < 128; bone++) {
					if (bone > 0 && bone < MAXSTUDIOBONES) {
						m_vecBone[bone] =  boneMatrix[bone].at(3);
					}
				}
				auto studio_model = interfaceManager::imodelinfo->GetStudiomodel(ent->GetModel());
				if (studio_model) {
					for (int id = 0; id < 12; id++) {
						auto hitbox_t = studio_model->GetHitboxSet(0)->GetHitbox(id);
						if (hitbox_t) {
							
							Vector	min = Vector{};
							Vector	max = Vector{};

							Functions::VectorTransform(hitbox_t->bbmin, boneMatrix[hitbox_t->bone], min);
							Functions::VectorTransform(hitbox_t->bbmax, boneMatrix[hitbox_t->bone], max);

							hitbox[id] = Vector{ (min.x + max.x) / 2.0f,
												 (min.y + max.y) / 2.0f,
												 (min.z + max.z) / 2.0f };
						}
					}
				}
			}
		}
		if (Functions::is_bad_ptr(pla)) {
			m_iHealth = pla->m_iHealth();
			m_iMaxHealth = pla->m_iMaxHealth();
		}
	}
private:
	Vector m_originPosition = Vector{};

	classid m_classID;
	int m_iMaxHealth = 0;
	int m_iTeam = 0;
	int m_iHealth = 0;
	int32_t m_nModelIndex = 0;
	float m_flSimulationTime = 0;
	Vector m_vecMins = Vector{};
	Vector m_vecMaxs = Vector{};
	int m_fFlags = 0;
	bool m_bSpotted = false;
	int m_iIndex = 0;
	HANDLE m_hOwnerEntity;
	Vector m_vecViewOffset;
	int m_nTickBase = 0;
	int32_t m_bSpottedbyMask = 0;
	Vector m_vecEye = Vector{};
	cBaseCombatWeapon* m_hActiveWeapon;
	int movetype = 0;
	bool m_visibleByLocal = false;
	Vector m_vecBone[12];
	Vector hitbox[12];
	bool CanFire = false;
	bool nDormant = true;
	
};*/
class EdgeAimFramework
{
public:
	void prePainting() {

	}
	void panelPainting() {
		crashhandler.setDebug("PAINT_BEGIN");
		if (variables::debug::main1) {

			if (variables::debug::main2) {
				crashhandler.setDebug("ESP_LOOP_BEGIN");
				esp.loop();
				crashhandler.setDebug("ESP_LOOP_FINISH");
			}
			if (variables::debug::main22) {
				crashhandler.setDebug("MARKERS_BEGIN");
				markers.draw();
				crashhandler.setDebug("MARKERS_FINISH");



				crashhandler.setDebug("DAMAGES_BEGIN");
				damages.draw();
				crashhandler.setDebug("DAMAGES_FINISH");


				crashhandler.setDebug("AIMBOT_FOV_BEGIN");
				aimbot.drawAimbotFOV();
				crashhandler.setDebug("AIMBOT_FOV_FINISH");


				crashhandler.setDebug("SPEC_BEGIN");
				spectator.loop();
				crashhandler.setDebug("SPEC_FINISH");


				whocansee.loop();


				if (variables::misc::grenade)
					helper.loop();

				crashhandler.setDebug("RADAR_BEGIN");
				radar.loop();
				crashhandler.setDebug("RADAR_FINISH");


				crashhandler.setDebug("GUI_BEGIN");
				
				gui.loop();
				

				crashhandler.setDebug("GUI_FINISH");
			}
		}
		
		crashhandler.setDebug("DEBUG_BEGIN");
		debugmanager.calculateDebugTestResults(&variables::debug::fpsData);
		crashhandler.setDebug("DEBUG_FINISH");
		crashhandler.setDebug("DEBUG_WARNING_BEGIN");
		debugmanager.runWarning();
		crashhandler.setDebug("DEBUG_WARNING_FINISH");
		crashhandler.setDebug("PAINT_PLACEHOLDER_RECT_BEGIN");
		paint->rectangle(0, 0, 2, 2, color(0, 0, 0, 0));
		crashhandler.setDebug("PAINT_PLACEHOLDER_RECT_FINISH");

		crashhandler.setDebug("PAINT_END");
		statistics.checkSync();
	}
	void fireevent(IGameEvent* event) {
		crashhandler.setDebug("MARKERS_UPDATE_BEGIN");
		markers.update(event);
		crashhandler.setDebug("MARKERS_UPDATE_FINISH");

		crashhandler.setDebug("DAMAGES_UPDATE_BEGIN");
		damages.update(event);
		crashhandler.setDebug("DAMAGES_UPDATE_BEGIN");
		statistics.catchEvents(event);
	}
	
	void viewmod(CViewSetup* view) {
		viewmodd.run(view);
	}
	void gameMove(CUserCmd* cmd, float sample, bool& bSendPacket) {
		crashhandler.setDebug("CMDMOVE_BEGIN");
		if (!variables::debug::main26) return;
		crashhandler.setDebug("CMDMOVE_AIMBOT_BEGIN_PARAMS");
		aimbot.SetMainParams();
		crashhandler.setDebug("CMDMOVE_AIMBOT_FINISH_PARAMS");
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (variables::debug::main27) {
			if (!variables::gui::bShowMainGui) {
				if (variables::debug::main28) {
					crashhandler.setDebug("CMDMOVE_AIMBOT_BEGIN_BT");
					aimbot.BacktrackCreateMove(cmd);
					crashhandler.setDebug("CMDMOVE_AIMBOT_FINISH_BT");
					if (aimbot.Enable) {
						crashhandler.setDebug("CMDMOVE_AIMBOT_BEGIN_CM");
						aimbot.CreateMove(bSendPacket, sample, cmd);
						crashhandler.setDebug("CMDMOVE_AIMBOT_FINISG_CM");
					}
					
				}
				if (variables::debug::main29) {
					crashhandler.setDebug("CMDMOVE_TRIG_BEGIN");



					//trigger.Loop(cmd);
					crashhandler.setDebug("CMDMOVE_TRIG_FINISH");
					crashhandler.setDebug("CMDMOVE_MISC_BEGIN");




					misc.Loop(cmd);
					crashhandler.setDebug("CMDMOVE_MISC_FINISH");
				}


			}
			else {
				crashhandler.setDebug("CMDMOVE_CONTROLS_DISABLED_BEGIN");



				cmd->buttons &= ~IN_ATTACK;



				crashhandler.setDebug("CMDMOVE_CONTROLS_DISABLED_FINISH");
			}
			crashhandler.setDebug("CMDMOVE_RADAR_BEGIN");
			radar.cmdUpdate(cmd);
			crashhandler.setDebug("CMDMOVE_RADAR_FINISH");
			if (Que::NextFullupdate) {
				Functions::fullupdate();
				Que::NextFullupdate = false;
			}
		}
		crashhandler.setDebug("CMDMOVE_FINISH");
	}
	void doposteffects() {
		glow.loop();
	}
	void drawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) {
		if (!chams.bInitialized)
			chams.Initialize();
		if (variables::debug::main30) {
			
			chams.loopDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
			
		}
	}
	void sceneend() {
		crashhandler.setDebug("SCENE_BEGIN");
		crashhandler.setDebug("CHAMS_1_INITIALISE_BEGIN");
		
		crashhandler.setDebug("CHAMS_1_INITIALISE_FINISH");
		if (variables::debug::main31) {
			crashhandler.setDebug("CHAMS_1_BEGIN");
			chams.loopSceneEnd();
			crashhandler.setDebug("CHAMS_1_FINISH");
		}
		crashhandler.setDebug("SCENE_FINISH");
	}
	void playerpostupdate(cBasePlayer* this_) {
		
	}
	void framenetupdatepostdataupdatestart(cBasePlayer* local) {
		crashhandler.setDebug("FS_BEGIN");
		crashhandler.setDebug("FS_NM_BEGIN");
		nightmode.Peform();
		asus.Peform();
		if (Que::NextFullupdate) {
			Functions::fullupdate();
			invChanger.createItem();
			Que::NextFullupdate = false;
		}
		skinchanger.Loop(local);
		crashhandler.setDebug("FS_FINISH");
	}
	void destroyCheat() {
		Hooks::destroyHooks();
		chams.Clean();
		markers.Clean();
		damages.Clean();
		logger.EndLog();
	
	}
	void setupCheat(LPVOID reserve) {
		crashhandler.setDebug("CHEAT_SETUP_BEGIN");
		crashhandler.setDebug("CHEAT_RETRIVE_DATA_BEGIN");
		Game::retriveGameData();
		crashhandler.setDebug("CHEAT_RETRIVE_DATA_FINISH");
		crashhandler.setDebug("CHEAT_RETRIVE_INTERFACES_BEGIN");
		interfaceManager::findInterfaces();
		crashhandler.setDebug("CHEAT_RETRIVE_INTERFACES_FINISH");
		crashhandler.setDebug("CHEAT_POST_RET_BEGIN");
		Game::postRetrive();
		crashhandler.setDebug("CHEAT_POST_RET_FINISH");
		crashhandler.setDebug("CHEAT_SCREENSIZE_BEGIN");
		interfaceManager::iengine->GetScreenSize(Game::m_iWidth, Game::m_iHeight);
		while (true) {
			interfaceManager::iengine->GetScreenSize(Game::m_iWidth, Game::m_iHeight);
			if (Game::m_iWidth > 200 || Game::m_iHeight > 200)
				break;
		}
		crashhandler.setDebug("CHEAT_SCREENSIZE_FINISH");
		crashhandler.setDebug("CHEAT_POSTRET_BEGIN");
		Game::postRetriveLater();
		crashhandler.setDebug("CHEAT_POSTRET_FINISH");
		crashhandler.setDebug("CHEAT_HOOKS_BEGIN");
		statistics.syncSavedStatistics();
		Hooks::setupHooks(reserve);
		crashhandler.setDebug("CHEAT_HOOKS_FINISH");
		crashhandler.setDebug("CHEAT_SETUP_FINISH");
	}
	aimbotFeature aimbot;
	Triggerbot trigger;
	espFeature esp;
	edgeGUI gui;
	Misc misc;
	Spectators spectator;
	WhoCanSee whocansee;
	inventoryChanger invChanger;
	radarFeature radar;
	Chams chams;
	Markers markers;
	Damage damages;
	iglow glow;
	debugManager debugmanager;
	viewmodifier viewmodd;
	RECStatistics statistics;
	grenadeHelper helper;
	std::string userName = xorStr("unknown");
	int cheatVersion = 1.0;
	HANDLE exceptionHandle;
};
extern EdgeAimFramework edgeaim;