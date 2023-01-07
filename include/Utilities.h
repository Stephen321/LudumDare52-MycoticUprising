#pragma once

#include "Constants.h"
#include "Settings.h"


// ini files
#define GET_SETTING(SECTION, KEY) GetPrivateProfileIntW(L##SECTION, L##KEY, INVALID, SETTINGS_INI)

extern Config getConfig();
extern Settings& getSettings();


extern size_t getScreenX(float percentage);
extern size_t getScreenY(float percentage);
