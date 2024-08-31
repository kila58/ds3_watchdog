#pragma once

// win
#include <Windows.h>
#include <Xinput.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// stl
#include <vector>
#include <memory>
#include <string>

// lib
#include "MinHook/include/MinHook.h"
#include "dx11renderer/D3D11Renderer.h"

// core
#include "sigscan.h"
#include "proxy.h"

// sdk
#include "sdk\vector.h"
#include "sdk\entities.h"

// watchdog
#include "players.h"
#include "detection.h"
#include "presenthook.h"