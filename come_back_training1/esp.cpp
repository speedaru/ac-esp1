#include "esp.h"


bool ESP::IsTeamGame() {
	switch (*gamemode) {
	case 0:
		return 1;
	case 4:
		return 1;
	case 5:
		return 1;
	case 7:
		return 1;
	case 11:
		return 1;
	case 13:
		return 1;
	case 14:
		return 1;
	case 16:
		return 1;
	case 17:
		return 1;
	case 20:
		return 1;
	case 21:
		return 1;
	default:
		return 0;
	}
}
bool ESP::IsEnemy(Entity* ent) {
	return localPlayer->team != ent->team;
}
bool ESP::IsValidEnt(Entity* ent) {
	if (ent) {
		if (ent->vTable == 0x4E4A98 || ent->vTable == 0x4E4AC0) {
			return true;
		}
	}
	return false;
}

void ESP::DrawESPBox(Entity* ent) {
    const Color color = (IsTeamGame() && !IsEnemy(ent)) ? gl_draw::rgb::green : gl_draw::rgb::red;

    // Define player width offset (half width along x-axis for simplicity)
    //vec3 widthOffset = { PLAYER_WIDTH / 2.0f, 0.0f, 0.0f };
    vec3 widthOffset = CalculateWidthOffset(ent);

    // Calculate four corners in world space
    vec3 headLeft = ent->head - widthOffset;
    vec3 headRight = ent->head + widthOffset;
    vec3 feetLeft = ent->pos - widthOffset;
    vec3 feetRight = ent->pos + widthOffset;

    // add head height
    headLeft.z = headRight.z += HEAD_SIZE;

    // Project to screen space
    vec3 screenHeadLeft, screenHeadRight, screenFeetLeft, screenFeetRight;
    bool allVisible = WorldToScreen(headLeft, screenHeadLeft, matrix, viewport[2], viewport[3]) &&
        WorldToScreen(headRight, screenHeadRight, matrix, viewport[2], viewport[3]) &&
        WorldToScreen(feetLeft, screenFeetLeft, matrix, viewport[2], viewport[3]) &&
        WorldToScreen(feetRight, screenFeetRight, matrix, viewport[2], viewport[3]);

    if (!allVisible) return; // Skip if any point fails (behind camera)

    // Draw perspective-corrected quad
    gl_draw::color = color;
    gl_draw::DrawLine(screenHeadLeft.x, screenHeadLeft.y, screenHeadRight.x, screenHeadRight.y, 2.f);
    gl_draw::DrawLine(screenHeadRight.x, screenHeadRight.y, screenFeetRight.x, screenFeetRight.y, 2.f);
    gl_draw::DrawLine(screenFeetRight.x, screenFeetRight.y, screenFeetLeft.x, screenFeetLeft.y, 2.f);
    gl_draw::DrawLine(screenFeetLeft.x, screenFeetLeft.y, screenHeadLeft.x, screenHeadLeft.y, 2.f);

    // Center text above the box (using head midpoint)
    float midX = (screenHeadLeft.x + screenHeadRight.x) / 2.0f;
    float width = screenHeadRight.x - screenHeadLeft.x; // Screen-space width
    float textX = gl_draw::CenterText(midX - width / 2.0f, width, (float)strlen(ent->name) * ESP_FONT_WIDTH);
    float textY = screenHeadLeft.y - 5; // Above top
    gl_draw::DisplayText(textX, textY, color, "%s", ent->name);
}

void ESP::Draw() {
    glGetIntegerv(GL_VIEWPORT, viewport);

    for (int i = 1; i < *numOfPlayers; i++) {
        if (!IsValidEnt(entityList->ents[i]) || entityList->ents[i]->isDead) {
            continue;
        }

        Entity* ent = entityList->ents[i];
        DrawESPBox(ent); // Pass entity directly, no single screen coord
    }
}

//void ESP::DrawESPBox(Entity* ent, vec3 screen) {
//	const GLubyte* color = nullptr;
//
//	if (IsTeamGame() && !IsEnemy(ent)) {
//		color = gl_draw::rgb::green;
//	}
//	else {
//		color = gl_draw::rgb::red;
//	}
//
//	float distance = localPlayer->pos.Distance(ent->pos);
//	float screenScale = ((float)viewport[2] / VIRTUAL_SCREEN_WIDTH);
//	float scale = (GAME_UNIT_MAGIC / distance) * screenScale; // [2]: width
//	float x = screen.x - scale;
//	float y = screen.y - scale * PLAYER_ASPECT_RATIO;
//	float width = scale * 2;
//	float height = scale * PLAYER_ASPECT_RATIO * 2;
//
//	if (!strcmp(ent->name, "Major_Headache")) {
//		printf("width, height:\t%.3f, %.3f\n", width, height);
//	}
//
//	gl_draw::DrawBox(x, y, width, height, color, 2.0f);
//
//	float textX = gl_draw::CenterText(x, width, (float)strlen(ent->name) * ESP_FONT_WIDTH);
//	float textY = y - 5;
//
//	gl_draw::DisplayText(textX, textY, color, "%s", ent->name);
//}
//void ESP::Draw() {
//	glGetIntegerv(GL_VIEWPORT, viewport);
//
//	for (int i = 1; i < *numOfPlayers; i++) {
//		// if not entity skip
//		if (!IsValidEnt(entityList->ents[i])) {
//			continue;
//		}
//
//		// skip dead players
//		if (entityList->ents[i]->isDead) {
//			continue;
//		}
//
//		Entity* ent = entityList->ents[i];
//
//		vec3 topleft = ent->head;
//		topleft.z -= PLAYER_HEIGHT / 2 - HEAD_SIZE;
//
//		vec3 screenCoords;
//		if (WorldToScreen(topleft, screenCoords, matrix, viewport[2], viewport[3])) {
//			DrawESPBox(ent, screenCoords);
//		}
//	}
//}


void ESP::On() {
	hackOn = true;
}
void ESP::Off() {
	hackOn = false;
}




// ----------------------- PRIVATE
vec3 ESP::CalculateWidthOffset(Entity* ent) {
    // Direction from local player to enemy
    vec3 VecToEnemy = ent->pos - localPlayer->pos;
    VecToEnemy.z = 0; // Flatten to XY plane
    float length = VecToEnemy.Length();
    if (length < 0.1f) return { PLAYER_WIDTH / 2.0f, 0.0f, 0.0f }; // Fallback when player behind
    
    // normalize vector, make it so it only represents direction, norm stays the same no matter the distance
    VecToEnemy = VecToEnemy / length;

    // get normal vec
    vec3 NormalVec = { -VecToEnemy.y, VecToEnemy.x, 0 };

    return NormalVec;
}