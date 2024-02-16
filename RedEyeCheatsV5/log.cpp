#include "log.h"
#include <stdio.h>
#include "xor.h"
#include "crashhandler.h"
Log logger;
void Log::BeginLog()
{
	_old_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_old_err = GetStdHandle(STD_ERROR_HANDLE);
	_old_in = GetStdHandle(STD_INPUT_HANDLE);
	::AllocConsole() && ::AttachConsole(GetCurrentProcessId());
	_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_err = GetStdHandle(STD_ERROR_HANDLE);
	_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(_out, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
	SetConsoleMode(_in, ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
	logging = true;
}

void Log::EndLog()
{
	if (_out && _err && _in) {
		FreeConsole();
		if (_old_out)
			SetStdHandle(STD_OUTPUT_HANDLE, _old_out);
		if (_old_err)
			SetStdHandle(STD_ERROR_HANDLE, _old_err);
		if (_old_in)
			SetStdHandle(STD_INPUT_HANDLE, _old_in);
	}
	logging = false;
}
bool Log::LogPrint(const char* fmt, ...)
{
	if (!_out)
		return false;

	char buf[1024];
	va_list va;

	va_start(va, fmt);
	_vsnprintf_s(buf, 1024, fmt, va);
	va_end(va);

	!!WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
}

void Log::LogString(std::string string)
{
	if (_out) {
		if (string == "lmao too big") {
			std::ofstream myfile;
			
			myfile.open("log.txt");
			myfile << logstring;
			myfile.close();
		}

		string.insert(0, "[ REDEYE ] - "); string += "\n";
		const char* str = string.c_str();
		char buf[1024];
		va_list va;
		va_start(va, str);
		_vsnprintf_s(buf, 1024, str, va);
		va_end(va);
		!!WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
		logstring += string;
	}
}