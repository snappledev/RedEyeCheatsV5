#pragma once
#include <Windows.h>
class IGameEvent {
public:
	virtual ~IGameEvent() {};
	virtual const char* GetName() const = 0;	// get event name

	virtual bool  IsReliable() const = 0; // if event handled reliable
	virtual bool  IsLocal() const = 0; // if event is never networked
	virtual bool  IsEmpty(const char* keyName = NULL) = 0; // check if data field exists
	virtual bool  GetBool(const char* keyName = NULL, bool defaultValue = false) = 0;
	virtual int   GetInt(const char* keyName = NULL, int defaultValue = 0) = 0;
	virtual unsigned __int64 GetUint64(const char* keyName = NULL, unsigned __int64 defaultValue = 0) = 0;
	virtual float GetFloat(const char* keyName = NULL, float defaultValue = 0.0f) = 0;
	virtual const char* GetString(const char* keyName = NULL, const char* defaultValue = "") = 0;
	virtual const wchar_t* GetWString(char const* keyName = NULL, const wchar_t* defaultValue = L"") = 0;
	virtual void SetBool(const char* keyName, bool value) = 0;
	virtual void SetInt(const char* keyName, int value) = 0;
	virtual void SetUint64(const char* keyName, unsigned __int64 value) = 0;
	virtual void SetFloat(const char* keyName, float value) = 0;
	virtual void SetString(const char* keyName, const char* value) = 0;
	virtual void SetWString(const char* keyName, const wchar_t* value) = 0;
};

class IGameEventListener2 {
public:
	virtual	~IGameEventListener2(void) {};
	virtual void FireGameEvent(IGameEvent* event) = 0;
	virtual int	 GetEventDebugID(void) = 0;
};

class bf_read;
class bf_write;

class GameEvent {
public:
	virtual	~GameEvent(void) {};
	virtual int LoadEventsFromFile(const char* filename) = 0;
	virtual void  Reset() = 0;
	virtual bool AddListener(IGameEventListener2* listener, const char* name, bool bServerSide) = 0;
	virtual bool FindListener(IGameEventListener2* listener, const char* name) = 0;
	virtual void RemoveListener(IGameEventListener2* listener) = 0;
	virtual IGameEvent* CreateEvent(const char* name, bool bForce = false, int* pCookie = NULL) = 0;
	virtual bool FireEvent(IGameEvent* event, bool bDontBroadcast = false) = 0;
	virtual bool FireEventClientSide(IGameEvent* event) = 0;
	virtual IGameEvent* DuplicateEvent(IGameEvent* event) = 0;
	virtual void FreeEvent(IGameEvent* event) = 0;
	virtual bool SerializeEvent(IGameEvent* event, bf_write* buf) = 0;
	virtual IGameEvent* UnserializeEvent(bf_read* buf) = 0;
};