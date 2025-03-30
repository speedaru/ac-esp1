#pragma once
#define NOMINMAX
#include <algorithm>

#include "assaultcube.h"
#include "gldraw.h"
#include "gltext.h"

#include "offsets.h"
#include "hack.h"

class ESP : public Hack {
private:
	// scaling (windowed mode)
	const int VIRTUAL_SCREEN_WIDTH = 800;
	const int VIRTUAL_SCREEN_HEIGHT = 600;
	const int GAME_UNIT_MAGIC = 400; // unit like meter in game

	const float PLAYER_HEIGHT = 5.25f;
	const float PLAYER_WIDTH = 2.0f;
	const float EYE_HEIGHT = 4.5f;
	const float HEAD_SIZE = PLAYER_HEIGHT - EYE_HEIGHT;

	const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

	const int ESP_FONT_HEIGHT = (int)gl_draw::CONSOLAS_TEXT_HEIGHT;
	const int ESP_FONT_WIDTH = (int)gl_draw::CONSOLAS_TEXT_WIDTH;

	int* gamemode = reinterpret_cast<int*>(offsets::ac_client::base + offsets::ac_client::gamemode);
	int* numOfPlayers = reinterpret_cast<int*>(offsets::ac_client::base + offsets::ac_client::gamemodePlayerCount);
	float* matrix = reinterpret_cast<float*>(offsets::ac_client::base + offsets::ac_client::matrix2);
	Entity* localPlayer = *reinterpret_cast<Entity**>(offsets::ac_client::base + offsets::ac_client::localPlayer);
	EntityList* entityList = *reinterpret_cast<EntityList**>(offsets::ac_client::base + offsets::ac_client::entityList);

	// specific to opengl (3th and 4th variable is window w, h)
	// used to get window w, h
	int viewport[4];
public:
	bool IsTeamGame();
	bool IsEnemy(Entity* ent);
	bool IsValidEnt(Entity* ent);

	void DrawESPBox(Entity* ent);
	//void DrawESPBox(Entity* ent, vec3 screen);
	void Draw();

	void On() override;
	void Off() override;
private:
	vec3 CalculateWidthOffset(Entity* ent);
};