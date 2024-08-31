#include "watchdog.h"

using PresentType = long(__stdcall*)(IDXGISwapChain*, UINT, UINT);
PresentType original_function;

ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;

long __stdcall Present(IDXGISwapChain* swapchain, UINT syncinterval, UINT flags)
{
	static D3D11Renderer* renderer;
	if (!renderer)
	{
		renderer = new D3D11Renderer(swapchain);
		if (!renderer->Initialize())
		{
			MessageBox(NULL, "Renderer failed to initialize.", "Renderer Error", MB_ICONERROR);

			delete renderer;
			renderer = nullptr;
		}
	}

	renderer->BeginScene();

	players.StorePlayers();

	renderer->FillRect(3, 30, 20, 20, Color(130, 220, 160, 255));

	renderer->DrawString(13, 3, 3, Color(255, 255, 255, 255), "DS3Watchdog 1.0b", true);

	detection.Frame(renderer);

	players.ClearPlayers();

	renderer->EndScene();

	return original_function(swapchain, syncinterval, flags);
}

LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
bool PresentHook::Init()
{
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle("dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);

	IDXGISwapChain* swapchain;

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "win", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("win", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, requestedLevels, sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL), 
		D3D11_SDK_VERSION, &scd, &swapchain, &device, &obtainedLevel, &context)))
		return false;

	DWORD_PTR* table = (DWORD_PTR*)swapchain;
	table = (DWORD_PTR*)table[0];

	if (MH_Initialize() != MH_OK)
		return false;

	if (MH_CreateHook((DWORD_PTR*)table[8], Present, (LPVOID*)&original_function) != MH_OK)
		return false;

	if (MH_EnableHook((DWORD_PTR*)table[8]) != MH_OK)
		return false;

	DWORD old;
	VirtualProtect(original_function, 2, PAGE_EXECUTE_READWRITE, &old);

	return true;
}

PresentHook presenthook;