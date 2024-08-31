#include "watchdog.h"

bool Players::Init()
{
	base = SigScan("48 8B 1D ? ? ? 04 48 8B F9 48 85 DB ? ? 8B 11 85 D2 ? ? 8D", "DarkSoulsIII.exe");
	if (!base) return false;
	base += *(int*)(base + 3) + 7;

	/*auto localplayer = GetPlayerFromIndex(0);
	MessageBoxA(NULL, std::to_string((DWORD64)localplayer.get()->GetAddress()).c_str(), NULL, NULL);*/

	return true;
}

std::unique_ptr<PlayerContainer> Players::GetPlayerFromIndex(int index)
{
	int playersize = 0x38;

	multiptr<PlayerBase> player({ base, 0x40, (ptr)index * playersize});

	if (player == nullptr || !player)
		return nullptr;

	return std::make_unique<PlayerContainer>(player);
}

std::vector<PlayerContainer*> Players::GetPlayers()
{
	return plys;
}

void Players::StorePlayers()
{
	for (int i = 1; i < MAX_PLAYERS; i++)
	{
		auto ply = GetPlayerFromIndex(i);
		if (ply) plys.push_back(ply.get());
	}
}

void Players::ClearPlayers()
{
	plys.clear();
}

Players players;