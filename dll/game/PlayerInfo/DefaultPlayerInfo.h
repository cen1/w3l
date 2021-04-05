#pragma once
#include <ctime>
#include <string>
#include "PlayerInfo.h"

class DefaultPlayerInfo : public PlayerInfo {
	private:

	protected:
		DefaultPlayerInfo& operator=(DefaultPlayerInfo const&) = delete; // disable copy-assignment constructor

		virtual void applyJsonData(nlohmann::basic_json<std::map> json) override {

		}

		virtual std::string compileNameString() override {
			return "";
		}

		virtual std::string compileRaceString() override {
			return "";
		}

		virtual std::string compileTeamString() override {
			return "";
		}

		virtual std::string compileHandicapString() override {
			return "";
		}
	public:
		DefaultPlayerInfo(std::string nickname) : PlayerInfo(nickname) {

		};
		//LagabuseDotaPlayerInfo();
		//~LagabuseDotaPlayerInfo();
};
