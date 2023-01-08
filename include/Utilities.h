#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Constants.h"
#include "Settings.h"


#define DEBUG_VIEW true

// ini files
#define GET_SETTING(SECTION, KEY) GetPrivateProfileIntW(L##SECTION, L##KEY, INVALID, SETTINGS_INI)

class Utilities
{
public:
    static Config getConfig();
    static Settings& getSettings();

    static float getScreenX(float percentage);
    static float getScreenY(float percentage);

    static float toRadians(float degrees)
    {
        return degrees * (M_PI / 180.0);
    }

    static float toDegrees(float radians)
    {
        return radians * (180.0 / M_PI);
    }

    static float getLength(float x, float y);

    static void normalize(float x, float y, float& outX, float& outY);

    static bool isColliding(float x1, float y1, float r1, float x2, float y2, float r2);
};
