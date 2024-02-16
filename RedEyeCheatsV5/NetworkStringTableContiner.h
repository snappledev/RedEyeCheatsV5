#pragma once
#include "virtualFunction.h"
#include <Windows.h>
typedef int TABLEID;
class INetworkStringTable;
typedef void(*pfnStringChanged)(void* object, INetworkStringTable* stringTable, int stringNumber, char const* newString, void const* newData);
const unsigned short INVALID_STRING_INDEX = (unsigned short)-1;
class INetworkStringTable
{
public:

	virtual					~INetworkStringTable(void) {};
	virtual const char* GetTableName(void) const = 0;
	virtual TABLEID			GetTableId(void) const = 0;
	virtual int				GetNumStrings(void) const = 0;
	virtual int				GetMaxStrings(void) const = 0;
	virtual int				GetEntryBits(void) const = 0;
	virtual void			SetTick(int tick) = 0;
	virtual bool			ChangedSinceTick(int tick) const = 0;
	virtual int				AddString(bool bIsServer, const char* value, int length = -1, const void* userdata = 0) = 0;
	virtual const char* GetString(int stringNumber) = 0;
	virtual void			SetStringUserData(int stringNumber, int length, const void* userdata) = 0;
	virtual const void* GetStringUserData(int stringNumber, int* length) = 0;
	virtual int				FindStringIndex(char const* string) = 0; // returns INVALID_STRING_INDEX if not found
	virtual void			SetStringChangedCallback(void* object, pfnStringChanged changeFunc) = 0;
};

class iNetworkStringTableContainer
{
public:
	INetworkStringTable* AquireTable(const char* table) {
		typedef INetworkStringTable* (__thiscall * findtable)(PVOID, const char*);
		return virtualFunction<findtable>(this, 3)(this, table);

	}
};
