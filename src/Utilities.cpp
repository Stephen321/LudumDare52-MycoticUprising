#include "Utilities.h"

#include "Game.h"
#include "Windows.h"

Config getConfig()
{
    Config config;
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
    return (float)getSettings().config.screenWidth * percentage;
}

extern float getScreenY(float percentage)
{
    return (float)getSettings().config.screenHeight * percentage;
}

bool isColliding(float x1, float y1, float r1, float x2, float y2, float r2)
{
    const float distance = getLength(x2 - x1, y2 - y1);
    return distance < (r1 + r2);
}
