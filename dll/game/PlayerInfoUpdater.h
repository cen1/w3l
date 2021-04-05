#pragma once

#include <atomic>
#include <mutex>
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include "LobbyInfo.h"
#include "PlayerInfo/PlayerInfo.h"

using json = nlohmann::json;

class PlayerInfoUpdater {

	private:
		const int SCHEDULE_ATTEMPTS_LIMIT = 3;
		LobbyInfo * lobbyInfo;
		std::thread * worker = NULL;
		mutable std::mutex startWorkerMutex;
		mutable std::mutex stopWorkerMutex;
		std::vector<std::string> scheduledNicknames;
		mutable std::mutex scheduleMutex;
		std::map<std::string, int> nicknameFailures;
		mutable std::mutex workerIterationMutex;
		std::atomic<bool> stopWorkerFlag{ false };

	public:
		const int WORKER_SLEEP_TIME = 150;
		
		PlayerInfoUpdater& operator=(PlayerInfoUpdater const&) = delete; // disable copy-assignment constructor

		PlayerInfoUpdater(LobbyInfo * lobby_info) {
			this->lobbyInfo = lobby_info;
		}

		~PlayerInfoUpdater() {
			this->stopWorker();
		}

		void startWorker() {
			std::lock_guard<std::mutex>  guard{ startWorkerMutex };
			this->stopWorker();
			this->worker = new std::thread(&PlayerInfoUpdater::workerFunction, this);
		}

		bool isWorkerRunning() {
			return this->worker != NULL && this->worker->joinable();
		}

		void stopWorker() {
			std::lock_guard<std::mutex>  guard{ stopWorkerMutex };
			if (this->worker != NULL) {
				if (this->worker->joinable()) {
					this->stopWorkerFlag.store(true);
					this->worker->join();
				}
				delete this->worker;
				this->worker = NULL;
			}
			this->stopWorkerFlag.store(false);
		}

		void workerFunction() {
			while (!this->stopWorkerFlag.load()) {
				std::lock_guard<std::mutex> guard(this->workerIterationMutex);
				if (!this->scheduledNicknames.empty()) { // we do not care about data race here, probably
					std::vector<std::string> nicknames;
					{
						std::lock_guard<std::mutex> task_guard{ scheduleMutex };
						nicknames = this->scheduledNicknames;
						this->scheduledNicknames.clear(); 
					}
					this->fetchPlayersInfo(nicknames);
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(PlayerInfoUpdater::WORKER_SLEEP_TIME));
			}
		}

		void fetchPlayersInfo(std::vector<std::string> nicknames) {
			if (nicknames.empty()) {
				return;
			}

			json player_info_mapped;
			bool should_reschedule = false;
			if (this->lobbyInfo->getMapType() == LobbyInfo::MAP_TYPE_DOTA) {
				if (this->lobbyInfo->getHostType() == LobbyInfo::HOST_TYPE_LAGABUSE) {
					std::string querystring = "/new/api/la/stats?";
					for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it) {
						// @todo urlencode
						querystring += "players[]=" + *it + "&";
					}

					httplib::SSLClient cli("eurobattle.net");
					cli.set_follow_location(true);
					auto res = cli.Get(querystring.c_str());
					if (res) {
						auto player_info_list = json::parse(res->body);
						for (json::iterator it = player_info_list.begin(); it != player_info_list.end(); ++it) {
							std::string nickname = (*it)["name"];
							player_info_mapped[nickname] = *it;
						}
					} else {
						should_reschedule = true;
					}
					
				} else if (this->lobbyInfo->getHostType() == LobbyInfo::HOST_TYPE_SAFELIST) {
					// @todo safelist
				}
			}

			if (should_reschedule) {
				for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end();) {
					std::string nickname = (*it);
					if (this->nicknameFailures.count(nickname) == 0) {
						this->nicknameFailures.insert({ nickname, 0 });
					}
					int failures_count = ++this->nicknameFailures[nickname];
					if (failures_count < PlayerInfoUpdater::SCHEDULE_ATTEMPTS_LIMIT) {
						this->scheduleUpdate(nickname);
						it = nicknames.erase(it);
					} else {
						it++;
					}
				}
			}

			for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it) {
				std::string nickname = (*it);
				std::string nickname_lowercased = strtolower(nickname);
				PlayerInfo * player_info = this->lobbyInfo->getPlayerInfo(nickname);
				if (player_info_mapped.contains(nickname_lowercased)) {
					player_info->updateFromJson(player_info_mapped[nickname_lowercased]);
				}
				player_info->setStateAndCompileStrings(PlayerInfo::STATE_LOADED);
				int slot_number = player_info->getSlotNumber();
				if (slot_number != -1) {
					struct PlayerSlot * player_slot = lobbyInfo->getPlayerSlot(slot_number);
					if (player_slot != NULL) {
						player_info->applyToPlayerSlot(player_slot);
					}
				}
			}
		}

		void scheduleUpdate(std::string nickname) {
			std::lock_guard<std::mutex> guard{ scheduleMutex };
			if (std::find(this->scheduledNicknames.begin(), this->scheduledNicknames.end(), nickname) == this->scheduledNicknames.end()) {
				this->scheduledNicknames.push_back(nickname);
			}
		}
};
