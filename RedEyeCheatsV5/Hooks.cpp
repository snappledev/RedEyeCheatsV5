#include "Hooks.h"
#include "interfaces.h"
#include "Game.h"
#include "edgeAim.h"
#include "inputManager.h"
#include "icons.h"
bool bPanel = false;
bool allhooked = false;
int interations = 0;
int paintTraverseIndex = 0;
void __fastcall paintTraverse(iPanel* this_, int edx, unsigned int panel, bool forceRepaint, bool allowForce)
{
	crashhandler.setDebug("PNT");
	
	static auto fn = Hooks::panel.get_original<decltype(&paintTraverse)>(Game::m_iPanelIndex);
	crashhandler.setDebug("PNT2");
	if (Functions::is_bad_ptr(this_) || Functions::is_bad_ptr(&edx) || Functions::is_bad_ptr(&panel) || Functions::is_bad_ptr(&forceRepaint) || Functions::is_bad_ptr(&allowForce)) {
		return;
	}
	logger.LogPrint(paintTraverseIndex + " - PAINTRAVERSE");
	fn(this_, edx, panel, forceRepaint, allowForce);
	static bool hashooked = false;

	if (allhooked) {
		if (!hashooked) {
			
			hashooked = true;
		}
		else {
			
		}
	}

	edgeaim.prePainting();
	crashhandler.setDebug("PNT3");
	if (!bPanel) {
		PCHAR sPanel = (PCHAR)interfaceManager::ipanel->findName(panel);
		if (strstr(sPanel, xorStr("FocusOverlayPanel"))) {
			paint->panelID = panel;
			bPanel = true;
		}
	}
	else if (paint->panelID == panel) {
		static bool bSkip = false;
		bSkip = !bSkip;
		if (bSkip)
		{
			crashhandler.setDebug("PNT4");
			inputmanager.updateFrame();
			crashhandler.setDebug("PNTB");
			if (!images::imagesCached)
				images::cacheImages();
			crashhandler.setDebug("PNT67");
			edgeaim.panelPainting();
		}
	} 

	crashhandler.setDebug("END3x");
	
	logger.LogString("paintend");
};
void __fastcall hkCreateMove_Proxy(void* _this, int, int sequence_number, float input_sample_frametime, bool active);
int createMoveIndex = 0;
void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
{
	crashhandler.setDebug("CRB");
	auto oCreateMove = Hooks::client.get_original<decltype(&hkCreateMove_Proxy)>(22);
	if (Functions::is_bad_ptr(interfaceManager::ibaseclient) || Functions::is_bad_ptr(&sequence_number) || Functions::is_bad_ptr(&input_sample_frametime) || Functions::is_bad_ptr(&active) || Functions::is_bad_ptr(&bSendPacket)) {
		return;
	}
	logger.LogPrint(createMoveIndex + " - CREATEMOVE");
	oCreateMove(interfaceManager::ibaseclient, 0, sequence_number, input_sample_frametime, active);
	crashhandler.setDebug("CRB2");
	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);



	auto cmd = interfaceManager::iinput->GetUserCmd(sequence_number);
	crashhandler.setDebug("CRB2-B");
	auto verified = interfaceManager::iinput->GetVerifiedCmd(sequence_number);
	crashhandler.setDebug("CRB3");
	if (!cmd || !cmd->command_number)
		return;
	crashhandler.setDebug("CRB4");
	cBaseEntity* local = interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local))
		return;
	crashhandler.setDebug("a");
	Game::localRotation = cmd->viewangles.y;
	edgeaim.gameMove(cmd, input_sample_frametime, bSendPacket);
	crashhandler.setDebug("e");

	Game::bSendPacket = send_packet;
	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();
	crashhandler.setDebug("d");
}

//--------------------------------------------------------------------------------
__declspec(naked) void __fastcall hkCreateMove_Proxy(void* _this, int, int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		push ebp
		mov  ebp, esp
		push ebx;
		push esp
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call hkCreateMove
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}

/*
bool __fastcall CreateHook(iClientMode* e, void* edx, float input_sample_frametime, CUserCmd* cmd)
{
	crashhandler.setDebug("a11");
	static auto oCreateMove = Hooks::clientmode.get_original<bool(__thiscall*)(iClientMode*, float, CUserCmd*)>(Game::m_iCreatemoveIndex);
	oCreateMove(interfaceManager::iclientmode,  input_sample_frametime, cmd);
	crashhandler.setDebug("a1");
	if (Functions::is_bad_ptr(cmd) || !cmd->command_number)
		return;
	cBaseEntity* local = interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	if (Functions::is_bad_ptr(local))
		return oCreateMove(_this, edx, input_sample_frametime, cmd);
	crashhandler.setDebug("a");
	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);
	crashhandler.setDebug("b");
	
	crashhandler.setDebug("c");
	bool bSendPacket = true;
	edgeaim.gameMove(cmd, input_sample_frametime, bSendPacket);
	crashhandler.setDebug("d");
	if (!Functions::is_bad_ptr(&send_packet))
		send_packet = bSendPacket;
	crashhandler.setDebug("e");
	return;
}*/
void __stdcall GetClipRect(unsigned int panel, int& x1, int&y1, int&x2, int&y2)
{
	crashhandler.setDebug("clip");
	static auto original = Hooks::panel.get_original<getClipRectStruct>(Game::m_iGetClipRect);
	if (Functions::is_bad_ptr(interfaceManager::ipanel) || Functions::is_bad_ptr(&x1) || Functions::is_bad_ptr(&y1) || Functions::is_bad_ptr(&x2) || Functions::is_bad_ptr(&y2)) {
		return;
	}
	original(interfaceManager::ipanel, panel, x1, y1, x2, y2);
	static bool hashooked = false;
	if (allhooked) {
		if (!hashooked) {
			
			hashooked = true;
		}
		else {
			
		}
	}
	crashhandler.setDebug("clip2");
	if (paint->bCustomClip)
	{
		x1 = paint->x;
		y1 = paint->y;
		x2 = paint->x1;
		y2 = paint->y1;
	}
	crashhandler.setDebug("clipend");
	
}
void __fastcall LockCursor(void* this_)
{
	crashhandler.setDebug("LOCK");
	static auto ofunc = Hooks::surface.get_original<decltype(&LockCursor)>(Game::m_iSurfaceIndex);
	if (Functions::is_bad_ptr(interfaceManager::isurface)) {
		return;
	}
	if (variables::gui::bShowMainGui) {
		interfaceManager::isurface->UnlockCursor();
		return;
	}


	ofunc(interfaceManager::isurface);
	static bool hashooked = false;
	if (allhooked) {
		if (!hashooked) {
			
			hashooked = true;
		}
		else {
			
		}
	}
	crashhandler.setDebug("LOCKEND");
}






float __stdcall GetViewmodelHook() {
	crashhandler.setDebug("VMODEL");
	static float fov = Hooks::clientmode.get_original<getviewmodelStruct>(Game::m_iViewmodel)();
	
	if (Game::m_defaultFOV == -1)
		Game::m_defaultFOV = fov;
	else {
		if (variables::misc::viewfov != 0)
			fov = Game::m_defaultFOV + variables::misc::viewfov;
	}
		
	crashhandler.setDebug("VMODEL2");
	static bool hashooked = false;
	if (allhooked) {
		if (!hashooked) {
			
			hashooked = true;
		}
		else {
			
		}
	}
	return fov;
}

/*
void __stdcall hkOverrideView(CViewSetup* vsView)
	{
		static auto ofunc = clientmode_hook.get_original<OverrideView>(index::OverrideView);

		if (g_EngineClient->IsInGame() && vsView) {
			Visuals::Misc::ThirdPerson();
		}

		ofunc(g_ClientMode, vsView);
	}

*/
bool previous = false;
bool __fastcall OverrideHook(void* thisptr, void*, CViewSetup* view) {
	static auto ofunc = Hooks::clientmode.get_original <decltype(&OverrideHook) > (Game::m_iOverride);
	if (Functions::is_bad_ptr(thisptr) || Functions::is_bad_ptr(view)) {
		return previous;
	}
	if (interfaceManager::iengine->IsInGame() && interfaceManager::iengine->IsConnected() && view) {
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (!Functions::is_bad_ptr(local)) {
			if (variables::misc::gamefov != 0)
				view->fov += variables::misc::gamefov;
		}
	}
	
	Game::m_FOV = view->fov;
	edgeaim.viewmod(view);
	
	crashhandler.setDebug("OVR1");
	previous = ofunc(interfaceManager::iclientmode,0,view);
	return previous;
	crashhandler.setDebug("OVR2");
}

/*
void __stdcall hkDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
	{
		static auto ofunc = mdlrender_hook.get_original<DrawModelExecute>(index::DrawModelExecute);

		Chams::Get().OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

		ofunc(g_MdlRender, ctx, state, pInfo, pCustomBoneToWorld);

		g_MdlRender->ForcedMaterialOverride(nullptr);
	}

*/
int drawModelIndex = 0;
void __fastcall Hooks::drawModelExecuteHook(void* _this, int edx, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) {
	crashhandler.setDebug("DME3");
	static auto dmo = Hooks::modelrender.get_original<decltype(&drawModelExecuteHook)>(Game::m_iDrawModelExecute);
	if (interfaceManager::irender->isForcedMaterialOverride()) {
		crashhandler.setDebug("DME5");
		return dmo(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
	}
	crashhandler.setDebug("DME4");
	edgeaim.drawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
	crashhandler.setDebug("DME6");
	dmo(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
	crashhandler.setDebug("DME7");
	interfaceManager::irender->ForcedMaterialOverride(nullptr);
	crashhandler.setDebug("DME3");
}
void __fastcall CSPlayerPostUpdate(IClientNetworkable* this_, void*,  int update_type) {
	
	edgeaim.playerpostupdate(static_cast<cBasePlayer*>(this_));
	return Hooks::networkhookOriginal(this_, nullptr, update_type);
}
int framestageIndex = 0;
void __fastcall FrameStageNotiyHook(void* _this, int edx, ClientFrameStage stage)
{
	static auto original = Hooks::client.get_original<decltype(&FrameStageNotiyHook)>(Game::m_iFramestageIndex);
	crashhandler.setDebug("frameStage");
	if (Functions::is_bad_ptr(interfaceManager::ibaseclient) || Functions::is_bad_ptr(interfaceManager::iengine) || Functions::is_bad_ptr(interfaceManager::ientitylist) || Functions::is_bad_ptr(&stage)) {
		return;
	}


	
	cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
	switch (stage)
	{
	case ClientFrameStage::FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		edgeaim.framenetupdatepostdataupdatestart(local);
		break;
	case ClientFrameStage::FRAME_RENDER_START:
		if (interfaceManager::iengine && interfaceManager::ientitylist) {
			if (interfaceManager::iengine->IsConnected() && interfaceManager::iengine->IsInGame()) {
				int index = interfaceManager::iengine->GetLocalPlayer();
				if (Functions::is_bad_ptr(Game::local)) {
					Game::local = local;
				}
			}
			else
				Game::local = NULL;
		}
		break;
		
	default:
		break;
	}
	original(interfaceManager::ibaseclient, edx, stage);
	crashhandler.setDebug("frameStage3");
}

/*void __fastcall emitSound(void* _this, int edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, int nSeed, float flAttenuation, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int unk)
{
	static auto func = Hooks::clientmode.get_original<decltype(&emitSound)>(Game::m_iPostEffects);
	if (!strcmp(pSoundEntry, xorStr("UIPanorama.popup_accept_match_beep")))
		Functions::SetLocalPlayerReady();
	func(_this, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, params);
}*/
int prev = 0;
int __fastcall dopostscreeneffects(void* this_, int* edx, int a) {
	auto fn = Hooks::clientmode.get_original<decltype(&dopostscreeneffects)>(Game::m_iPostEffects);
	if (Functions::is_bad_ptr(this_) || Functions::is_bad_ptr(edx) || Functions::is_bad_ptr(&a))
		return prev;
	edgeaim.doposteffects();
	prev = fn(interfaceManager::iclientmode, edx, a);
	return prev;
}



bool prv = false;
bool __stdcall FireEventHook(IGameEvent* _event, bool broadcast)
{
	crashhandler.setDebug("FIREEVENT1");
	static auto ohook = Hooks::events.get_original<fireeventStruct>(Game::m_iEventsIndex);

	if (Functions::is_bad_ptr(_event) || Functions::is_bad_ptr(&broadcast) || Functions::is_bad_ptr(interfaceManager::igameevent) || Functions::is_bad_ptr(interfaceManager::igameevent)) {
		return prv;
	}
	if (!Functions::is_bad_ptr(_event)) {
		crashhandler.setDebug("FIREEVENTC");
		edgeaim.fireevent(_event);
	}
	crashhandler.setDebug("FIREEVENT2");
	prv = ohook(interfaceManager::igameevent, _event, broadcast);;
	return prv;
}
void __cdecl SequenceProxy(const CRecvProxyData* proxy_data_const, void* entity, void* output)
{
	crashhandler.setDebug("SEQ1");
	static auto ofunc = Hooks::sequence->get_original_function();
	crashhandler.setDebug("SEQ3");
	const auto proxy = const_cast<CRecvProxyData*>(proxy_data_const);
	crashhandler.setDebug("SEQB");
	const auto model = static_cast<cBaseViewModel*>(entity);
	if (!Functions::is_bad_ptr(model) && !Functions::is_bad_ptr(proxy) && !Functions::is_bad_ptr(entity)) {
		skinchanger.CorrectSequences(proxy, model);
	}

	ofunc(proxy_data_const, entity, output);
	crashhandler.setDebug("SEQ2");
}
void __fastcall SceneEndHook(void* thisptr, void* edx) {
	crashhandler.setDebug("SCENE1");
	static auto oScene = Hooks::view.get_original<decltype(&SceneEndHook)>(Game::m_iViewIndex);
	oScene(thisptr, edx);
	crashhandler.setDebug("SCENE2");
}
void __fastcall onScreenSizeChangedHook(void* ecx, int edx, int oldWidth, int oldHeight) {
	crashhandler.setDebug("onSCR");
	if (Functions::is_bad_ptr(ecx) || Functions::is_bad_ptr(&edx) || Functions::is_bad_ptr(&oldWidth) || Functions::is_bad_ptr(&oldHeight)) {
		return;
	}
	static auto func = Hooks::surface.get_original<decltype(&onScreenSizeChangedHook)>(Game::m_iOnScreenSizeChange);
	interfaceManager::iengine->GetScreenSize(Game::m_iWidth, Game::m_iHeight);
	Game::resolution_scale_factor = ((double)Game::m_iWidth / 1920.0000f); 
	paint->resetFonts();
	func(ecx,edx, oldWidth, oldHeight);
	crashhandler.setDebug("onSCR2");
}

namespace Hooks
{
	VMT panel;
	paintTraverseStruct paintraverseOriginal;
	getClipRectStruct getrectOriginal;
	networkOriginal networkhookOriginal;


	VMT localNetwork;
	VMT surface;
	VMT client;
	framestageStruct framestageOriginal;
	VMT clientmode;
	overrideStruct overrideOriginal;
	VMT events;
	VMT view;
	VMT modelrender;
	recv_prop_hook* sequence;
	VMT seqhook;
	void setupHooks(LPVOID reserve) {
		bool successPanel = panel.setup(interfaceManager::ipanel, xorStr("vgui2.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_1");
		bool successSurface = surface.setup(interfaceManager::isurface, xorStr("vguimatsurface.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_2");
		bool successClient = client.setup(interfaceManager::ibaseclient, xorStr("client.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_3");
		bool successClientMode = clientmode.setup(interfaceManager::iclientmode, xorStr("client.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_4");
		bool successEvents = events.setup(interfaceManager::igameevent, xorStr("engine.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_5");
		bool successView = view.setup(interfaceManager::iview, xorStr("engine.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_6");
		bool successModel = modelrender.setup(interfaceManager::irender, xorStr("engine.dll"));
		crashhandler.setDebug("CHEAT_HOOKS_7");
		
		if (!successPanel || !successSurface || !successClient || !successClientMode ||
			!successEvents || !successView || !successModel) {
			crashhandler.messageBox(xorStr("Critical setup error: code ") +
				std::to_string(successPanel) +
				std::to_string(successSurface) +
				std::to_string(successClient) +
				std::to_string(successClientMode) +
				std::to_string(successEvents) +
				std::to_string(successView) +
				std::to_string(successModel));
			return;
			
		}
	 	crashhandler.setDebug("CHEAT_HOOKS_8");
		
		
	
		panel.hook_index(Game::m_iPanelIndex, paintTraverse);

		crashhandler.setDebug("CHEAT_HOOKS_9");
		
		getrectOriginal = Hooks::panel.get_original<getClipRectStruct>(Game::m_iGetClipRect);
		
		panel.hook_index(Game::m_iGetClipRect, GetClipRect);

		crashhandler.setDebug("CHEAT_HOOKS_10");
		client.hook_index(22, hkCreateMove_Proxy);
		crashhandler.setDebug("CHEAT_HOOKS_11");

		//overrideOriginal = Hooks::clientmode.get_original <decltype(&OverrideHook) > (Game::m_iOverride);
		
		clientmode.hook_index(Game::m_iOverride, OverrideHook);  //OVR2 CRASH
		clientmode.hook_index(Game::m_iPostEffects, dopostscreeneffects);
		//crashhandler.setDebug("CHEAT_HOOKS_12");
//
		//viewmodelOriginal = 
		//clientmode.hook_index(Game::m_iViewmodel, GetViewmodelHook); //CRASH
		crashhandler.setDebug("CHEAT_HOOKS_13");


		



		
		client.hook_index(Game::m_iFramestageIndex, FrameStageNotiyHook);//CRASH
		crashhandler.setDebug("CHEAT_HOOKS_14");
		


		//////////////////////////////////////////////////////////////////////////
		crashhandler.setDebug("CHEAT_HOOKS_15");
		//
		surface.hook_index(Game::m_iSurfaceIndex, LockCursor);
		crashhandler.setDebug("CHEAT_HOOKS_16");
		surface.hook_index(Game::m_iOnScreenSizeChange, onScreenSizeChangedHook);
		crashhandler.setDebug("CHEAT_HOOKS_17");
		
		 modelrender.hook_index(Game::m_iDrawModelExecute, drawModelExecuteHook); //DME3 CRASH

	
		
		events.hook_index(Game::m_iEventsIndex, FireEventHook);
		
		
		crashhandler.setDebug("CHEAT_HOOKS_18");
		RecvProp* sequence_prop = Game::network.GetNetvarProp(xorStr("DT_BaseViewModel"), xorStr("m_nSequence"));
		crashhandler.setDebug("CHEAT_HOOKS_19");
		sequence = new recv_prop_hook(sequence_prop, &SequenceProxy);
		crashhandler.setDebug("CHEAT_HOOKS_20");

		
		const char* DLLs[]{ "client.dll", "engine.dll", "server.dll", "studiorender.dll", "materialsystem.dll", "shaderapidx9.dll", "vstdlib.dll", "vguimatsurface.dll" };
		long long PatchADDR = 0x69690004C201B0;
		for (auto DLL : DLLs) {
			HMODULE module = GetModuleHandleA(xorStr(DLL));
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)Functions::signature(module, "55 8B EC 56 8B F1 33 C0 57 8B 7D 08"), &PatchADDR, 7, 0);
		}
		
		allhooked = true;

	}
	void destroyHooks()
	{
		panel.unhook_all();
		clientmode.unhook_all();
		client.unhook_all();
		events.unhook_all();
		surface.unhook_all();
		modelrender.unhook_all();
		//delete sequence;
		
	}
}


