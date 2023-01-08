#include "GameObject.h"

#include "TextureManager.h"

#include "Constants.h"


GameObject::GameObject()
    : m_position{}
      , m_origin{}
      , m_scale(1.f)
      , m_rotation(0.f)
      , m_tint(WHITE)
      , m_horizontalFlip(false)
      , m_drawLayer(0)
      , m_alive(true)
{
}

void GameObject::init(const std::string& textureName, size_t drawLayer)
{
    m_texture = TextureManager::get().loadTexture(textureName);

    m_origin.x = m_texture.width * 0.5f;
    m_origin.y = m_texture.height * 0.5f;
}

void GameObject::draw() const
{
    Rectangle source;
    source.x = 0.f;
    source.y = 0.f;
    source.width = (m_horizontalFlip ? -1.f : 1.f) * (float)m_texture.width;
    source.height = (float)m_texture.height;

    Rectangle destination;
    destination.x = m_position.x;
    destination.y = m_position.y;
    destination.width = (float)m_texture.width;
    destination.height = (float)m_texture.height;

    DrawTexturePro(m_texture, source, destination, m_origin, m_rotation, m_tint);

#ifdef GAME_DEBUG
    if (getWidth() < 400.f)
        DrawCircleLines(m_position.x, m_position.y, getWidth(), RED);
#endif
}

void GameObject::close()
{
    TextureManager::get().closeTexture(m_texture);
}

void GameObject::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void GameObject::setOrigin(float x, float y)
{
    m_origin.x = x;
    m_origin.y = y;
}

bool GameObject::isVisible() const
{
    const float Offset = 100.f;
    return (m_position.x > -Offset ||
        m_position.y > -Offset ||
        m_position.x < (float)GetScreenWidth() + Offset ||
        m_position.y < (float)GetScreenHeight() + Offset);
}
