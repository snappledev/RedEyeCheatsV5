#pragma once
#include <Windows.h>
#include "virtualFunction.h"
class iPanel
{
public:
	const char* findName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall * Panel)(PVOID, unsigned int);
		return virtualFunction<Panel>(this, 36)(this, vguiPanel);
	}
};