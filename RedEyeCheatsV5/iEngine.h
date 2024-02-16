#pragma once
#include <Windows.h>
#include "virtualFunction.h"
#include "matrix3x4.h"
#include <stdint.h>
#include "qAngle.h"
typedef struct player_info_s {
private:
	int64_t unknown;
public:
	union {
		int64_t xuid;
		struct {
			int xuid_low;
			int xuid_high;
		};
	};
	char name[128];
	int userid;
	int m_nUserID;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
} player_info_t;


class iNetChannelInfo
{
public:
	enum
	{
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMentS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char  *GetName(void) const = 0;
	virtual const char  *GetAddress(void) const = 0;
	virtual float		GetTime(void) const = 0;
	virtual float		GetTimeConnected(void) const = 0;
	virtual int			GetBufferSize(void) const = 0;
	virtual int			GetDataRate(void) const = 0;
	virtual bool		IsLoopback(void) const = 0;
	virtual bool		IsTimingOut(void) const = 0;
	virtual bool		IsPlayback(void) const = 0;
	virtual float		GetLatency(int flow) const = 0;
	virtual float		GetAvgLatency(int flow) const = 0;
	virtual float		GetAvgLoss(int flow) const = 0;
	virtual float		GetAvgChoke(int flow) const = 0;
	virtual float		GetAvgData(int flow) const = 0;
	virtual float		GetAvgPackets(int flow) const = 0;
	virtual int			GetTotalData(int flow) const = 0;
	virtual int			GetTotalPackets(int flow) const = 0;
	virtual int			GetSequenceNr(int flow) const = 0;
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0;
	virtual float		GetPacketTime(int flow, int frame_number) const = 0;
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0;
	virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;
	virtual float		GetTimeSinceLastReceived(void) const = 0;
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};
class iEngine
{
public:
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* function)(PVOID, int&, int&);
		return virtualFunction<function>(this, 5)(this, width, height);
	}
	bool GetPlayerInfo(int ent_num, player_info_t *pinfo)
	{
		typedef bool(__thiscall* function)(PVOID, int, player_info_t *);
		return virtualFunction<function>(this, 8)(this, ent_num, pinfo);
	}
	int GetPlayerForUserID(int UserID) {
		using Original = int(__thiscall*)(PVOID, int);
		return virtualFunction<Original>(this, 9)(this, UserID);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 12)(this);
	}
	void GetViewAngles(QAngle* va)
	{
		typedef void(__thiscall* function)(PVOID, QAngle*);
		return virtualFunction<function>(this, 18)(this, va);
	}
	
	void SetViewAngles(Vector* va)
	{
		typedef void(__thiscall * function)(PVOID, Vector*);
		return virtualFunction<function>(this, 19)(this, va);
	}
	int GetMaxClients(void)
	{
		typedef int(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 20)(this);
	}
	bool IsInGame(void)
	{
		typedef bool(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 26)(this);
	}
	bool IsConnected(void)
	{
		typedef bool(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 27)(this);
	}

	const matrix3x4_t& WorldToScreenMatrix(void)
	{
		typedef const matrix3x4_t& (__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 37)(this);
	}
	bool IsTakingScreenshot(void)
	{
		typedef bool(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 85)(this);
	}
	float Time(void)
	{
		typedef float(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 14)(this);
	}
	void ClientCmd_Unrestricted(const char* chCommandString)
	{
		typedef void(__thiscall* function)(PVOID, const char *);
		return virtualFunction<function>(this, 114)(this, chCommandString);
	}
	void ExecuteClientCmd(const char* cmd)
	{
		typedef void(__thiscall* ExecuteClientCmdFn)(void*, const char*);
		return virtualFunction<ExecuteClientCmdFn>(this, 108)(this, cmd);
	}
	iNetChannelInfo* GetNetChannelInfo()
	{
		typedef iNetChannelInfo*(__thiscall* function)(PVOID);
		return virtualFunction< function >(this, 78)(this);
	}
};
