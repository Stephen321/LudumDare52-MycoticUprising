#include "Utilities.h"

#include "Game.h"
#include "Windows.h"

Config Utilities::getConfig()
{
    Config config;
    config.screenWidth = GET_SETTING("Screen", "Width");
    config.screenHeight = GET_SETTING("Screen", "Height");
    return config;
}

Settings& Utilities::getSettings()
{
    return Game::get().getSettings();
}

float Utilities::getScreenX(float percentage)
{
    return (float)getSettings().config.screenWidth * percentage;
}

float Utilities::getScreenY(float percentage)
{
    return (float)getSettings().config.screenHeight * percentage;
}

bool Utilities::isColliding(float x1, float y1, float r1, float x2, float y2, float r2)
{
    const float distance = Utilities::getLength(x2 - x1, y2 - y1);
    return distance < (r1 + r2);
}

float Utilities::getLength(float x, float y)
{
    return sqrt(x * x + y * y);
}

void Utilities::normalize(float x, float y, float& outX, float& outY)
{
    float length = getLength(x, y);
    outX = x / length;
    outY = y / length;
}
