#include "SoundUtilities.h"

#include "Constants.h"

Sound loadSound(const std::string& soundName)
{
    std::string path = std::string(SOUND_DIR);
    path += soundName;
    path += ".wav";
    return LoadSound(path.c_str());
}
