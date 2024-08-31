#pragma once

#define MAX_PLAYERS 6

class PlayerGameData
{
public:
	char pad0[0x18];
	int health;
	int health_max;
	char pad1[0x24];
	int stat_vigor;
	int stat_attunement;
	int stat_endurance;
	int stat_strength;
	int stat_dexterity;
	int stat_intellegence;
	int stat_faith;
	int stat_luck;
	char pad2[0x8];
	int stat_vitality;
	int level;
	char pad3[0x14];
	wchar_t name[32];
};

class PhysicsModule
{
public:
	char pad0[0x80];
	Vector position;
};

class PhysicsContainer
{
public:
	char pad0[0x28];
	PhysicsModule* physics;

	void SetPosition(Vector pos)
	{
		if (physics)
			physics->position = pos;
	}
};

class PlayerBase
{
public:
	char pad0[0x18];
	PhysicsContainer* physics_container;
	char pad1[0x50];
	int phantom_type;

	PhysicsContainer* GetPhysics()
	{
		return physics_container;
	}

	PlayerGameData* GetPlayerData()
	{
		return multiptr<PlayerGameData>({ (DWORD_PTR)this, /*xb*/0x1FA0 });
	}
};