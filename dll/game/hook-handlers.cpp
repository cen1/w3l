#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <windows.h>
#include <map>
#include <ctime>
#include <string>
#include <atomic>
#include <cmath>

#include "../debug.h"
#include "globals.h"
#include "hooks.h"
#include "player-slot-helpers.h"
#include "LobbyInfo.h"
#include "PlayerInfo/PlayerInfo.h"
#include "PlayerInfo/LagabuseDotaPlayerInfo.h"
#include "PlayerInfoUpdater.h"

std::atomic<bool> is_in_lobby{ false };

LobbyInfo * lobby_info;
PlayerInfoUpdater * player_info_updater;

const char * default_font;

/*
* Todo list:
* [+] Support private lobbies too, find better way to detect map name and host name
* [+] Fix crash on exit
* Manage strtolower usage
* Urlencode nicknames
* [+] If possible, get rid of default strings being appeared in some special conditions
* Someday, get rid of default way of updating strings for handicap menu
* Let only hooks in hooks.cpp, move definitions somewhere else
* [+] Try to store PlayerSlot instances instantly on init
* [+] Avoid locking main thread on lobby quit
* [+] Clear tasks queue at lobby exit / at exit
* [+] Mutex for player info instances
* [+] Remove left players from cache
* [+] Handle unprocessed players
* [+] Emptify whole map on lobby destroy
* [+] Do not let duplicates in queue
* [+] Clean code so it will be easy to separate safelist / lagabuse logic, move to classes
* [+] Add condition on map name
* [+] Add condition on host name
* [+] Fix lobby destroy hook (calls twice)
* [+] Reduce font height
* [+] Rechedule on request error, limited attempts
*/

__declspec(dllexport) void __stdcall onGameTerminate(void) {
	is_in_lobby.store(false);
	if (player_info_updater != NULL) {
		player_info_updater->stopWorker();
		delete player_info_updater;
		player_info_updater = NULL;
	}

	if (lobby_info != NULL) {
		delete lobby_info;
		lobby_info = NULL;
	}
}

__declspec(dllexport) void __stdcall resetLobbyInfo(void) {
	is_in_lobby.store(false);
	lobby_info->invalidatePlayersInfo();
	lobby_info->invalidateSlots();
}

__declspec(dllexport) void __stdcall onLobbyDestroy(void) {
	resetLobbyInfo();
}

__declspec(dllexport) void __stdcall onGameStart(void) {
	resetLobbyInfo();
}

__declspec(dllexport) void __stdcall onLobbyGameInfo(struct lobbyMapInfo * lobby_map_info) {
	is_in_lobby.store(true);
	default_font = skinGetPathByName("MasterFont", "");
	lobby_info->setHostName(lobby_map_info->creator);
	lobby_info->setMapPath(lobby_map_info->mapPath);
}

__declspec(dllexport) void __stdcall onPostLobbyLeave(char* nickname) {
	//if (is_in_lobby.load()) {
		lobby_info->removePlayerInfo(nickname);
	//}
}

__declspec(dllexport) void __stdcall onLobbyInitStart(void) {
	if (!player_info_updater->isWorkerRunning()) {
		player_info_updater->startWorker();
	}
}

__declspec(dllexport) void __stdcall onAfterSlotInit(struct PlayerSlot* slot) {
	lobby_info->registerSlot(slot);
	if (lobby_info->getMapType() == LobbyInfo::MAP_TYPE_DOTA && lobby_info->getHostType() == LobbyInfo::HOST_TYPE_LAGABUSE) {
		// reducing race textFrame font size, so our extended info fits there
		initPlayerRaceFont(slot, default_font, 0.0098f);
	}
}

__declspec(dllexport) void __stdcall onSlotChange(struct PlayerSlot* slot, char* nickname) {
	std::string str_nickname;
	if (nickname) {
		str_nickname = nickname;
	}
	int slot_number = slot->slotNumber;
	bool is_empty_slot = str_nickname.empty();

	PlayerInfo* player_info = lobby_info->getPlayerInfo(str_nickname);
	if (is_empty_slot) {
		std::string previous_str_nickname = lobby_info->getSlotNickname(slot_number);
		if (!previous_str_nickname.empty()) {
			lobby_info->getPlayerInfo(previous_str_nickname)->unsetSlotNumber();
		}
	} else {
		player_info->setSlotNumber(slot_number);
		if (player_info->getState() == PlayerInfo::STATE_DEFAULT) {
			player_info->setStateAndCompileStrings(PlayerInfo::STATE_LOADING);
			player_info_updater->scheduleUpdate(str_nickname);
		}
	}
	lobby_info->setSlotNickname(slot_number, str_nickname);
}

__declspec(dllexport) int __stdcall isDefaultUpdatingTeamTextDisabled() {
	return lobby_info->getMapType() == LobbyInfo::MAP_TYPE_DOTA && lobby_info->getHostType() == LobbyInfo::HOST_TYPE_LAGABUSE;
}

__declspec(dllexport) void __stdcall afterSlotTextsUpdate(struct PlayerSlot* slot) {
	int slotNumber = slot->slotNumber;
	std::string nickname = lobby_info->getSlotNickname(slotNumber);
	lobby_info->getPlayerInfo(nickname)->applyToPlayerSlot(slot);
}

__declspec(dllexport) void init_hook_handlers() {
	lobby_info = new LobbyInfo();
	player_info_updater = new PlayerInfoUpdater(lobby_info);
}
