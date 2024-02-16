#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include "xor.h"
class Log
{
public:
	void BeginLog();
	void LogString(std::string text);
	bool LogPrint(const char* fmt, ...);
	void EndLog();
	bool logging = false;
private:
	std::string path = "";
	std::fstream file;
	HANDLE _out = NULL, _old_out = NULL;
	HANDLE _err = NULL, _old_err = NULL;
	HANDLE _in = NULL, _old_in = NULL;
	std::string logstring;
};
extern Log logger;