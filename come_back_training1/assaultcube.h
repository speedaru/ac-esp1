#pragma once
#include <cstdint>

#include "structs.h"
#include "geom.h"

class Weapon {
public:
	uint32_t vTable; //0x0000
	int32_t id; //0x0004
	class Entity* owner; //0x0008
	uint32_t* guninfo; //0x000C
	int32_t* reserveAmmo; //0x0010
	int32_t* ammo; //0x0014
	char pad_0018[4]; //0x0018
	int32_t shots_fired; //0x001C
	char pad_0020[244]; //0x0020
}; //Size: 0x0114

class Entity {
public:
	uint32_t vTable; //0x0000
	vec3 head; //0x0004
	char pad_0010[36]; //0x0010
	vec3 pos; //0x0034
	vec3 viewAngle; //0x0040
	char pad_004C[37]; //0x004C
	uint8_t scoping; //0x0071
	char pad_0072[134]; //0x0072
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[252]; //0x0100
	int32_t frags; //0x01FC
	char pad_0200[4]; //0x0200
	int32_t deaths; //0x0204
	char pad_0208[28]; //0x0208
	uint8_t attacking; //0x0224
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	uint8_t team; //0x032C
	char pad_032D[11]; //0x032D
	uint8_t isDead; //0x0338
	char pad_0339[59]; //0x0339
	class Weapon* currentWeapon; //0x0374
	char pad_0378[232]; //0x0378
}; //Size: 0x0460

struct EntityList{
	Entity* ents[31];
};