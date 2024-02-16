#pragma once
#pragma once
#include "conv.h"
class Asus
{
public:
	void Peform();
	void Clean() {


	}
	~Asus() {
		Clean();
	}
	bool ShouldApply = false;
	int ValueChanged = 0;
	ConVar* r_drawspecificstaticprop;
};
extern Asus asus;