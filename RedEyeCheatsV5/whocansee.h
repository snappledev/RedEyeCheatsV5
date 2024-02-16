#pragma once
#include <Windows.h>
#include "cBasePlayer.h"

class WhoCanSee
{
public:
	void Draw();
	void loop();
	void Update();
private:
	int x = 10, y = 500, rx, ry;
	bool Open = true, Holding = false;
};

