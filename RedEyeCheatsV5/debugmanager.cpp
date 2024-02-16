#include "debugmanager.h"
#include "interfaces.h"
#include "log.h"
#include "variables.h"
#include "painting.h"
void debugManager::fillSwitchPointers() {
	switchPointers = 
	{	&variables::debug::main1,
		&variables::debug::main2, 
		&variables::debug::main3,
		&variables::debug::main4,
		&variables::debug::main5,
		&variables::debug::main6,
		&variables::debug::main7,
		&variables::debug::main8,
		&variables::debug::main9,
		&variables::debug::main10,
		&variables::debug::main11,
		&variables::debug::main12,
		&variables::debug::main13,
		&variables::debug::main14,
		&variables::debug::main15,
		&variables::debug::main16,
		&variables::debug::main17, 
		&variables::debug::main18,
		&variables::debug::main19,
		&variables::debug::main20,
		&variables::debug::main21,
		&variables::debug::main22,
		&variables::debug::main23,
		&variables::debug::main24,
		&variables::debug::main25,
		&variables::debug::main26,
		&variables::debug::main27,
		&variables::debug::main28,
		&variables::debug::main29,
		&variables::debug::main30,
		&variables::debug::main31,
		&variables::debug::main32 };
}
void debugManager::turnSwitchPointersOff() {
	average_FPS = std::vector<int>(switchPointers.size());
	for (int i = 0; i < switchPointers.size(); i++) {
		*switchPointers[i] = false;
		average_FPS[i] = -1;
	}

}
float debugManager::getCurrentFPS() {
	return static_cast<int>(1.f / interfaceManager::iglobal->frametime);
}
void debugManager::disableInputForDebug() {
	
}

void debugManager::runDebugTest() {
	if (!runningTest) {
		if (switchPointers.empty())
			fillSwitchPointers();
		interfaceManager::inputsys->EnableInput(false);
		average_FPS.clear();
		tempFPS.clear();
		turnSwitchPointersOff();
		runningTest = true;
	}
}
void debugManager::runWarning() {
	if (runningTest) {
		int percentageComplete = 100.f * (float)((float)switchIndex / (float)switchPointers.size());
		std::string word = xorStr("RUNNING DEBUG TEST: ") + std::to_string(percentageComplete) + xorStr("%");
		RECT area = paint->textSize(word.c_str(), Glyphs::debug_warning);
		paint->rectangle((Game::m_iWidth / 2) - (area.right / 2) - 5, (Game::m_iHeight / 2) - (area.bottom / 2) - 5, area.right + 10, area.bottom + 10, color(25, 25, 25, 255));
		paint->text(Game::m_iWidth / 2, Game::m_iHeight / 2, word.c_str(), Glyphs::debug_warning, Anchor::Center, color(255, 0, 0, 255));
	}
}
void debugManager::calculateDebugTestResults(std::vector<int>* d) {
	if (runningTest) {
		if (switchIndex < average_FPS.size()) {
			if (average_FPS[switchIndex] == -1) {

				if (tempFPS.size() < frameChecks) {
					if (interfaceManager::iglobal->curtime - previousCurTime > timeBetweenFrameChecks) {
						float currentFPS = getCurrentFPS();
						tempFPS.push_back(currentFPS);
						previousCurTime = interfaceManager::iglobal->curtime;

					}
					else {
						if (previousCurTime < -0.5)
							previousCurTime = interfaceManager::iglobal->curtime;
					}
				}
				else {
					//We can assume we have more than 3 data of the temp fps
					float average = 0;
					for (int x = 0; x < tempFPS.size(); x++)
						average += tempFPS[x];

					average /= tempFPS.size();
					tempFPS.clear();
					average_FPS[switchIndex] = (average);
					previousCurTime = interfaceManager::iglobal->curtime;
					*switchPointers[switchIndex] = true;
					switchIndex++;

				}
			}
		}
		else {
			runningTest = false;
			//Final data is ready
			*d = average_FPS;
			switchIndex = 0;
			tempFPS.clear();
			previousCurTime = 0;
			interfaceManager::inputsys->EnableInput(true);
		}
	}
}