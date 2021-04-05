#pragma once
#define lobbyInitStartJmpOffset 0x5AF860
#define lobbyInitStartRestoreOffset 0x5AF86B

#define lobbyGameInfoJmpOffset 0x5AFC1B
#define lobbyGameInfoRestoreOffset 0x5AFC24

#define gameTerminateJmpOffset 0x7A50
#define gameTerminateRestoreOffset 0x7A5B

//#define lobbyJoinJmpOffset 0x551CB0
//#define lobbyJoinRestoreOffset 0x551CB8

// works only for self-quit, decent
#define lobbyDestroyJmpOffset 0x5C4120
#define lobbyDestroyRestoreOffset 0x5C4128

// works randomly, but enough
#define slotEventJmpOffset 0x443650
#define slotEventRestoreOffset 0x443655

#define postPlayerLeaveJmpOffset 0x54FE52
#define postPlayerLeaveRestoreOffset 0x54FE57

#define gameStartJmpOffset 0x5527FF
#define gameStartRestoreOffset 0x552807

//
#define comboBoxIterJmpOffset 0x5CF32E
#define comboBoxIterRestoreOffset 0x5CF333

#define comboBoxItemFillerInvocatorOffset 0x610EC0

#define pingMinimapExJmpOffset 0x3B8660
#define pingMinimapExRestoreOffset 0x3B8665
#define pingMinimapExEndOffset 0x3B86E1

#define minimapSignalJmpOffset 0x349300
#define minimapSignalRestoreOffset 0x349305
#define minimapSignalEndOffset 0x349516

#define afterSlotInitJmpOffset 0x5608CA
#define afterSlotInitRestoreOffset 0x5608D3

#define slotComboboxItemBeforeSetTextJmpOffset 0x610F1C
#define slotComboboxItemBeforeSetTextRestoreOffset 0x610F26

#define slotChangeEventJmpOffset 0x560470
#define slotChangeEventRestoreOffset 0x560477

#define textFrameInitFontOffset 0x5FB960
#define textFrameSetTextOffset 0x611D40

#define playerTeamUpdateTextJmpOffset 0x559193
#define playerTeamUpdateTextRestoreOffset 0x559198

#define afterSlotTextUpdateJmpOffset 0x560F38
//0x566308
#define afterSlotTextUpdateRestoreOffset 0x560F3D
//0x56630D
