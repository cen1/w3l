#pragma once

#include <string>
#include <vector>

class Config {
public:
    static bool lobbyOverlayEnabled;
    static std::string lobbyOverlayApiHost;
    static std::string lobbyOverlayApiPath;
    static std::vector<std::string> lobbyOverlayBotNames;
};