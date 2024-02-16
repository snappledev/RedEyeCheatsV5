#include "interfaces.h"
#include "iAppSystem.h"
#include <libloaderapi.h>
#include "xor.h"
#include "log.h"
#include "Functions.h"
#include "crashhandler.h"
#include "cInventoryManager.h"
#define STRINGIFY_IMPL(s) #s
#define STRINGIFY(s)      STRINGIFY_IMPL(s)
#define PRINT_INTERFACE(name) crashhandler.writeToDebugLog("%-20s: %p\n", STRINGIFY(name), name)
typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *name, int *rcode);
CreateInterfaceFn Module(HMODULE module)
{
	return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, xorStr("CreateInterface")));
}
bool is_number(char parse) {
	return isdigit(parse);

}
template<typename T>
T* claspInterface(CreateInterfaceFn f, const char* szInterfaceVersion)
{
	T* return_Value = reinterpret_cast<T*>(f(szInterfaceVersion, nullptr));
	if (return_Value == NULL) {
		for (int i = 0; i < 100; i++) {
			std::string name = szInterfaceVersion;
			if (i <= 9) {
				name += "00" + std::to_string(i);
			}
			else if (i > 9 && i <= 99) {
				name += "0" + std::to_string(i);
			}
			else {
				name += std::to_string(i);
			}
			return_Value = reinterpret_cast<T*>(f(name.c_str(), nullptr));
			if (return_Value) {
				return return_Value;
			}
		}
	}
	return return_Value;
}

namespace interfaceManager
{
	void findInterfaces() {
		crashhandler.setDebug("INF_1");
		clientModule = GetModuleHandleA(xorStr("client.dll"));
		E = GetModuleHandleA(xorStr("engine.dll"));
		HMODULE materialSys = GetModuleHandleA(xorStr("materialsystem.dll"));
		HMODULE vGuiMatSurface = GetModuleHandleA(xorStr("vguimatsurface.dll"));
		HMODULE vGui2 = GetModuleHandleA(xorStr("vgui2.dll"));
		HMODULE inputs = GetModuleHandleA(xorStr("inputsystem.dll"));
		HMODULE vstdli = GetModuleHandleA(xorStr("vstdlib.dll"));
		HMODULE localize = GetModuleHandleA(xorStr("localize.dll"));

		while (!materialSys || !vGuiMatSurface || !vGui2 || !inputs || !vstdli || !localize) {
			crashhandler.setDebug("INF_1A");
			clientModule = GetModuleHandleA(xorStr("client.dll")); crashhandler.setDebug("INF_13");
			E = GetModuleHandleA(xorStr("engine.dll")); 
			crashhandler.setDebug("INF_1B");
			materialSys = GetModuleHandleA(xorStr("materialsystem.dll")); 
			crashhandler.setDebug("INF_1C");
			vGuiMatSurface = GetModuleHandleA(xorStr("vguimatsurface.dll")); 
			crashhandler.setDebug("INF_1D");
			vGui2 = GetModuleHandleA(xorStr("vgui2.dll")); 
			crashhandler.setDebug("INF_1E");
			inputs = GetModuleHandleA(xorStr("inputsystem.dll")); 
			crashhandler.setDebug("INF_1F");
			vstdli = GetModuleHandleA(xorStr("vstdlib.dll")); 
			crashhandler.setDebug("INF_1G");
			localize = GetModuleHandleA(xorStr("localize.dll")); 
			crashhandler.setDebug("INF_1H");
		}


		crashhandler.setDebug("INF_2");
		crashhandler.setDebug("INF_3");

		auto FC = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(clientModule, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_4");
		auto FE = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(E, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_5");
		auto FM = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(materialSys, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_6");
		auto FG = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vGuiMatSurface, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_7");
		auto FP = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vGui2, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_8");
		auto FI = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(inputs, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_9");
		auto FS = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vstdli, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_10");
		auto FL = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(localize, xorStr("CreateInterface")));
		crashhandler.setDebug("INF_11");
		while (!FC || !FE || !FM || !FG || !FP || !FI || !FS || !FE || !FL) {
			crashhandler.setDebug("INF_12");
			FC = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(clientModule, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_13");
			FE = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(E, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_14");
			FM = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(materialSys, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_15");
			FG = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vGuiMatSurface, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_16");
			FP = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vGui2, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_17");
			FI = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(inputs, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_18");
			FS = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(vstdli, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_19");
			FL = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(localize, xorStr("CreateInterface")));
			crashhandler.setDebug("INF_20");
		}
		crashhandler.setDebug("INF_21");
		ibaseclient = claspInterface<iBaseClient>(    FC, xorStr("VClient018"));
		crashhandler.setDebug("ibase");
		ientitylist = claspInterface<iEntityList>(    FC, xorStr("VClientEntityList003"));
		crashhandler.setDebug("ient");
		iengine =     claspInterface<iEngine>(        FE, xorStr("VEngineClient014"));
		crashhandler.setDebug("iengine");
		isurface =    claspInterface<iSurface>(       FG, xorStr("VGUI_Surface031"));
		crashhandler.setDebug("isurface");
		ipanel =      claspInterface<iPanel>(         FP, xorStr("VGUI_Panel009"));
		crashhandler.setDebug("ipanel");
		itrace =      claspInterface<iEngineTrace>(   FE, xorStr("EngineTraceClient004"));
		crashhandler.setDebug("itrace");
		imaterial =   claspInterface<iMaterialSystem>(FM, xorStr("VMaterialSystem080"));
		crashhandler.setDebug("imaterial");
		imodelinfo =  claspInterface<IVModelInfo>(    FE, xorStr("VModelInfoClient004"));
		crashhandler.setDebug("imodel");
		ilocalize =   claspInterface<ILocalize>(      FL, xorStr("Localize_001"));
		crashhandler.setDebug("ilocalize");
		icvars = claspInterface<VCvars>(              FS, xorStr("VEngineCvar007"));
		crashhandler.setDebug("iceevar");
		igameevent = claspInterface<GameEvent>(        FE, xorStr("GAMEEVENTSMANAGER002"));
		crashhandler.setDebug("igameevent");
		inetworkstring = claspInterface<iNetworkStringTableContainer>(FE, xorStr("VEngineClientStringTable001"));
		crashhandler.setDebug("inetwork");
		iview =         claspInterface<VRenderView>(FE, xorStr("VEngineRenderView014"));
		crashhandler.setDebug("iview");
		irender = claspInterface<IModelRender>(FE, xorStr("VEngineModel016"));
		crashhandler.setDebug("irdr");
		inputsys = claspInterface<iInputSystem>(FI, xorStr("InputSystemVersion001"));
		crashhandler.setDebug("iinputsys");
		//"\xA1????\x8B?????\x85?\x74?\x8B?"
		iclientmode = *(iClientMode * *)(Functions::signature(clientModule, xorStr("B9 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 53")) + 1);
		crashhandler.setDebug("icmm");
		                                                                   //clientstate out of   A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0
		                                                                   //\xA1????\x8B?????\x85?\x74?\x8B?

		iclientstate = **(CClientState * **)(Functions::signature(E, xorStr("A1 ? ? ? ? 8B ? ? ? ? ? 85 ? 74 ? 8B")) + 1);
		crashhandler.setDebug("icsss");

		iglobal    =  **(iGlobals * **)((*(DWORD * *)ibaseclient)[11] + 10);
		crashhandler.setDebug("iglobal");
		iinput = *(iInput * *)((*(DWORD * *)ibaseclient)[16] + 0x1);
		crashhandler.setDebug("CLR_INST");                                            
		                                                                          //"\x11?????\x83??\xC7?????????\x0F\x28?????\x68????"
		glowsystem = *(iGlowManagerSystem**)(Functions::signature(clientModule, xorStr("0F 11 05 ? ? ? ? 83 C8 01")) + 3);


		crashhandler.setDebug("ieff");
		//Game::steamcontext = (SteamContext*)Functions::signature(clientModule, "FF 15 ?? ?? ?? ?? B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 6A 00") + 7;
		//steaminterface = (*(SteamContext**)Game::steamcontext)->m_pSteamHTTP;
		ieffect = claspInterface<iEffects>(FC, xorStr("IEffects001"));
		crashhandler.setDebug("idbg");
		idebug = claspInterface<iDebugOverlay>(FE, xorStr("VDebugOverlay"));
		crashhandler.setDebug("_IGNR");
		Functions::LoadNamedSky("", true);
		crashhandler.setDebug("No Success");
		//iLocalInventory = **reinterpret_cast<cPlayerInventory***>(Functions::signature(clientModule, xorStr("8B 3D ? ? ? ? 85 FF 74 1A")) + 0x2);
		crashhandler.setDebug("No Success 1");
		//iCSInventoryManager = *reinterpret_cast<cInventoryManager * *>(Functions::signature(clientModule, xorStr("B9 ?? ?? ?? ?? 8D 44 24 10 89 54 24 14") + 0x1));
		crashhandler.setDebug("Yay");
}
	iDebugOverlay* idebug;
	HMODULE E, clientModule;
	ILocalize* ilocalize;
	iInputSystem* inputsys;
	iNetworkStringTableContainer* inetworkstring;
	iEntityList* ientitylist;
	iBaseClient* ibaseclient;
	iInput* iinput;
	iMaterialSystem* imaterial;
	iEngine*	 iengine;
	VRenderView* iview;
	CClientState* iclientstate;
	iGlowManagerSystem* glowsystem;
	IModelRender* irender;
	VCvars* icvars;
	iSurface*    isurface;
	GameEvent*   igameevent;
	iPanel*      ipanel;
	iEngineTrace*    itrace;
	IVModelInfo*     imodelinfo;
	iGlobals* iglobal;
	iClientMode* iclientmode;
	ISteamHTTP* steaminterface;
	iEffects* ieffect;
	std::string keySig;
	cPlayerInventory* iLocalInventory;
	cInventoryManager* iCSInventoryManager;
}
