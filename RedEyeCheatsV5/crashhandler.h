#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "xor.h"
#include "log.h"
#include "Game.h"
class crashHander {
public:
	void handleCrash(DWORD crash) {
		if (debugData == "_IGNR")
			return;
		if (debugData == "LOCKEND")
			return;
		if (debugData == "LOCK")
			return;
		if (debugData == "clipend")
			return;
		std::string exceptionText = "UNKNOWN";
		switch (crash) {
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			exceptionText = xorStr("0x1");
			break;
		case EXCEPTION_ACCESS_VIOLATION:
			exceptionText = xorStr("0x2");
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			exceptionText = xorStr("0x3");
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			exceptionText = xorStr("0x4");
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			exceptionText = xorStr("0x5");
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			exceptionText = xorStr("0x6");
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			exceptionText = xorStr("0x7");
			break;
		case EXCEPTION_FLT_OVERFLOW:
			exceptionText = xorStr("0x8");
			break;
		case EXCEPTION_FLT_STACK_CHECK:
			exceptionText = xorStr("0x9");
			break;
		case EXCEPTION_INT_OVERFLOW:
			exceptionText = xorStr("0xA");
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			exceptionText = xorStr("0xB");
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			exceptionText = xorStr("0xC");
			break;
		case EXCEPTION_IN_PAGE_ERROR:
			exceptionText = xorStr("0xD");
			break;
		case EXCEPTION_STACK_OVERFLOW:
			exceptionText = xorStr("0xE");
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			exceptionText = xorStr("0xF");
			break;
		case EXCEPTION_INVALID_HANDLE:
			exceptionText = xorStr("0xG");
			break;
		default:
			break;
		}
		
		std::string data = xorStr("Oops, it looks like RedEyeCheats has encountered an error.\nPLEASE post about this issue: redeyecheats.com/threads/cheat-crash-feedback.31560/\nError Code : ") + exceptionText + xorStr("\nError Type:") + debugData + xorStr("\nResolution:") + std::to_string(Game::m_iWidth) + xorStr(":") + std::to_string(Game::m_iHeight);
		data += +xorStr("\n. Please post this unique error code on the forum \n Please force-close CSGO via task manager if this message does not disappear");
		
		MessageBoxA(NULL, data.c_str(), xorStr("Red Eye Cheats V5"), MB_OK);
	}
	void messageBox(std::string data) {
		MessageBoxA(NULL, data.c_str(), xorStr("Red Eye Cheats V5"), NULL);
	}
	bool fileExists(const char* _path)
	{
		std::ifstream infile(_path);
		bool g = infile.good();
		infile.close();
		return g;
	}
	void setDebug(std::string debugdata) {
		//if (logger.logging)
		//	logger.LogString(debugdata);
		debugData = debugdata;
	}
	void writeToDebugLog(const char* data, ...) {
		if (path == "") {
			char* appdata = nullptr; size_t sz = 0;
			_dupenv_s(&appdata, &sz, xorStr("APPDATA"));
			std::string dir = appdata; dir += xorStr("\\VPXA_3432\\");
			path = dir;
			free(appdata);
		}
		if (!fileExists(path.c_str()))
			CreateDirectory(path.c_str(), NULL);
		std::string m_sSettingDirectory = path + xorStr("crashlog2.rec");
		std::ofstream file;
		file.open(m_sSettingDirectory.c_str());
		if (!file) {
			MessageBoxA(NULL, xorStr("Unable to write to crash-log file"), xorStr("Red Eye Cheats V5"), NULL);
			return;
		}
		file << data << std::endl;
		file.close();
		return;
	}
	void writeToLog(std::string data) {
		if (path == "") {
			char* appdata = nullptr; size_t sz = 0;
			_dupenv_s(&appdata, &sz, xorStr("APPDATA"));
			std::string dir = appdata; dir += xorStr("\\VPXA_3432\\");
			path = dir;
			free(appdata);
		}
		if (!fileExists(path.c_str()))
			CreateDirectory(path.c_str(), NULL);
		std::string m_sSettingDirectory = path + xorStr("crashlog.rec");
		std::ofstream file;
		file.open(m_sSettingDirectory.c_str());
		if (!file) {
			MessageBoxA(NULL, xorStr("Unable to write to crash-log file"), xorStr("Red Eye Cheats V5"), NULL);
			return;
		}
		file <<  data << std::endl;
		file.close();
		return;
	}
	std::string debugData = "";
private:
	std::string path = "";
};
extern crashHander crashhandler;