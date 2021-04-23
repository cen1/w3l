#include "hooks.h"
#include "player-slot-helpers.h"

#ifdef __cplusplus
extern "C" {
#endif

// PlayerName
LPVOID getPlayerNameTextFrame(struct PlayerSlot* slot) {
	return slot->playerName->comboBox->firstTextFrame;
}

void initPlayerNameFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerNameTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerNameText(struct PlayerSlot* slot, const char* text) {
	textFrameSetText(getPlayerNameTextFrame(slot), text);
}

// PlayerRace
LPVOID getPlayerRaceTextFrame(struct PlayerSlot* slot) {
	return slot->playerRace->comboBox->firstTextFrame;
}

void initPlayerRaceFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerRaceTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerRaceText(struct PlayerSlot* slot, const char* text) {
	textFrameSetText(getPlayerRaceTextFrame(slot), text);
}

// PlayerTeam
LPVOID getPlayerTeamTextFrame(struct PlayerSlot* slot) {
	return slot->teamButtonTitle;
}

void initPlayerTeamFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerTeamTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerTeamText(struct PlayerSlot* slot, const char* text) {
	textFrameSetText(getPlayerTeamTextFrame(slot), text);
}

// PlayerHandicap
LPVOID getPlayerHandicapTextFrame(struct PlayerSlot* slot) {
	return slot->playerHandicap->comboBox->firstTextFrame;
}

void initPlayerHandicapFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerHandicapTextFrame(slot), fontPath, fontHeight, 0);
}

void setHandicapText(struct PlayerSlot* slot, const char* text) {
	textFrameSetText(getPlayerHandicapTextFrame(slot), text);
}

#ifdef __cplusplus
}
#endif 