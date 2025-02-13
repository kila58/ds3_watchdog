#include "watchdog.h"

DWORD __stdcall Init(LPVOID)
{
	if (proxy.Init())
	{
		if (!detection.Init() || !presenthook.Init())
			MessageBoxA(NULL, "Memory/hooking routines failed.", __FUNCTION__, MB_ICONERROR);
	}
	else
		MessageBoxA(NULL, "Unable to create proxy environment.", __FUNCTION__, MB_ICONERROR);

	return NULL;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			CreateThread(NULL, 0, Init, NULL, 0, NULL);
			break;
	}

	return TRUE;
}