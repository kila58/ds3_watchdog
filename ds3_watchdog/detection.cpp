#include "watchdog.h"

bool Detection::Init()
{
	/*base_a = SigScan("48 8B 05 ? ? ? ? 48 85 C0 ? ? 48 8b 40 ? C3", "DarkSoulsIII.exe");
	if (!base_a) return false;
	base_a += *(int*)(base_a + 3) + 7;*/

	/*base_b = SigScan("48 8B 1D ? ? ? 04 48 8B F9 48 85 DB ? ? 8B 11 85 D2 ? ? 8D", "DarkSoulsIII.exe");
	if (!base_b) return false;
	base_b += *(int*)(base_b + 3) + 7;*/

	/*DWORD_PTR xb_add = SigScan("48 8B 83 ? ? ? ? 48 85 C0 ? ? E8  ? ? ? ? 8b ? ? 48", "DarkSoulsIII.exe");
	if (!xb_add) return false;
	xb = *(int*)xb_add + 3;

	xc = 0x950;*/

	if (!players.Init())
		return false;

	return true;
}

bool StatsWithinBounds(PlayerGameData* player, int& level)
{
	int true_level = (player->stat_vigor + player->stat_attunement + player->stat_endurance + player->stat_vitality + player->stat_strength + player->stat_dexterity
		+ player->stat_intellegence + player->stat_faith + player->stat_luck) - 89/*level-less points*/;

	level = true_level;

	return (true_level == player->level && player->health <= player->health_max && player->health < 2500);
}

void Detection::Frame(D3D11Renderer* renderer)
{
	static int i = 1;

	for (auto container : players.GetPlayers())
	{
		PlayerGameData* player = container->GetAddress()->GetPlayerData();
		if (!player)
			continue;

		std::wstring name(player->name);
		std::string stats(name.begin(), name.end());
		stats = std::to_string(i) + ". " + stats + "  SL " + std::to_string(player->level);

		int true_level;
		if (!StatsWithinBounds(player, true_level))
		{
			stats += "  |  Actual SL " + std::to_string(true_level) + "   /"
				+ std::to_string(player->stat_vigor) + "/" + std::to_string(player->stat_attunement) + "/" + std::to_string(player->stat_endurance) + "/"
				+ std::to_string(player->stat_vitality) + "/" + std::to_string(player->stat_strength) + "/" + std::to_string(player->stat_dexterity) + "/"
				+ std::to_string(player->stat_intellegence) + "/" + std::to_string(player->stat_faith) + "/" + std::to_string(player->stat_luck) + "/ ";

			/*multiptr<PlayerBase> playerbase({ base_b, 0x40, (ptr)i * 0x38 });
			if (playerbase)
				playerbase->pahntom_type = 1;*/

			//if (GetAsyncKeyState(VK_F1) & 0x8000)
				//container->GetAddress()->GetPhysics()->SetPosition(Vector(9999, -9999, 9999));

			renderer->DrawString(13, 3, 20 + (16 * i), Color(255, 20, 20, 255), stats, true);
		}
		else
			renderer->DrawString(13, 3, 20 + (16 * i), Color(255, 255, 255, 255), stats, true);

		i++;
	}

	i = 1;
}

Detection detection;