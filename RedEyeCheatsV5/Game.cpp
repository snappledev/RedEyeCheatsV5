#include "Game.h"
#include "networkedVariables.h"
#include "painting.h"
#include "interfaces.h"
#include "skinchanger.h"
namespace Game {
	int m_iFramestageIndex;
	int m_iCreatemoveIndex;
	bool neverJoinedBefore = true;
	int m_iEventsIndex;
	int m_iViewIndex;
	int m_iSurfaceIndex;
	int m_iDME;
	int m_iOverride;
	int m_iViewmodel;
	int m_iKey;
	int m_iOnScreenSizeChange;
	int m_iSpace;
	int m_iPanelIndex;
	int m_iGetClipRect;
	int m_iHudUpdate;
	int m_iDrawModelExecute;
	int m_iPostEffects;
	int m_iEmitSound;
	int m_iWidth;
	int RenderView;
	int m_iHeight;
	HMODULE gameModule;
	SteamContext* steamcontext;
	double menu_scale_factor = 1.1;
	double resolution_scale_factor = 1;
	int m_FOV = 90;
	float localRotation = 0;
	bool bSendPacket = false;
	int m_defaultFOV = -1;
	bool menuOpen = false;
	bool setupCheat = false;
	bool enableBetaFix = false;
	networkManager network;
	cBasePlayer* local;
	void retriveGameData() {
		/*====================Hook Indexes===================*/
		m_iKey = 20;
		RenderView = 6;
		m_iFramestageIndex = 37;
		m_iCreatemoveIndex = 24;
		m_iEventsIndex = 8;
		m_iViewIndex = 9;
		m_iSurfaceIndex = 67;
		m_iPanelIndex = 41;
		m_iSpace = 44;
		m_iHudUpdate = 11;
		m_iViewmodel = 35;
		m_iDME = 21;
		m_iOverride = 18;
		m_iEmitSound = 5;
		m_iGetClipRect = 11;
		m_iOnScreenSizeChange = 116;
		m_iDrawModelExecute = 21;
		m_iPostEffects = 44;
		//const int result = MessageBoxA(NULL, "Some users may experience crashes due to the cheat being in beta. Would you like to enable a beta fix? This may cause minor GUI visual glitchs", "Enable Beta Fix", MB_YESNOCANCEL);
		//enableBetaFix = (result == IDYES) ? true : false;
		local = NULL;
		/*===================================================*/
	}
	void postRetrive() {
		network.findNetworkTables();
		paint = std::make_unique<Paint>();
	}
	void postRetriveLater() {
		menu_scale_factor = ((double)Game::m_iWidth / 1920.0000f) + 0.1;
		resolution_scale_factor = ((double)Game::m_iWidth / 1920.0000f);
		variables::gui::scaleFactor = 100 * menu_scale_factor;
		skinchanger.FindKits();
	}
}