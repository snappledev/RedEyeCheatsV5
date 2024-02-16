#include "inputManager.h"
#include <Windows.h>
#include <xutility>
#include "xor.h"
#include "interfaces.h"

inputManager inputmanager;


const char* key_[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, xorStr("0"), xorStr("1"), xorStr("2"), xorStr("3"), xorStr("4"), xorStr("5"), xorStr("6"), xorStr("7"), xorStr("8"), xorStr("9"), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, xorStr("a"), xorStr("b"), xorStr("c"), xorStr("d"), xorStr("e"), xorStr("f"), xorStr("g"), xorStr("h"), xorStr("i"), xorStr("j"), xorStr("k"), xorStr("l"), xorStr("m"), xorStr("n"), xorStr("o"), xorStr("p"), xorStr("q"), xorStr("r"), xorStr("s"), xorStr("t"), xorStr("u"), xorStr("v"), xorStr("w"), xorStr("x"),
xorStr("y"), xorStr("z"), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };


const char* keynum_[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, xorStr("0"), xorStr("1"), xorStr("2"), xorStr("3"), xorStr("4"), xorStr("5"), xorStr("6"), xorStr("7"), xorStr("8"), xorStr("9"), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

const char* keycap_[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, xorStr(")"), xorStr("!"), xorStr("'"), xorStr("£"), xorStr("$"), xorStr("%"), xorStr("^"), xorStr("&"), xorStr("*"), xorStr("("), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, xorStr("A"), xorStr("B"), xorStr("C"), xorStr("D"), xorStr("E"), xorStr("F"), xorStr("G"), xorStr("H"), xorStr("I"), xorStr("J"), xorStr("K"), xorStr("L"), xorStr("M"), xorStr("N"), xorStr("O"), xorStr("P"), xorStr("Q"), xorStr("R"), xorStr("S"), xorStr("T"), xorStr("U"), xorStr("V"), xorStr("W"), xorStr("X"),
xorStr("Y"), xorStr("Z"), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
void inputManager::updateFrame() {
	POINT cur; 
	GetCursorPos(&cur); 
	ScreenToClient(GetForegroundWindow(), &cur);
	cursor = Vector(cur.x, cur.y,0);
	std::copy(keyboardData, keyboardData + 255, oldKeyboardData);
	for (int i = 0; i < 255; i++)
		keyboardData[i] = GetAsyncKeyState(i); 

	static int iOldAnalogValue = 0;
	int iCurrAnalogWheelValue = interfaceManager::inputsys->GetAnalogValue(3);
	if (iOldAnalogValue != iCurrAnalogWheelValue)
	{
		int iDelta = iCurrAnalogWheelValue - iOldAnalogValue;

		bMouseDown = (iDelta == -1);
		bMouseUp = (iDelta == 1);
		if (bMouseDown == 1)
			downCurtime = interfaceManager::iglobal->curtime;
		if (bMouseUp == 1)
			upCurtime = interfaceManager::iglobal->curtime;
	}
	if ((interfaceManager::iglobal->curtime - downCurtime) > 0.15 && (bMouseDown == 1))
		bMouseDown = 0;
	if ((interfaceManager::iglobal->curtime - upCurtime) > 0.15 && (bMouseUp == 1))
		bMouseUp = 0;
	iOldAnalogValue = iCurrAnalogWheelValue;
}
bool inputManager::click(int key) {
	if (oldKeyboardData[key] == false && keyboardData[key] == true && key != -1)
		return true;
	return false;
}
bool inputManager::hold(int key) {
	if (keyboardData[key] == true && key != -1)
		return true;
	return false;
}
const char* inputManager::KeyToNumber(unsigned int key)
{
	
	return keynum_[key];
	

}
const char* inputManager::KeyToName(unsigned int key, bool capital)
{
	if (capital)
		return keycap_[key];
	return key_[key];

}
bool inputManager::inArea(int x, int y, int w, int h) {
	if (cursor.x > x && cursor.x < (x + w) && cursor.y > y && cursor.y < (y + h))
		return true;
	return false;
}