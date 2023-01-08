#pragma once
#include <map>
#include <raylib.h>
#include <string>


class TextureManager
{
public:
    static TextureManager& get();

    Texture2D loadTexture(const std::string& textureName);
    void closeTexture(const Texture& texture);

private:
    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

   std::map<std::string, std::pair<Texture2D, size_t>> m_textures;
};
