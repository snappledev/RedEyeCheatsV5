#pragma once
#include "vector.h"
class inputManager
{
public:
	void updateFrame();
	bool click(int key);
	bool hold(int key);
	bool inArea(int x, int y, int w, int h);
	const char* KeyToName(unsigned int key, bool capital);
	const char* KeyToNumber(unsigned int key);
	Vector cursor;
	bool bMouseUp, bMouseDown;
private:
	float upCurtime, downCurtime;
	bool keyboardData[256];
	bool oldKeyboardData[256];
};
extern inputManager inputmanager;