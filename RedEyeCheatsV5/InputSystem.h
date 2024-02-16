#pragma once
#include "virtualFunction.h"
#include "ButtonCode_t.h"
class iInputSystem
{
public:
	inline void EnableInput(bool bEnable)
	{
		typedef void(__thiscall * OriginalFn)(void*, bool);
		return virtualFunction<OriginalFn>(this, 11)(this, bEnable);
	}
	inline int GetAnalogValue(int v) {
		typedef int(__thiscall * OriginalFn)(void*, int);
		return virtualFunction<OriginalFn>(this, 18)(this, v);
	}
	inline bool IsButtonDown(ButtonCode_t code)
	{
		typedef bool(__thiscall * OriginalFn)(void*, ButtonCode_t);
		return virtualFunction<OriginalFn>(this, 15)(this, code);
	}

	inline void GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall * OriginalFn)(void*, int*, int*);
		return virtualFunction<OriginalFn>(this, 56)(this, m_pX, m_pY);
	}

	inline ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
	{
		typedef ButtonCode_t(__thiscall * OriginalFn)(void*, int);
		return virtualFunction<OriginalFn>(this, 44)(this, nVirtualKey);
	}

	inline int ButtonCodeToVirtualKey(ButtonCode_t code)
	{
		typedef int(__thiscall * OriginalFn)(void*, ButtonCode_t);
		return virtualFunction<OriginalFn>(this, 45)(this, code);
	}
};

