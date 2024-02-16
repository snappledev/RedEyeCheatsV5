#pragma once
#include "iClientMode.h"
class viewmodifier
{
public:
	void run(CViewSetup* setup);
private:
	int mapRaise = 0;
	int mirrorRotation = 0;
	Vector origin = Vector(0,0,0 );
};