#include "TextureManager.h"

#include "Constants.h"

TextureManager& TextureManager::get()
{
    static TextureManager textureManager;
    return textureManager;
}

Texture2D TextureManager::loadTexture(const std::string& textureName)
{
    if (m_textures.find(textureName) == m_textures.end())
    {
        std::string path = std::string(TEXTURES_DIR);
        path += textureName;
        path += ".png";
        std::pair<Texture2D, size_t> value;
        value.first = LoadTexture(path.c_str());
        value.second = 0;
        m_textures.try_emplace(textureName, value);
    }
    m_textures.at(textureName).second++;
    return m_textures.at(textureName).first;
}

void TextureManager::closeTexture(const Texture& texture)
{
    // TODO: hack to stop all texture unloaded as it will affect other particles...
        return;

    bool remove = false;
    std::string textureName;

    for (auto& entry : m_textures)
    {
        if (entry.second.first.id == texture.id)
        {
            entry.second.second--;
            if (entry.second.second == 0)
            {
                remove = true;
                textureName = entry.first;
                break;
            }
        }
    }
    if (remove)
    {
        UnloadTexture(texture);
        m_textures.erase(textureName);
    }
}
