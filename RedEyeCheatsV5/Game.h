#pragma once
#include <Windows.h>
#include "networkedVariables.h"
#include "addr.h"
#include "steamhttp.h"
class cBasePlayer;
namespace Game {
	extern bool neverJoinedBefore;
	extern int m_iFramestageIndex;
	extern int m_iCreatemoveIndex;
	extern int m_iEventsIndex;
	extern int m_iViewIndex;
	extern int m_iSurfaceIndex;
	extern int m_iDME;
	extern int m_iOverride;
	extern int m_iViewmodel;
	extern int m_iKey;
	extern int m_iSpace;
	extern int m_iPanelIndex;
	extern int m_iGetClipRect;
	extern int m_iPostEffects;
	extern int m_iHudUpdate;
	extern int m_iEmitSound;
	extern int m_iOnScreenSizeChange;
	extern int m_iDrawModelExecute;
	extern int m_iWidth;
	extern int m_iHeight;
	extern int RenderView;
	extern double menu_scale_factor;
	extern double resolution_scale_factor;
	extern int m_FOV;
	extern  bool bSendPacket;
	extern int m_defaultFOV;
	extern bool menuOpen;
	extern bool setupCheat;
	extern float localRotation;
	extern bool enableBetaFix;
	
	extern networkManager network;
	extern HMODULE gameModule;
	extern cBasePlayer* local;
	extern SteamContext* steamcontext;
	extern void postRetrive();
	extern void postRetriveLater();
	extern void retriveGameData();
}
#define NET(type, name, table, netvar)                           \
    type& name() const {                                          \
        static int _##name = Game::network.getOffset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);                 \
    }

#define NET_OFF(type, name, table, netvar, offset)                           \
    type& name() const {                                          \
        static int _##name = Game::network.getOffset(table, netvar);     \
        return *(type*)((uintptr_t)this + offset +  _##name);                 \
    }
#define NETPROP(funcname, class_name, var_name) \
static auto funcname()->RecvProp* \
{ \
static RecvProp* prop_ptr; \
if (!prop_ptr) prop_ptr = Game::network.GetNetvarProp(class_name, var_name); \
return prop_ptr; \
}

#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset ); }