#pragma once
#include <windows.h>
#include <stdint.h>

struct SlotComboBox {
	int8_t pad208[208];
	int32_t f208;
	int8_t padFirstTextFrame[272];
	// "StandardPopupMenuTitleTextTemplate"
	LPVOID firstTextFrame; // 0x1E4
};

struct SubData {
	int8_t pad208[208];
	int32_t f208;
};

struct ComboBoxData {
	int8_t pad12[8];
	struct SubData* f0;
	uint32_t f12;
	uint32_t f16;
	int8_t padComboBox[464];
	struct SlotComboBox* comboBox; // 464
	struct SlotComboBox* comboBox_2_unk; // 468
};

//int32_t gets_race_text_frame_from_ecx_(struct s0* ecx) {
// s0 = playerSlot
struct PlayerSlot {
	int8_t padInternalSlotNumber[396];
	uint32_t internalSlotNumber;
	int8_t padDownloadValue_unk[12];
	struct ComboBoxData* downloadValue_unk; // DownloadValue (412)
	struct ComboBoxData* playerName; // NameMenu (416)
	struct ComboBoxData* playerRace; // RaceMenu (420)
	struct ComboBoxData* teamButton_unk; // TeamButton
	//struct ComboBoxData* playerRace_428; // 
	int8_t pad4[4];
	struct ComboBoxData* teamButtonTitle; // TeamButtonTitle
	struct ComboBoxData* teamButtonArrow_unk; // TeamButtonArrow
	struct ComboBoxData* ColorButtonValue_unk; // ColorButtonValue
	struct ComboBoxData* ColorButtonArrow_unk; // ColorButtonArrow
	struct ComboBoxData* playerHandicap; // HandicapMenu (448)
	int8_t pad456[4];
	int32_t slotNumber;
	//int8_t pad440[16];
	//int32_t f440;
};

// a bit dirty with string lengths, but it works so far :/
struct lobbyMapInfo {
	int8_t pad49[49];
	uint8_t f49;
	int8_t pad84[34];
	char mapPath[54];
	char creator[53];
};
