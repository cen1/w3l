#pragma once
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

void setPlayerNameText(struct PlayerSlot* slot, const char* text);
void setPlayerRaceText(struct PlayerSlot* slot, const char* text);

void setPlayerTeamText(struct PlayerSlot* slot, const char* text);

void setHandicapText(struct PlayerSlot* slot, const char* text);
void initPlayerNameFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight);
void initPlayerRaceFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight);
void initPlayerTeamFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight);
void initPlayerHandicapFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight);

#ifdef __cplusplus
}
#endif