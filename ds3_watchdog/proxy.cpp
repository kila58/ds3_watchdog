#include "watchdog.h"

HMODULE module; //xinput1_3.dll

bool Proxy::Init()
{
	char path[MAX_PATH];
	GetSystemDirectory(path, MAX_PATH);
	strcat_s(path, "\\xinput1_3.dll");
	module = LoadLibrary(path);

	return !!module;
}

template<class T>
T set_call(T& ptr, const char* name)
{
	if (!ptr)
		ptr = (T)GetProcAddress(module, name);

	return ptr;
}

template<class T>
T set_call(T& ptr, int ord)
{
	if (!ptr)
		ptr = (T)GetProcAddress(module, (const char*)ord);

	return ptr;
}

#pragma warning( disable: 4995 )
void WINAPI XInputEnable(BOOL state)
{
	static void (WINAPI *orig)(BOOL state);
	return set_call(orig, __FUNCTION__)(state);
}

DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation);
	return set_call(orig, __FUNCTION__)(dwUserIndex, devType, pBatteryInformation);
}

DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities);
	return set_call(orig, __FUNCTION__)(dwUserIndex, dwFlags, pCapabilities);
}

DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid);
	return set_call(orig, __FUNCTION__)(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke);
	return set_call(orig, __FUNCTION__)(dwUserIndex, dwReserved, pKeystroke);
}

DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, XINPUT_STATE *pState);
	return set_call(orig, __FUNCTION__)(dwUserIndex, pState);
}

DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);
	return set_call(orig, __FUNCTION__)(dwUserIndex, pVibration);
}

DWORD WINAPI XInputOrd100(DWORD dwUserIndex, XINPUT_STATE *pState)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, XINPUT_STATE *pState);
	return set_call(orig, "XInputGetState")(dwUserIndex, pState);
}

DWORD WINAPI XInputOrd101(DWORD dwUserIndex, DWORD unk, void* ptr)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex, DWORD unk, void* ptr);
	return set_call(orig, 101)(dwUserIndex, unk, ptr);
}

DWORD WINAPI XInputOrd102(DWORD dwUserIndex)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex);
	return set_call(orig, 102)(dwUserIndex);
}

DWORD WINAPI XInputOrd103(DWORD dwUserIndex)
{
	static DWORD(WINAPI *orig)(DWORD dwUserIndex);
	return set_call(orig, 103)(dwUserIndex);
}

Proxy proxy;