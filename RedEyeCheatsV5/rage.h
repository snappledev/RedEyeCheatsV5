#pragma once
#include "cUserCmd.h"
#include <Windows.h>
#include "cBasePlayer.h"
#include "interfaces.h"
class edgeRagebot {
public:
	void cmdMove(CUserCmd* cmd) {
		cBasePlayer* local = (cBasePlayer*)interfaceManager::ientitylist->getClientEntity(interfaceManager::iengine->GetLocalPlayer());
		if (Functions::is_bad_ptr(local)) return;
		if (local->m_iHealth() <= 0) return;
		syncConfigurations(local);
		if (!enabled) return;
		if (!Functions::is_bad_ptr(target)) {
			//We've got a valid entity, so atleast he isnt shit last frame
			if (target->m_iHealth() <= 0 ||
				target->nDormant()) {
				//Target is dead or less so delete and find new one
				target = nullptr; 
				findNewTarget();
			}
			else {
				//Nah he valid apparantly but idk maybe we can't hit him or something
				//This is where we find dat bone boi
				if (local->canSee(target, 0)) {
					//The head is visible so we can maybe just target that

				}
				else {
					Vector head = target->hitbox(0);
					float rot = (cmd->viewangles.y * 3.1415) / 180.0f;
					float pixelRadius = 25;
					Vector rightPos = { head.x + pixelRadius * cos(rot + 90),
									   head.y + pixelRadius * sin(rot + 90),
									   head.z };
					Vector leftPos = { head.x + pixelRadius * cos(rot - 90),
									   head.y + pixelRadius * sin(rot - 90),
									   head.z };
					bool 
				}
				Vector velocity = target->m_vecVelocity();
				if (velocity.x == 0 &&
					velocity.y == 0 &&
					velocity.z == 0) {
					//They're completely still;
					//if (local->canSee(target)
				}
				else if (velocity.x == 0 && velocity.y == 0 
					&& velocity.z != 0){
					//They're falling in a straight direction
				}
				else if ((velocity.x != 0 || velocity.y != 0) &&
					velocity.z == 0) {
					//Theyre just moving on a plane
				}
				else if (velocity.x != 0 && velocity.y != 0
					&& velocity.z != 0) {
					//they're falling/flying
				}
			}
		}
	}
	void syncConfigurations(cBasePlayer* local) {

	}
	void findNewTarget() {

	}
private:
	cBasePlayer* target = nullptr;
	bool enabled = true;
};