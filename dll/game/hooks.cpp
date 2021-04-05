// what the hell are those directives lol
#ifdef _MSC_VER
#undef UNICODE
#if _MSC_VER > 1400
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include "hooks.h"
#include "hook-handlers.h"
#include "globals.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

LPVOID gameTerminateRestorePtr;
LPVOID lobbyInitStartRestorePtr;
LPVOID lobbyGameInfoRestorePtr;
LPVOID gameStartRestorePtr;
LPVOID lobbyDestroyRestorePtr;
LPVOID pingMinimapExRestorePtr;
LPVOID minimapSignalRestorePtr;
LPVOID minimapSignalEndPtr;
LPVOID afterSlotInitRestorePtr;
LPVOID textFrameInitFontPtr;
LPVOID textFrameSetTextPtr;
LPVOID slotChangeEventRestorePtr;
LPVOID afterSlotTextUpdateRestorePtr;
LPVOID game_6FAAE350;
LPVOID game_6F5BE670;
LPVOID game_6FAAE140;
LPVOID game_6F5BE680;
LPVOID game_6F5BCEF0;
LPVOID game_6F5AFC24;
LPVOID postLobbyLeaveRestorePtr;
LPVOID globalMapInfoPtr;
LPVOID playerTeamUpdateTextRestorePtr;

skinGetPathByName_def skinGetPathByName;

int saveeax = 0;

LPVOID GAME_GlobalClass;
LPVOID GAME_PrintToScreen;

LPVOID comboBoxIterRestorePtr;
LPVOID comboBoxItemFillerInvocatorPtr;


void __declspec(dllexport) __declspec(naked) __cdecl lobbyInitStartHook() {
	__asm {
		pushad
		call onLobbyInitStart
		popad
		sub esp, 0x3B0
		; @todo optimize those dword ptr
		mov eax, game_6FAAE140
		mov eax, dword ptr ds : [eax]
		jmp lobbyInitStartRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl lobbyGameInfoHook() {
	__asm {
		mov saveeax, eax
		lea eax, ss:[esp + 0xB8]
		pushad
		push eax
		call onLobbyGameInfo
		popad
		mov eax, saveeax
		test eax, eax
		je deer_line
		mov edi, 0x1
		deer_line:
		mov ecx, dword ptr ds : [esi + 0x204]
		jmp lobbyGameInfoRestorePtr
	}
}


void __declspec(dllexport) __declspec(naked) __cdecl lobbyDestroyHook() {
	__asm {
		pushad
		call onLobbyDestroy
		popad
		push esi
		mov esi, ecx
		call game_6F5BE680
		jmp lobbyDestroyRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl gameStartHook() {
	__asm {
		pushad
		call onGameStart
		popad
		mov edx, dword ptr ds : [esi + 0x1C68]
		push ebx
		push edx
		jmp gameStartRestorePtr
	}
}

BOOL PlantDetourJMP(BYTE* source, const BYTE* destination, size_t length) {
	DWORD oldProtection;
	BOOL bRet = VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &oldProtection);

	if (bRet == FALSE)
		return FALSE;

	source[0] = 0xE9;
	*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;

	for (unsigned int i = 5; i < length; i++)
		source[i] = 0x90;

	VirtualProtect(source, length, oldProtection, &oldProtection);

	return TRUE;
}


void __stdcall textFrameSetText(void *textFrame, const char* text) {
	__asm {
		push text
		mov ecx, textFrame
		call textFrameSetTextPtr
	}
}

void __declspec(dllexport) __stdcall textFrameInitFont(void *textFrame, const char* fontPath, float fontHeight, uint32_t arg3 = 0) {
	__asm {
		push 0
		push fontHeight
		push fontPath
		mov ecx, textFrame
		call textFrameInitFontPtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl slotChangeEventHook() {
	__asm {
		pushad
		push ebp
		push ecx
		call onSlotChange
		popad
		push esi
		mov esi, ecx
		mov ecx, dword ptr ss : [esp + 0x8]
		jmp slotChangeEventRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl afterSlotTextUpdateHook() {
	__asm {
		pushad
		push edi
		call afterSlotTextsUpdate
		popad
		call game_6F5BE670
		jmp afterSlotTextUpdateRestorePtr
	}
}


void TextPrint(char *szText, float fDuration)
{
	DWORD dwDuration = *((DWORD *)&fDuration);

	__asm
	{
		PUSH	0xFFFFFFFF
		PUSH	dwDuration
		PUSH	szText
		PUSH	0x0
		PUSH	0x0
		MOV		ECX, [GAME_GlobalClass]
		MOV		ECX, [ECX]
		CALL	GAME_PrintToScreen
	}
}

/*int signalCounter = 0;
void __declspec(dllexport) __declspec(naked) __cdecl minimapSignalHook() {
	__asm {
		pushad
	}

	signalCounter++;

	if (signalCounter % 2 == 0) {
		TextPrint("|c00FFFF00Stop spamming you|r |cFFFF0000moose|r", 10.0f);
		__asm {
			popad
			ret 0x18
		}
	}
	__asm {
		popad
		sub esp, 0x10
		push ebx
		push ebp
		jmp minimapSignalRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __stdcall pingMinimapExHook() {
	__asm {
		pushad
		popad
		sub esp, 0x10
		xor edx, edx
		jmp pingMinimapExRestorePtr
	}
}*/

void __declspec(dllexport) __declspec(naked) __cdecl afterSlotInitHook() {
	__asm {
		pushad
		push esi
		call onAfterSlotInit
		popad
		mov ecx, dword ptr ss : [esp + 0x108]
		pop edi
		pop esi
		jmp afterSlotInitRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl gameTerminateHook() {
	__asm {
		pushad
		call onGameTerminate
		popad
		push esi
		; @todo optimize those dword ptr
		mov saveeax, eax
		mov eax, game_6FAAE350
		mov dword ptr ds : [eax], 0
		mov eax, saveeax
		jmp gameTerminateRestorePtr
	}
}


void __declspec(dllexport) __declspec(naked) __cdecl postLobbyLeaveHook() {
	__asm {
		pushad
		mov saveeax, eax
		add eax, 0x19
		push eax
		call onPostLobbyLeave
		mov eax, saveeax
		popad
		movzx ecx, byte ptr ds : [edi + 0x18]
		push ecx
		jmp postLobbyLeaveRestorePtr
	}
}

void __declspec(dllexport) __declspec(naked) __cdecl playerTeamUpdateTextHook() {
	__asm {
		pushad
		call isDefaultUpdatingTeamTextDisabled
		cmp eax, 1
		popad
		je justend

		mov eax, game_6FAAE140
		mov eax, dword ptr ds : [eax]
		jmp playerTeamUpdateTextRestorePtr

		justend:
		add esp, 0x44
		ret 4
	}
}

int enhancement_patch(char *game_dll_base) {
	*(int*)&textFrameSetTextPtr = (int)game_dll_base + textFrameSetTextOffset;
	*(int*)&textFrameInitFontPtr = (int)game_dll_base + textFrameInitFontOffset;
	*(int*)&game_6F5BE670 = (int)game_dll_base + 0x5BE670;
	// @todo: optimize usage of this one in ASM
	*(int*)&game_6FAAE140 = (int)game_dll_base + 0xAAE140;
	*(int*)&game_6F5BCEF0 = (int)game_dll_base + 0x5BCEF0;

	*(int*)&game_6F5AFC24 = (int)game_dll_base + 0x5AFC24;

	*(int*)&GAME_PrintToScreen = (int)game_dll_base + 0x2F8E40;


	*(int*)&skinGetPathByName = (int)game_dll_base + 0x31F530;

	// after player slot init
	PlantDetourJMP((BYTE*)(game_dll_base + afterSlotInitJmpOffset), (BYTE*)afterSlotInitHook, 9);
	*(int*)&afterSlotInitRestorePtr = (int)game_dll_base + afterSlotInitRestoreOffset;

	// game terminate hook
	PlantDetourJMP((BYTE*)(game_dll_base + gameTerminateJmpOffset), (BYTE*)gameTerminateHook, 5);
	*(int*)&gameTerminateRestorePtr = (int)game_dll_base + gameTerminateRestoreOffset;
	*(int*)&game_6FAAE350 = (int)game_dll_base + 0xAAE350;

	// lobby init hook
	PlantDetourJMP((BYTE*)(game_dll_base + lobbyInitStartJmpOffset), (BYTE*)lobbyInitStartHook, 5);
	*(int*)&lobbyInitStartRestorePtr = (int)game_dll_base + lobbyInitStartRestoreOffset;

	// lobby init, has game info
	PlantDetourJMP((BYTE*)(game_dll_base + lobbyGameInfoJmpOffset), (BYTE*)lobbyGameInfoHook, 5);
	*(int*)&lobbyGameInfoRestorePtr = (int)game_dll_base + lobbyGameInfoRestoreOffset;
	
	// lobby destroy hook
	PlantDetourJMP((BYTE*)(game_dll_base + lobbyDestroyJmpOffset), (BYTE*)lobbyDestroyHook, 5);
	*(int*)&lobbyDestroyRestorePtr = (int)game_dll_base + lobbyDestroyRestoreOffset;
	*(int*)&game_6F5BE680 = (int)game_dll_base + 0x5BE680;

	// post lobby leave hook
	PlantDetourJMP((BYTE*)(game_dll_base + postPlayerLeaveJmpOffset), (BYTE*)postLobbyLeaveHook, 5);
	*(int*)&postLobbyLeaveRestorePtr = (int)game_dll_base + postPlayerLeaveRestoreOffset;
	
	// start of the game hook
	PlantDetourJMP((BYTE*)(game_dll_base + gameStartJmpOffset), (BYTE*)gameStartHook, 5);
	*(int*)&gameStartRestorePtr = (int)game_dll_base + gameStartRestoreOffset;
	
	// slot change hook
	PlantDetourJMP((BYTE*)(game_dll_base + slotChangeEventJmpOffset), (BYTE*)slotChangeEventHook, 5);
	*(int*)&slotChangeEventRestorePtr = (int)game_dll_base + slotChangeEventRestoreOffset;
	
	// slot change after texts update hook
	PlantDetourJMP((BYTE*)(game_dll_base + afterSlotTextUpdateJmpOffset), (BYTE*)afterSlotTextUpdateHook, 5);
	*(int*)&afterSlotTextUpdateRestorePtr = (int)game_dll_base + afterSlotTextUpdateRestoreOffset;

	// player change after texts update hook
	PlantDetourJMP((BYTE*)(game_dll_base + playerTeamUpdateTextJmpOffset), (BYTE*)playerTeamUpdateTextHook, 5);
	*(int*)&playerTeamUpdateTextRestorePtr = (int)game_dll_base + playerTeamUpdateTextRestoreOffset;

	init_hook_handlers();

	return 0;

	// start of the minimap signal hook
	//PlantDetourJMP((BYTE*)(game_dll_base + minimapSignalJmpOffset), (BYTE*)minimapSignalHook, 5);
	//*(int*)&minimapSignalRestorePtr = (int)game_dll_base + minimapSignalRestoreOffset;
	//*(int*)&minimapSignalEndPtr = (int)game_dll_base + minimapSignalEndOffset;
}
