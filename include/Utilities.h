#pragma once

#include <cmath>

#include "Constants.h"
#include "Settings.h"


#define DEBUG_VIEW true

// ini files
#define GET_SETTING(SECTION, KEY) GetPrivateProfileIntW(L##SECTION, L##KEY, INVALID, SETTINGS_INI)

extern Config getConfig();
extern Settings& getSettings();


extern float getScreenX(float percentage);
extern float getScreenY(float percentage);

inline float getLength(float x, float y)
{
    return sqrt(x * x + y * y);
}

inline void normalize(float x, float y, float& outX, float& outY)
{
    float length = getLength(x, y);
    outX = x / length;
    outY = y / length;
}
