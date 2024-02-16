#pragma once
#include <Windows.h>
#include "hookClass.h"
#include "iBaseClient.h"
#include "cUserCmd.h"
#include "iClientMode.h"
#include "ClientFrameStage.h"
#include "gameEvent.h"
#include "IMatRenderContext.h" 
#include "iSurface.h"
#include "recvhook.h"
#include "IModelRender.h"
#include "matrix3x4.h"
#include "IClientNetworkable.h"
using paintTraverseStruct = void(__thiscall*)(iPanel*, unsigned int, bool, bool);
using getClipRectStruct = void(__thiscall*)(iPanel*, unsigned int, int&, int&, int&, int&);

typedef bool(__fastcall* createMoveStruct) (iClientMode*, void*, float, CUserCmd*);
//typedef bool(__thiscall* createMoveStruct)(iClientMode*, float, CUserCmd*);
typedef void(__thiscall* renderviewStruct)(void*, CViewSetup&, CViewSetup&, int, int);
typedef void(__thiscall* framestageStruct)(iBaseClient*, ClientFrameStage);
using drawmodelexecuteStruct = void(__thiscall*)(IModelRender*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
typedef bool(__thiscall* fireeventStruct)(GameEvent*, IGameEvent*, bool);
typedef void(__thiscall* onscreensizechangeStruct)(iSurface*, int,int);
typedef void(__fastcall* sceneendStruct)(void*, void*);

typedef void(__fastcall* networkOriginal)(IClientNetworkable* thisptr, void*, int update_type);
typedef void(__thiscall* lockStruct)(void*);
using overrideStruct = void* (__thiscall*)(void*, CViewSetup*);
typedef float(__thiscall* getviewmodelStruct)();
namespace Hooks
{
	extern void setupHooks(LPVOID reserve);
	extern void destroyHooks();
	extern VMT panel;
	extern paintTraverseStruct paintraverseOriginal;
	extern getClipRectStruct getrectOriginal;
	extern networkOriginal networkhookOriginal;
	void __fastcall drawModelExecuteHook(void* _this, int edx, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
	extern VMT localNetwork;
	extern VMT surface;
	extern VMT client;
	extern framestageStruct framestageOriginal;
	extern VMT clientmode;
	extern overrideStruct overrideOriginal;
	extern VMT events;
	extern VMT view;
	extern VMT modelrender;
	extern VMT seqhook;
	extern recv_prop_hook* sequence;
}