#include "GameObject.h"
#include "Utilities.h"


GameObject::GameObject()
    : m_drawLayer(0)
      , m_alive(true)
      , m_position{0, 0}
      , m_rotation(0.f)
      , m_scale(1.f)
      , m_tint(WHITE)
{
}

void GameObject::init(const std::string& textureName, size_t drawLayer)
{
    std::string path = std::string(TEXTURES_DIR);
    path += textureName;
    path += ".png";
    m_texture = LoadTexture(path.c_str());
}

void GameObject::draw() const
{
    DrawTextureEx(m_texture, m_position, m_rotation, m_scale, m_tint);
}

void GameObject::close()
{
    UnloadTexture(m_texture);
}

void GameObject::setPosition(float x, float y)
{
    if (x != INVALID)
        m_position.x = x;
    
    if (y != INVALID)
        m_position.y = y;
}
