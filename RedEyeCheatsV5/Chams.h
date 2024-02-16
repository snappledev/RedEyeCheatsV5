#pragma once
#include "cBasePlayer.h"
#include "IMatRenderContext.h"
#include "IModelRender.h"
#include "matrix3x4.h"
class Chams
{
public:
	void Clean();
	~Chams() {
		Clean();
	}
	void Initialize();
	void loopSceneEnd();
	void loopDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
	void PaintTextureDrawModelExecute(cBaseEntity* entity, bool xqz, bool backtrack, float m_fcolors[3], float m_fxqzcolors[3], IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
	void PaintTextureSceneEnd(cBaseEntity* entity, IMaterial* material, float* color, float* xyzcolor, bool xqz);
	void Sync(cBaseEntity* entity, bool& m_bEnabled, bool& m_bXQZ, float m_fColors[3], float m_fXQZColors[3]);
	bool bInitialized = false;

private:
	IMaterial* m_mGoldMaterial;
	IMaterial* m_mPlasticMaterial;
	IMaterial* m_mPlatinumMaterial;
	IMaterial* m_mPlainMaterial;
	IMaterial* m_mFlatMaterial;

	IMaterial* m_mOutlineMaterial;
	IMaterial* m_mAppliedMaterial;
};
extern Chams chams;