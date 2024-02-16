#pragma once
#include <Windows.h>
#include <vector>
#include "xor.h"
class debugManager
{
public:
	void fillSwitchPointers();
	void turnSwitchPointersOff();
	float getCurrentFPS();
	void runDebugTest();
	void runWarning();
	void calculateDebugTestResults(std::vector<int>* d);
	void disableInputForDebug();
	std::vector<int> average_FPS = {};
private:
	int switchIndex = 0;
	float previousCurTime = 0;
	float timeBetweenFrameChecks = 0.5;
	float frameChecks = 10;
	bool permissionToPushCurrentFPS = false;
	bool runningTest = false;
	std::vector<int> tempFPS = {};
	std::vector<bool*> switchPointers = {};
};

