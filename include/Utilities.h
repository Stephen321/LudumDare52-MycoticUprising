#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Constants.h"
#include "Settings.h"


#define DEBUG_VIEW true

// ini files
#define GET_SETTING(SECTION, KEY) GetPrivateProfileIntW(L##SECTION, L##KEY, INVALID, SETTINGS_INI)

extern Config getConfig();
extern Settings& getSettings();

extern float getScreenX(float percentage);
extern float getScreenY(float percentage);

inline float toRadians(float degrees)
{
    return degrees * (M_PI / 180.0);
}

inline float toDegrees(float radians)
{
    return radians * (180.0 / M_PI);
}

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

extern bool isColliding(float x1, float y1, float r1, float x2, float y2, float r2);
