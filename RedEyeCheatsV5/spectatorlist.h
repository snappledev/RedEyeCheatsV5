#pragma once
#include <Windows.h>
#include "cBasePlayer.h"

class Spectators
{
public:
	void Draw();
	void loop();
	void Update();
private:
	int x = 10, y = 300, rx, ry;
	bool Open = true, Holding = false;
};
