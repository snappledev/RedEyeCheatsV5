#pragma once
#include <Windows.h>
#include "vector.h"
#include "GameEvent.h"
#include "variables.h"
#include "interfaces.h"
struct mark
{
	Vector Position;
	Vector Max;
	Vector Min;
	std::string name;
	bool enemy;
	float curtime;
};
class Markers : public  IGameEventListener2 {
public:
	void draw();
	void update(IGameEvent* event);
	void Initialize() {
		if (!interfaceManager::igameevent)
			return;
		interfaceManager::igameevent->AddListener(this, xorStr("player_death"), false);
		interfaceManager::igameevent->AddListener(this, xorStr("round_start"), false);
	}
	void Clean() {
		if (!interfaceManager::igameevent)
			return;
		//interfaceManager::igameevent->RemoveListener(this);
	}
	~Markers() {
		Clean();
	}
	virtual void FireGameEvent(IGameEvent* even)
	{
		if (!even) return;
	}

	virtual int GetEventDebugID(void) {
		return 0x2A;
	}
	std::vector<mark> marks;
private:
	IGameEventListener2* listener;
};