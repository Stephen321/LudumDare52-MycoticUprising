#include "TextureManager.h"

#include "Constants.h"

TextureManager& TextureManager::get()
{
    static TextureManager textureManager;
    return textureManager;
}

Texture2D TextureManager::loadTexture(const std::string& textureName)
{
    if (m_textures.find(textureName) != m_textures.end())
    {
        return m_textures.at(textureName);
    }
    std::string path = std::string(TEXTURES_DIR);
    path += textureName;
    path += ".png";
    return m_textures.try_emplace(textureName, LoadTexture(path.c_str())).first->second;
}
