#pragma once

#include "structures.h"
#include "offsets.h"

	
__declspec(dllexport) void __stdcall onGameTerminate(void);

__declspec(dllexport) void __stdcall onLobbyJoin(void);

__declspec(dllexport) void __stdcall onLobbyDestroy(void);

__declspec(dllexport) void __stdcall onGameStart(void);

__declspec(dllexport) int __stdcall isDefaultUpdatingTeamTextDisabled(void);

__declspec(dllexport) void __stdcall onLobbyInitStart(void);
__declspec(dllexport) void __stdcall onLobbyGameInfo(struct lobbyMapInfo * lobby_info);

__declspec(dllexport) void __stdcall onPostLobbyLeave(char* nickname);

__declspec(dllexport) void __stdcall onSlotChange(struct PlayerSlot* slot, char* nickname);

__declspec(dllexport) void __stdcall onAfterSlotInit(struct PlayerSlot* slot);
__declspec(dllexport) void __stdcall afterSlotTextsUpdate(struct PlayerSlot* slot);


#ifdef __cplusplus
extern "C" {
#endif

	int enhancement_patch(char *game_dll_base);

#ifdef __cplusplus
}
#endif

void __stdcall textFrameSetText(void *textFrame, const char* text);

void __declspec(dllexport) __stdcall textFrameInitFont(void *textFrame, const char* fontPath, float fontHeight, uint32_t arg3);


typedef const char*(__fastcall * skinGetPathByName_def)(const char* name, const char* type);
extern skinGetPathByName_def skinGetPathByName;
