#pragma once
#include "cUserCmd.h"
class radarFeature {
public:
	void cmdUpdate(CUserCmd* c);
	void loop();
	void update();
	void draw();
private:
	int x = 20, y = 30, h = 266, w = 266, rx, ry;
	float localAngle = 90.0f;
	bool holding = false;
};