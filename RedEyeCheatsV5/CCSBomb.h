#pragma once
#include <Windows.h>
#include "cBaseEntity.h"
class CCSBomb
{
public:
	NET(float, m_flC4Blow, xorStr("DT_PlantedC4"), xorStr("m_flC4Blow"));
	NET(float, m_flDefuseCountDown, xorStr("DT_PlantedC4"), xorStr("m_flDefuseCountDown"));
	NET(float, m_flDefuseLength, xorStr("DT_PlantedC4"), xorStr("m_flDefuseLength"));
	NET(HANDLE, m_hBombDefuser, xorStr("DT_PlantedC4"), xorStr("m_hBombDefuser"));
	NET(HANDLE, m_hOwnerEntity, xorStr("DT_PlantedC4"), xorStr("m_hOwnerEntity"));
};