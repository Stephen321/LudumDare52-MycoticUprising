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

extern float getScreenX(float percentage)
{
    return getSettings().config.screenWidth * percentage;
}

extern float getScreenY(float percentage)
{
    return getSettings().config.screenHeight * percentage;
}
