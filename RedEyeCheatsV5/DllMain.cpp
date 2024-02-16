#include <WinSock2.h>
#include <Windows.h>
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include "Game.h"
#include "Functions.h"
#include "edgeAim.h"
#include "log.h"
#include "crashhandler.h"
#include "crashhandler.h"
#include "ReflectiveLoader.h"
#include <iomanip>
#define _CRTDBG_MAP_ALLOC

#define BUF_SIZE MAX_PATH + 1
#define new		new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define NDEBUG
#pragma comment(lib, "Ws2_32.lib")
LONG CALLBACK TopLevelHandler(EXCEPTION_POINTERS* info)
{
	/*
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
	
	*/
	DWORD exception = info->ExceptionRecord->ExceptionCode;
	if (EXCEPTION_ACCESS_VIOLATION == exception ||
		EXCEPTION_DATATYPE_MISALIGNMENT == exception ||
		EXCEPTION_BREAKPOINT == exception ||
		EXCEPTION_SINGLE_STEP == exception ||
		EXCEPTION_ARRAY_BOUNDS_EXCEEDED == exception ||
		EXCEPTION_FLT_DENORMAL_OPERAND == exception ||
		EXCEPTION_FLT_DIVIDE_BY_ZERO == exception ||
		EXCEPTION_FLT_INEXACT_RESULT == exception ||
		EXCEPTION_FLT_INVALID_OPERATION == exception ||
		EXCEPTION_FLT_OVERFLOW == exception ||
		EXCEPTION_FLT_STACK_CHECK == exception ||
		EXCEPTION_FLT_UNDERFLOW == exception ||
		EXCEPTION_INT_DIVIDE_BY_ZERO == exception ||
		EXCEPTION_INT_OVERFLOW == exception ||
		EXCEPTION_PRIV_INSTRUCTION == exception ||
		EXCEPTION_IN_PAGE_ERROR == exception ||
		EXCEPTION_ILLEGAL_INSTRUCTION == exception ||
		EXCEPTION_NONCONTINUABLE_EXCEPTION == exception ||
		EXCEPTION_STACK_OVERFLOW == exception ||
		EXCEPTION_INVALID_DISPOSITION == exception ||
		EXCEPTION_GUARD_PAGE == exception ||
		EXCEPTION_INVALID_HANDLE == exception) {

		crashhandler.handleCrash(exception);
		edgeaim.destroyCheat();
		edgeaim.statistics.writeStatistics();
		FreeLibraryAndExitThread(Game::gameModule, EXIT_SUCCESS);
		RemoveVectoredExceptionHandler(edgeaim.exceptionHandle);
	}

	

	return EXCEPTION_CONTINUE_SEARCH;
}
bool done = false;

//removed security for release


DWORD WINAPI Thread(LPVOID reserve)
{
	

	if (Functions::modulesPresent(30000, { L"engine.dll",L"client.dll",
									L"materialsystem.dll",L"vguimatsurface.dll",
									L"vgui2.dll",L"inputsystem.dll",L"vstdlib.dll",
									L"localize.dll"}) == WAIT_TIMEOUT) {
		return FALSE;
	}
	Game::gameModule = static_cast<HMODULE>(reserve);
	if (!done) {
		edgeaim.exceptionHandle = AddVectoredExceptionHandler(TRUE, TopLevelHandler);
		if (edgeaim.exceptionHandle == NULL) {
			MessageBoxA(NULL, xorStr("Critical error occured setting up crash handler, please post on forum"), xorStr("[REDEYECHEATSV5]"), NULL);
		}
		done = true;
	}
	edgeaim.setupCheat(reserve);
	return 0;
}

extern HINSTANCE hAppInstance;
HINSTANCE exhinstDLL;
BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserve) {
	if (reason == DLL_QUERY_HMODULE) {
		if (reserve != NULL)
			*(HMODULE*)reserve = hAppInstance;
	}
	else if (reason == DLL_PROCESS_ATTACH) {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		DisableThreadLibraryCalls(dll);
		exhinstDLL = dll;
		CreateThread(nullptr, NULL, Thread, dll, NULL, nullptr);
		return TRUE;
	}
	else if (reason == DLL_PROCESS_DETACH || reason == DLL_THREAD_DETACH) {
		if (reserve == nullptr) {
			//edgeaim.destroyCheat();
			//MessageBoxA(NULL, xorStr("Error"), xorStr("Critical Shutdown - Please restart the client and reinject"), NULL);
			//RemoveVectoredExceptionHandler(edgeaim.exceptionHandle);
		}
		return TRUE;
	}
	return TRUE;
}