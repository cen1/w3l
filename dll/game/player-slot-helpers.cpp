#include "hooks.h"
#include "player-slot-helpers.h"

#ifdef __cplusplus
extern "C" {
#endif

// PlayerName
LPVOID getPlayerNameTextFrame(struct PlayerSlot* slot) {
	if (!slot || !slot->playerName || !slot->playerName->comboBox) {
		return NULL;
	}
	return slot->playerName->comboBox->firstTextFrame;
}

void initPlayerNameFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerNameTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerNameText(struct PlayerSlot* slot, const char* text) {
	LPVOID textFrame = getPlayerNameTextFrame(slot);
	if (textFrame) {
		textFrameSetText(textFrame, text);
	}
}

// PlayerRace
LPVOID getPlayerRaceTextFrame(struct PlayerSlot* slot) {
	if (!slot || !slot->playerRace || !slot->playerRace->comboBox) {
		return NULL;
	}
	return slot->playerRace->comboBox->firstTextFrame;
}

void initPlayerRaceFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerRaceTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerRaceText(struct PlayerSlot* slot, const char* text) {
	LPVOID textFrame = getPlayerRaceTextFrame(slot);
	if (textFrame) {
		textFrameSetText(textFrame, text);
	}
}

// PlayerTeam
LPVOID getPlayerTeamTextFrame(struct PlayerSlot* slot) {
	if (!slot || !slot->teamButtonTitle) {
		return NULL;
	}
	return slot->teamButtonTitle;
}

void initPlayerTeamFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerTeamTextFrame(slot), fontPath, fontHeight, 0);
}

void setPlayerTeamText(struct PlayerSlot* slot, const char* text) {
	LPVOID textFrame = getPlayerTeamTextFrame(slot);
	if (textFrame) {
		textFrameSetText(textFrame, text);
	}
}

// PlayerHandicap
LPVOID getPlayerHandicapTextFrame(struct PlayerSlot* slot) {
	if (!slot || !slot->playerHandicap || !slot->playerHandicap->comboBox) {
		return NULL;
	}
	return slot->playerHandicap->comboBox->firstTextFrame;
}

void initPlayerHandicapFont(struct PlayerSlot* slot, const char* fontPath, float fontHeight) {
	textFrameInitFont(getPlayerHandicapTextFrame(slot), fontPath, fontHeight, 0);
}

void setHandicapText(struct PlayerSlot* slot, const char* text) {
	LPVOID textFrame = getPlayerHandicapTextFrame(slot);
	if (textFrame) {
		textFrameSetText(textFrame, text);
	}
}

#ifdef __cplusplus
}
#endif 