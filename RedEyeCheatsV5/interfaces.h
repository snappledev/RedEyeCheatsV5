#pragma once
#include "iBaseClient.h"
#include "entityList.h"
#include "iEngine.h"
#include "iSurface.h"
#include "iPanel.h"
#include "iEngineTrace.h"
#include "IVModelInfo.h"
#include "globals.h"
#include "input.h"
#include "iClientMode.h"
#include "IVModelInfo.h"
#include "IModelRender.h"
#include "convars.h"
#include "NetworkStringTableContiner.h"
#include "localize.h"
#include "gameEvent.h"
#include "InputSystem.h"
#include "clientState.h"
#include "glowsystem.h"
#include "DebugOverlay.h"
#include "IEffect.h"
#include "cPlayerInventory.h"
#include "cInventoryManager.h"
namespace interfaceManager
{
	extern void findInterfaces();
	extern HMODULE E, clientModule;
	extern iBaseClient* ibaseclient;
	extern iEntityList* ientitylist;
	extern iEngine* iengine;
	extern iSurface* isurface;
	extern iPanel* ipanel;
	extern iEngineTrace* itrace;
	extern IVModelInfo* imodelinfo;
	extern iGlobals* iglobal;
	extern iInput* iinput;
	extern iInputSystem* inputsys;
	extern iClientMode* iclientmode;
	extern GameEvent* igameevent;
	extern VRenderView* iview;
	extern CClientState* iclientstate;
	extern IModelRender* irender;
	extern iNetworkStringTableContainer* inetworkstring;
	extern VCvars* icvars;
	extern iMaterialSystem* imaterial;
	extern iGlowManagerSystem* glowsystem;
	extern ILocalize* ilocalize;
	extern iDebugOverlay* idebug;
	extern ISteamHTTP* steaminterface;
	extern iEffects* ieffect;
	extern std::string keySig;
	extern cPlayerInventory* iLocalInventory;
	extern cInventoryManager* iCSInventoryManager;
};
