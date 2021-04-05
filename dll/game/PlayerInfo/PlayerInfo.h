#pragma once
#include <atomic>
#include <map>
#include <ctime>
#include <string>
#include <nlohmann/json.hpp>

// @fixme it is supposed to be an abstract class, but i did not manage to do it correctly
class PlayerInfo {

	private:
		std::atomic<int> slotNumber{ -1 };
		std::atomic<int> state{ PlayerInfo::STATE_DEFAULT };
		std::string nickname;

		std::string compiledName;
		std::string compiledRace;
		std::string compiledTeam;
		std::string compiledHandicap;
		mutable std::mutex compile_mutex;
		mutable std::mutex update_mutex;

	protected:
		virtual void applyJsonData(nlohmann::basic_json<std::map> json) {

		}

		virtual std::string compileNameString() {
			return "";
		}

		virtual std::string compileRaceString() {
			return "";
		}

		virtual std::string compileTeamString() {
			return "";
		}

		virtual std::string compileHandicapString() {
			return "";
		}

	public:
		static const int STATE_DEFAULT = 0;
		static const int STATE_LOADING = 1;
		static const int STATE_LOADED = 2;
		static const int STATE_EMPTY = 3; // @todo

		PlayerInfo& operator=(PlayerInfo const&) = delete; // disable copy-assignment constructor

		PlayerInfo(std::string nickname) {
			this->nickname = nickname;
		}

		virtual ~PlayerInfo() {

		}

		std::string getNickname() {
			return this->nickname;
		}

		void updateFromJson(nlohmann::basic_json<std::map> json) {
			std::lock_guard<std::mutex> l(update_mutex);
			this->applyJsonData(json);
		};

		void updateCompiledStrings() {
			std::lock_guard<std::mutex> l(compile_mutex);
			this->compiledName = this->compileNameString();
			this->compiledRace = this->compileRaceString();
			this->compiledTeam = this->compileTeamString();
			this->compiledHandicap = this->compileHandicapString();
		}

		int getState() {
			return this->state.load();
		}

		void setState(int state) {
			this->state.store(state); // @todo exception on wrong state
		}

		void setStateAndCompileStrings(int state) {
			// wtf architecture
			this->setState(state);
			updateCompiledStrings();
		}

		void setSlotNumber(int slotNumber) {
			this->slotNumber.store(slotNumber);
		}

		int getSlotNumber() {
			return this->slotNumber.load();
		}

		void unsetSlotNumber() {
			this->setSlotNumber(-1);
		}

		void applyToPlayerSlot(PlayerSlot * slot) {
			if (slot == NULL) {
				return;
			}
			// @todo refactor
			std::lock_guard<std::mutex> l(compile_mutex);
			std::string compiledString;
			compiledString = this->compiledName;
			if (!compiledString.empty()) {
				setPlayerNameText(slot, compiledString.c_str());
			}

			compiledString = this->compiledRace;
			if (!compiledString.empty()) {
				setPlayerRaceText(slot, compiledString.c_str());
			}

			compiledString = this->compiledTeam;
			if (!compiledString.empty()) {
				setPlayerTeamText(slot, compiledString.c_str());
			}

			compiledString = this->compiledHandicap;
			if (!compiledString.empty()) {
				setHandicapText(slot, compiledString.c_str());
			}
		}
};
