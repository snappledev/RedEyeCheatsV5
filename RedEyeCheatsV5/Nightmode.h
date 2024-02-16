#pragma once
#include "conv.h"
class Nightmode
{
public:
	void Peform();
	void Clean() {
		

	}
	~Nightmode() {
		Clean();
	}
	bool ShouldApply = false;
	bool ValueChanged = false;
	ConVar* r_drawspecificstaticprop;
};
extern Nightmode nightmode;