#include "Utilities.h"

#include "Game.h"
#include "Windows.h"

Config getConfig()
{
    Config config{};
    config.screenWidth = GET_SETTING("Screen", "Width");
    config.screenHeight = GET_SETTING("Screen", "Height");
    return config;
}


Settings& getSettings()
{
    return Game::get().getSettings();
}

extern size_t getScreenX(float percentage)
{
    return (size_t)(getSettings().config.screenWidth * percentage);
}

extern size_t getScreenY(float percentage)
{
    return (size_t)(getSettings().config.screenHeight * percentage);
}
