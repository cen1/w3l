#pragma once
#include <ctime>
#include <string>
#include "PlayerInfo.h"

class LagabuseDotaPlayerInfo : public PlayerInfo {
	private:
		unsigned long rating = 0;
		unsigned long gamesCount = 0;
		unsigned long wins = 0;
		unsigned long loses = 0;
		unsigned long rank = 0;
	protected:
		LagabuseDotaPlayerInfo& operator=(LagabuseDotaPlayerInfo const&) = delete; // disable copy-assignment constructor

		virtual void applyJsonData(nlohmann::basic_json<std::map> json) override {
			this->rating = json["rating"];
			this->wins = json["wins"];
			this->loses = json["loses"];
			this->gamesCount = this->wins + this->loses;
			this->rank = json["rank"];
		}

		virtual std::string compileNameString() override {
			return "";
		}

		virtual std::string compileRaceString() override {
			int state = this->getState();
			if (state == PlayerInfo::STATE_LOADING) {
				return "|c00FFFF00Loading...|r";
			}
			if (state == PlayerInfo::STATE_LOADED) {
				if (this->rating == 0) {
					return "|c006969FFn/a|r";
				}
				return "|c00FFFF00" + std::to_string(this->rating) + "|r|c006969FFpsr|r (|c009AFF35" + std::to_string(this->wins) + "|r - |c00FF0F4F" + std::to_string(this->loses) + "|r)";
			}
			if (state == PlayerInfo::STATE_EMPTY) {
				return " ";
			}
			return "";
		}

		virtual std::string compileTeamString() override {
			int state = this->getState();
			if (state == PlayerInfo::STATE_LOADING) {
				return "|c00FFFF00...|r";
			}
			if (state == PlayerInfo::STATE_LOADED) {
				if (this->rating == 0 || this->gamesCount == 0) {
					return "|c006969FFn/a|r";
				}
				std::string color;
				int winrate = (int)round(100 * this->wins / this->gamesCount);
				// @todo color helper
				// @todo better colors and gradations; here i just test stuff
				if (winrate <= 40) {
					color = "FF0000";
				} else if (winrate <= 60) {
					color = "FF7F00";
				} else {
					color = "96FF96";
				}
				return "|c006969FFWin:|r |c00" + color + std::to_string(winrate) + "%|r";
			}
			if (state == PlayerInfo::STATE_EMPTY) {
				return " ";
			}
			return "";
		}

		virtual std::string compileHandicapString() override {
			int state = this->getState();
			if (state == PlayerInfo::STATE_LOADING) {
				return "|c00FFFF00...|r";
			}
			if (state == PlayerInfo::STATE_LOADED) {
				if (this->rating == 0) {
					return "|c006969FFn/a|r";
				} else if (this->rank > 0 && this->rank <= 5000) {
					return "|c006969FF#" + std::to_string(this->rank) + "|r";	
				}
				return "|c006969FFUnranked|r"; // @todo gray color here
			}
			if (state == PlayerInfo::STATE_EMPTY) {
				return " ";
			}
			return "";
		}
	public:
		LagabuseDotaPlayerInfo(std::string nickname) : PlayerInfo(nickname) {

		};
		//~LagabuseDotaPlayerInfo();
};
