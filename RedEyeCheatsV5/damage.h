#pragma once
#include "cBasePlayer.h"
#include "GameEvent.h"
#include "Interfaces.h"
struct damage_cloud
{
	int             Damage;
	float           Time;
	cBasePlayer * Player;
	Vector          Position;
	bool            Headshot = false;
	bool            Fatal = false;
};
class Damage : public  IGameEventListener2
{
public:
	void draw();
	void update(IGameEvent* event);
	void Initialize() {
		if (!interfaceManager::igameevent)
			return;
		interfaceManager::igameevent->AddListener(this, xorStr("player_hurt"), false);
	}
	void Clean() {
		if (!interfaceManager::igameevent)
			return;
		//interfaceManager::igameevent->RemoveListener(this);
	}
	~Damage() {
		Clean();
	}
	virtual void FireGameEvent(IGameEvent* even)
	{
		if (!even) return;
		
	}

	virtual int GetEventDebugID(void) {
		return 0x2A;
	}
	std::vector<damage_cloud> damage_clouds = {};
};