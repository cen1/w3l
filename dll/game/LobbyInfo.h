#pragma once
#include <atomic>
#include <mutex>
#include <string>
#include <map>
#include "PlayerInfo/PlayerInfo.h"
#include "PlayerInfo/DefaultPlayerInfo.h"
#include "PlayerInfo/LagabuseDotaPlayerInfo.h"
#include "globals.h"
#include "../debug.h"

std::string strtolower(std::string str) {
	std::string result;
	for (auto elem : str) {
		result += std::tolower(elem);
	}
	return result;
}

class LobbyInfo {
	private:
		std::string hostName;
		std::string mapPath;
		std::string slotNicknames[MAX_SLOT_NUMBERS];
		struct PlayerSlot* playerSlots[MAX_SLOT_NUMBERS];
		std::map<std::string, PlayerInfo*> nicknameInfoMap;
		mutable std::mutex player_slot_mutex;
		mutable std::mutex player_info_mutex;

		int mapType;
		int hostType;
	protected:

		virtual PlayerInfo * createPlayerInfo(std::string nickname) {
			// @fixme it uses evil 'new' keyword, need to somehow make it obvious
			if (this->getMapType() == LobbyInfo::MAP_TYPE_DOTA) {
				if (this->getHostType() == LobbyInfo::HOST_TYPE_LAGABUSE) {
					return new LagabuseDotaPlayerInfo(nickname);
				//} else if (this->hostType == LobbyInfo::HOST_TYPE_SAFELIST) {
				// @todo safelist support
				//	return new SafelistDotaPlayerInfo(nickname);
				}
			}
			return new DefaultPlayerInfo(nickname);
		}

		int detectMapTypeByPath(std::string map_name) {
			if (map_name.find("DotA_Allstars") != std::string::npos) {
				// @todo remove true
				return LobbyInfo::MAP_TYPE_DOTA;
			}
			return LobbyInfo::MAP_TYPE_UNKNOWN;
		}

		int detectHostTypeByName(std::string host_name) {
			if (host_name.find("lagabuse.com.") != std::string::npos) {
				// @todo remove true
				return LobbyInfo::HOST_TYPE_LAGABUSE;
			}
			//if (host_name.find("some_safelist_creator_name") != std::string::npos) {
			// @todo safelist support
			// return LobbyInfo::HOST_TYPE_SAFELIST;
			//}
			return LobbyInfo::HOST_TYPE_UNKNOWN;
		}

	public:
		static const int MAP_TYPE_UNKNOWN = 0;
		static const int MAP_TYPE_DOTA = 0;

		static const int HOST_TYPE_UNKNOWN = 0;
		static const int HOST_TYPE_LAGABUSE = 1;
		static const int HOST_TYPE_SAFELIST = 2;

		LobbyInfo& operator=(LobbyInfo const&) = delete; // disable copy-assignment constructor

		~LobbyInfo() {
			this->invalidatePlayersInfo();
			this->invalidateSlots();
		}

		void setHostName(std::string host_name) {
			this->hostName = host_name;
			this->hostType = this->detectHostTypeByName(host_name);
			debug((char*)("Host name: " + this->hostName + " " + std::to_string(this->hostType) + "\n").c_str());
		}

		std::string getHostName() {
			// @todo immutability
			return this->hostName;
		}

		void setMapPath(std::string map_path) {
			this->mapPath = map_path;
			this->mapType = this->detectMapTypeByPath(map_path);
			debug((char*) ("Map path: " + this->mapPath + " " + std::to_string(this->mapType) + "\n").c_str());
		}

		std::string getMapPath() {
			// @todo immutability
			return this->mapPath;
		}

		int getHostType() {
			return this->hostType;
		}

		int getMapType() {
			return this->mapType;
		}

		void registerSlot(struct PlayerSlot* slot) {
			std::lock_guard<std::mutex> l(player_slot_mutex);
			int slot_number = slot->slotNumber;
			if (playerSlots[slot_number] == slot) {
				return;
			}
			this->playerSlots[slot_number] = slot;
		}

		void invalidatePlayersInfo() {
			std::lock_guard<std::mutex> l(player_info_mutex);
			for (auto it = nicknameInfoMap.begin(); it != nicknameInfoMap.end();) {
				delete it->second;
				it = nicknameInfoMap.erase(it);
			}
		}

		void invalidateSlots() {
			std::lock_guard<std::mutex> l(player_slot_mutex);
			for (int i = 0; i < MAX_SLOT_NUMBERS; i++) {
				this->playerSlots[i] = NULL;
			}
		}

		struct PlayerSlot* getPlayerSlot(int slot_number) {
			std::lock_guard<std::mutex> l(player_slot_mutex);
			return this->playerSlots[slot_number];
		}

		std::string getSlotNickname(int slot_number) {
			// @todo invalid argument exception
			std::lock_guard<std::mutex> l(player_slot_mutex);
			return this->slotNicknames[slot_number];
		}

		void setSlotNickname(int slot_number, std::string nickname) {
			std::lock_guard<std::mutex> l(player_slot_mutex);
			this->slotNicknames[slot_number] = nickname;
		}

		PlayerInfo * getPlayerInfo(std::string nickname) {
			// @todo refactor, should be only getter :'-(
			std::lock_guard<std::mutex> l(player_info_mutex);
			std::string nickname_lowercased = strtolower(nickname);
			if (nicknameInfoMap.count(nickname_lowercased) == 0) {
				PlayerInfo * player_info = this->createPlayerInfo(nickname);
				if (nickname.empty()) {
					player_info->setStateAndCompileStrings(PlayerInfo::STATE_EMPTY);
				}
				nicknameInfoMap.insert({ nickname_lowercased, player_info });
			}
			return nicknameInfoMap.at(nickname_lowercased);
		}

		void removePlayerInfo(std::string nickname) {
			std::lock_guard<std::mutex> l(player_info_mutex);
			std::string nickname_lowercased = strtolower(nickname);
			if (this->nicknameInfoMap.count(nickname_lowercased) == 1) {
				delete this->nicknameInfoMap.at(nickname_lowercased);
				this->nicknameInfoMap.erase(nickname_lowercased);
			}
		}
};
