#include "Chams.h"
#include "Interfaces.h"
#include "variables.h"
#include <iostream>
#include <fstream>
#include "Hooks.h"
#include "edgeAim.h"
void Chams::Initialize() //Very large constructor :)
{
	if (bInitialized) return;
	m_mGoldMaterial = interfaceManager::imaterial->FindMaterial(xorStr("models/inventory_items/trophy_majors/gold"), TEXTURE_GROUP_MODEL);
	m_mPlasticMaterial = interfaceManager::imaterial->FindMaterial(xorStr("models/inventory_items/trophy_majors/crystal_clear"), TEXTURE_GROUP_MODEL);
	m_mPlatinumMaterial = interfaceManager::imaterial->FindMaterial(xorStr("models/player/ct_fbi/ct_fbi_glass"), TEXTURE_GROUP_MODEL);
	m_mPlainMaterial = interfaceManager::imaterial->FindMaterial(xorStr("debug/debugambientcube"), TEXTURE_GROUP_MODEL);
	m_mFlatMaterial = interfaceManager::imaterial->FindMaterial(xorStr("debug/debugdrawflat"), TEXTURE_GROUP_MODEL);

	m_mAppliedMaterial = m_mPlainMaterial;
	m_mOutlineMaterial = m_mPlainMaterial;
	bInitialized = true;
}
void Chams::Clean()

{
	if (m_mGoldMaterial)
		m_mGoldMaterial->Release();
	if (m_mPlasticMaterial)
		m_mPlasticMaterial->Release();
	if (m_mPlatinumMaterial)
		m_mPlatinumMaterial->Release();
	if (m_mPlainMaterial)
		m_mPlainMaterial->Release();
	if (m_mFlatMaterial)
		m_mFlatMaterial->Release();
	if (m_mAppliedMaterial)
		m_mAppliedMaterial->Release();
	if (m_mOutlineMaterial) {
		m_mOutlineMaterial->Release();
	}
}
void Chams::PaintTextureSceneEnd(cBaseEntity* entity, IMaterial* material, float* color, float* xqzcolor, bool xqz)
{
	if (Functions::is_bad_ptr(material)) return;
	if (Functions::is_bad_ptr(entity)) return;
	if (xqz) {
		material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		interfaceManager::iview->SetColorModulation(xqzcolor);
		interfaceManager::irender->ForcedMaterialOverride(material);
		entity->DrawModel(0x1, 255);
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	interfaceManager::iview->SetColorModulation(color);
	interfaceManager::irender->ForcedMaterialOverride(material);
	entity->DrawModel(0x1, 255);
	interfaceManager::irender->ForcedMaterialOverride(nullptr);

}
void Chams::Sync(cBaseEntity* ent, bool& m_bEnabled, bool& m_bXQZ, float m_fColors[3], float m_fXQZColors[3])
{
	if (Functions::is_bad_ptr(ent)) return;
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local)) return;
	classid clientclass = ent->m_ClientClass()->m_ClassID;
	std::string model = interfaceManager::imodelinfo->GetModelName(ent->GetModel());
	if (clientclass == classid::CCSPlayer) {
		cBasePlayer* entity = (cBasePlayer*)ent;
		if (Functions::is_bad_ptr(entity)) return;
		
		if (entity->m_iHealth() > 0 && !entity->nDormant()) {
			bool isSameTeam = entity->sameTeam(local);
			if (!isSameTeam) {
				m_bEnabled = variables::esp::enemies::enabled && variables::esp::enemies::chams > 0;
				m_bXQZ = variables::esp::enemies::chamsxqz;
				double small_enemy_r = (double)variables::esp::enemies::chamsVisible.r() / 255.f; double small_enemy_g = (double)variables::esp::enemies::chamsVisible.g() / 255.f; double small_enemy_b = (double)variables::esp::enemies::chamsVisible.b() / 255.f;

				m_fColors[0] = small_enemy_r; m_fColors[1] = small_enemy_g; m_fColors[2] = small_enemy_b;
				double small_enemy_xqzr = (double)variables::esp::enemies::chamsInvisible.r() / 255.f; double small_enemy_xqzg = (double)variables::esp::enemies::chamsInvisible.g() / 255.f; double small_enemy_xqzb = (double)variables::esp::enemies::chamsInvisible.b() / 255.f;
				m_fXQZColors[0] = small_enemy_xqzr; m_fXQZColors[1] = small_enemy_xqzg; m_fXQZColors[2] = small_enemy_xqzb;
				if (variables::esp::enemies::chams == 1  || variables::esp::enemies::chams == 3) { m_mAppliedMaterial = m_mPlainMaterial; }
				else if (variables::esp::enemies::chams == 2) { m_mAppliedMaterial = m_mFlatMaterial; }
				else if (variables::esp::enemies::chams == 4) { m_mAppliedMaterial = m_mGoldMaterial; }
				else if (variables::esp::enemies::chams == 5) { m_mAppliedMaterial = m_mPlasticMaterial; }
				else if (variables::esp::enemies::chams == 6) { m_mAppliedMaterial = m_mPlatinumMaterial; }
				else { m_mAppliedMaterial = m_mPlainMaterial; }
				m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, (variables::esp::enemies::chams == 3));
				return;
			}
			else if (isSameTeam) {
				m_bEnabled = variables::esp::team::enabled && variables::esp::team::chams;
				m_bXQZ = variables::esp::team::chamsxqz;

				double small_team_r = (double)variables::esp::team::chamsVisible.r() / 255.f; double small_team_g = (double)variables::esp::team::chamsVisible.g() / 255.f; double small_team_b = (double)variables::esp::team::chamsVisible.b() / 255.f;

				m_fColors[0] = small_team_r; m_fColors[1] = small_team_g; m_fColors[2] = small_team_b;
				double small_team_xqzr = (double)variables::esp::team::chamsInvisible.r() / 255.f; double small_team_xqzg = (double)variables::esp::team::chamsInvisible.g() / 255.f; double small_team_xqzb = (double)variables::esp::team::chamsInvisible.b() / 255.f;
				m_fXQZColors[0] = small_team_xqzr; m_fXQZColors[1] = small_team_xqzg; m_fXQZColors[2] = small_team_xqzb;
				if (variables::esp::team::chams == 1  || variables::esp::team::chams == 3) { m_mAppliedMaterial = m_mPlainMaterial; }
				else if (variables::esp::team::chams == 2) { m_mAppliedMaterial = m_mFlatMaterial; }
				else if (variables::esp::team::chams == 4) { m_mAppliedMaterial = m_mGoldMaterial; }
				else if (variables::esp::team::chams == 5) { m_mAppliedMaterial = m_mPlasticMaterial; }
				else if (variables::esp::team::chams == 6) { m_mAppliedMaterial = m_mPlatinumMaterial; }
				else { m_mAppliedMaterial = m_mPlainMaterial; }
				m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, (variables::esp::team::chams == 3));
				return;
			}
		}
	}
	/*else if (Functions::isGrenade(model) != xorStr("")) {
		m_bEnabled = variables::esp::grenades::enabled && variables::esp::grenades::chams != 0;
		m_bXQZ = variables::esp::grenades::XQZchams;
		m_fColors[0] = 1.f; m_fColors[1] = 0.49803921568; m_fColors[2] = 0.15294117647;
		m_fXQZColors[0] = 0.4431372549f; m_fXQZColors[1] = 0.16470588235; m_fXQZColors[2] = 0.96862745098;
		if (variables::esp::grenades::chams == 1  || variables::esp::grenades::chams == 3) { m_mAppliedMaterial = m_mPlainMaterial; }
		else if (variables::esp::grenades::chams == 2) { m_mAppliedMaterial = m_mFlatMaterial; }
		else if (variables::esp::grenades::chams == 4) { m_mAppliedMaterial = m_mGoldMaterial; }
		else if (variables::esp::grenades::chams == 5) { m_mAppliedMaterial = m_mPlasticMaterial; }
		else if (variables::esp::grenades::chams == 6) { m_mAppliedMaterial = m_mPlatinumMaterial; }
		else { m_mAppliedMaterial = m_mPlainMaterial; }
		m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, (variables::esp::grenades::chams == 3));
		return;

	}*/
	else if ((model.find(xorStr("models/weapons/w_ied_dropped.mdl")) != std::string::npos)) {
		m_bEnabled = variables::esp::C4::enabled && variables::esp::C4::chams > 0;
		m_bXQZ = variables::esp::C4::XQZchams;
		m_fColors[0] = 1.f; m_fColors[1] = 0.49803921568; m_fColors[2] = 0.15294117647;
		m_fXQZColors[0] = 0.4431372549f; m_fXQZColors[1] = 0.16470588235; m_fXQZColors[2] = 0.96862745098;
		if (variables::esp::C4::chams == 1  || variables::esp::C4::chams == 3) { m_mAppliedMaterial = m_mPlainMaterial; }
		else if (variables::esp::C4::chams == 2) { m_mAppliedMaterial = m_mFlatMaterial; }
		else if (variables::esp::C4::chams == 4) { m_mAppliedMaterial = m_mGoldMaterial; }
		else if (variables::esp::C4::chams == 5) { m_mAppliedMaterial = m_mPlasticMaterial; }
		else if (variables::esp::C4::chams == 6) { m_mAppliedMaterial = m_mPlatinumMaterial; }
		else { m_mAppliedMaterial = m_mPlainMaterial; }
		m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, (variables::esp::C4::chams == 3));
		return;
	}
	m_bEnabled = false;
	m_bXQZ = false;
	m_fColors[0] = 0; m_fColors[1] = 0; m_fColors[2] = 0;
	m_fXQZColors[0] = 0; m_fXQZColors[1] = 0; m_fXQZColors[2] = 0;
}
void Chams::loopDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) {
	if (!interfaceManager::iengine->IsInGame() || !interfaceManager::iengine->IsConnected()) return;
	crashhandler.setDebug("DMAC1");
	if (!variables::esp::enemies::enabled && !variables::esp::team::enabled && !variables::esp::grenades::enabled && !variables::esp::C4::enabled) return;
	crashhandler.setDebug("DMAC2");
	if (variables::esp::enemies::chams == 0 && variables::esp::team::chams == 0 /*&& variables::esp::grenades::chams == 0*/ && variables::esp::C4::chams == 0 /*&& variables::esp::other::sleeveChams && variables::esp::other::armsChams*/) return;
	crashhandler.setDebug("DMAC3");
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (!local) return;
	cBaseEntity* entity = interfaceManager::ientitylist->getClientEntity(pInfo.entity_index);
	crashhandler.setDebug("DMAC4");
	if (!entity) return;
	if (Functions::is_bad_ptr(entity)) return;
	ClientClass* cclass = entity->m_ClientClass();
	crashhandler.setDebug("DMAC5");
	if (Functions::is_bad_ptr(cclass)) return;
	crashhandler.setDebug("DMAC6");
	if (cclass->m_ClassID != classid::CCSPlayer && cclass->m_ClassID != classid::CC4 && cclass->m_ClassID != classid::CPlantedC4 ) {
		std::string model = interfaceManager::imodelinfo->GetModelName(entity->GetModel());
		crashhandler.setDebug("DMAC7");
		if (Functions::isGrenade(model) == xorStr("")) {
			return;
		}
	}
	/*if (arms || sleeves) {
		IMaterial* arms_ = interfaceManager::imaterial->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);
		if (((arms && variables::esp::other::armsChams) || (sleeves && variables::esp::other::sleeveChams)) && arms_){
			arms_->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			interfaceManager::iview->SetColorModulation(m_fcolors);
			interfaceManager::iview->SetBlend(1.f);
			interfaceManager::irender->ForcedMaterialOverride(m_mAppliedMaterial, OVERRIDE_NORMAL, 0);
			Hooks::drawmodelexecuteOriginal(interfaceManager::irender, ctx, state, pInfo, pCustomBoneToWorld);
		}
	}*/
	crashhandler.setDebug("DMAC8");
	bool enable = false, xqz = false;
	float m_fcolors[3] = { 1.0f, 1.0f, 1.0f }, m_fxqzcolors[3] = { 1.0f, 1.0f, 1.0f };
	Sync(entity, enable, xqz, m_fcolors, m_fxqzcolors);
	crashhandler.setDebug("DMAC9");
	if (enable) {
		if (!Functions::is_bad_ptr(m_mAppliedMaterial)) {
			if (cclass->m_ClassID == classid::CCSPlayer) {
				cBasePlayer* p = (cBasePlayer*)entity;
				crashhandler.setDebug("DMAC10");
				PaintTextureDrawModelExecute(entity, xqz, p->sameTeam(local) ? variables::esp::team::backtrackChams : variables::esp::enemies::backtrackChams, m_fcolors, m_fxqzcolors, ctx, state, pInfo, pCustomBoneToWorld);
			}
			else {
				PaintTextureDrawModelExecute(entity, xqz, false, m_fcolors, m_fxqzcolors, ctx, state, pInfo, pCustomBoneToWorld);

			}
			
		}
	}
}
void Chams::PaintTextureDrawModelExecute(cBaseEntity* entity, bool xqz, bool backtrack, float m_fcolors[3], float m_fxqzcolors[3], IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) {
	
	static auto dmo = Hooks::modelrender.get_original<decltype(&Hooks::drawModelExecuteHook)>(Game::m_iDrawModelExecute);

	crashhandler.setDebug("DMAC11");
	if (!entity) return;
	crashhandler.setDebug("DMAC12");
	if (!m_mAppliedMaterial) return;
	if (xqz) {
		interfaceManager::iview->SetColorModulation(m_fxqzcolors);
		interfaceManager::iview->SetBlend(1.f);
		m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		interfaceManager::irender->ForcedMaterialOverride(m_mAppliedMaterial, OVERRIDE_NORMAL, 0);
		dmo(interfaceManager::irender, 0, ctx, state, pInfo, pCustomBoneToWorld);
	}
	crashhandler.setDebug("DMAC13");
	interfaceManager::iview->SetColorModulation(m_fcolors);
	crashhandler.setDebug("DMAC14");
	interfaceManager::iview->SetBlend(1.f);
	crashhandler.setDebug("DMAC15");
	m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	crashhandler.setDebug("DMAC16");
	interfaceManager::irender->ForcedMaterialOverride(m_mAppliedMaterial, OVERRIDE_NORMAL, 0);
	crashhandler.setDebug("DMAC17");
	dmo(interfaceManager::irender, 0, ctx, state, pInfo, pCustomBoneToWorld);

	if (backtrack) {
		int arraySize = (sizeof(edgeaim.aimbot.headPositions) / sizeof(edgeaim.aimbot.headPositions[0]));
		if (arraySize > 0 && edgeaim.aimbot.Backtrack && entity == edgeaim.aimbot.pBestBacktrTarget) {
			for (int i = 0; i < edgeaim.aimbot.BacktrackTicks; i += 2) {
				if (i >= edgeaim.aimbot.BacktrackTicks) continue;
				aimbotFeature::backtrackData record = edgeaim.aimbot.headPositions[entity->m_iIndex()][i];
				if (record.hitboxPos == NULL) continue;
				if (!record.newMatrix) continue;
				interfaceManager::iview->SetColorModulation(m_fcolors);
				interfaceManager::iview->SetBlend(0.7f);
				m_mAppliedMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				interfaceManager::irender->ForcedMaterialOverride(m_mAppliedMaterial, OVERRIDE_NORMAL, 0);
				dmo(interfaceManager::irender, 0, ctx, state, pInfo, record.boneMatrix);

			}
		}
	}

}
void Chams::loopSceneEnd()
{
	if (!variables::esp::enemies::enabled && variables::esp::team::enabled && !variables::esp::grenades::enabled && !variables::esp::C4::enabled) return;
	if (!variables::esp::enemies::chams && variables::esp::team::chams &&/* !variables::esp::grenades::chams &&*/ !variables::esp::C4::chams) return;
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local)) return;
	for (int i = 0; i < interfaceManager::ientitylist->getHighestEntityIndex(); i++) {
		auto entity = interfaceManager::ientitylist->getClientEntity(i);
		if (Functions::is_bad_ptr(entity)) continue;
		ClientClass* cclass = entity->m_ClientClass();
		if (Functions::is_bad_ptr(cclass)) continue;
		if (cclass->m_ClassID != classid::CCSPlayer && cclass->m_ClassID != classid::CC4 && cclass->m_ClassID != classid::CPlantedC4) {
			std::string model = interfaceManager::imodelinfo->GetModelName(entity->GetModel());
			if (!strstr(model.c_str(), xorStr("models/Weapons/w_eq_fraggrenade_dropped.mdl")) &&
				!strstr(model.c_str(), xorStr("models/Weapons/w_eq_incendiarygrenade_dropped.mdl")) &&
				!strstr(model.c_str(), xorStr("models/Weapons/w_eq_flashbang_dropped.mdl")) &&
				!strstr(model.c_str(), xorStr("models/Weapons/w_eq_smokegrenade_thrown.mdl")) &&
				!strstr(model.c_str(), xorStr("models/Weapons/w_eq_decoy_dropped.mdl")) &&
				!strstr(model.c_str(), xorStr("models/Weapons/w_eq_molotov_dropped.mdl"))) {
				continue;
			}
		}
		bool enable, xqz;
		float m_fcolors[3], m_fxqzcolors[3];
		Sync(entity, enable, xqz, m_fcolors, m_fxqzcolors);
		if (enable) {
			if (!Functions::is_bad_ptr(m_mAppliedMaterial))
				PaintTextureSceneEnd(entity, m_mAppliedMaterial, m_fcolors, m_fxqzcolors, xqz);
		}
	}
}
