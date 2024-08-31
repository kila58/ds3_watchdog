#pragma once

class PlayerContainer
{
private:
	PlayerBase* pointer = nullptr;

public:
	PlayerContainer(PlayerBase* ptr)
	{
		pointer = ptr;
	}

	PlayerBase* GetAddress() { return pointer; }
};

class Players
{
private:
	DWORD_PTR base;

	std::vector<PlayerContainer*> plys;

public:
	std::unique_ptr<PlayerContainer> GetPlayerFromIndex(int index);
	std::vector<PlayerContainer*> GetPlayers();

	bool Init();
	void StorePlayers();
	void ClearPlayers();
};

extern Players players;