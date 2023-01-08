#include "DynamicGameObject.h"
#include "Utilities.h"

DynamicGameObject::DynamicGameObject(const float maxVelocity)
    : m_acceleration{}
      , m_velocity{}
      , MaxVelocity(maxVelocity)
      , m_direction(1)
      , m_hasDrag(false)
{
}

void DynamicGameObject::update(float deltaTime)
{
    // accelerate
    Vector2 newVelocity{};
    newVelocity.x = m_velocity.x + (m_acceleration.x * deltaTime);
    newVelocity.y = m_velocity.y + (m_acceleration.y * deltaTime);

    // drag
    if (m_hasDrag && !isAccelerating() && isMoving())
    {
        newVelocity.x *= 0.80f;
        newVelocity.y *= 0.80f;
    }

    // set velocity if below max
    const float newVelocityLength = getLength(newVelocity.x, newVelocity.y);
    if (newVelocityLength < MaxVelocity)
    {
        m_velocity = newVelocity;
        if (newVelocityLength < 0.01f)
            m_velocity = {};
    }
    else
    {
        Vector2 normalizedVelocity{};
        normalize(m_velocity.x, m_velocity.y, normalizedVelocity.x, normalizedVelocity.y);
        m_velocity.x = normalizedVelocity.x * MaxVelocity;
        m_velocity.y = normalizedVelocity.y * MaxVelocity;
    }

    // direction
    if (m_acceleration.x > 0.f)
        m_direction = 1;
    else if (m_acceleration.x < 0.f)
        m_direction = -1;

    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}

void DynamicGameObject::draw() const
{
    DrawTextureRec(m_texture, {0, 0, (float)m_direction * m_texture.width, (float)m_texture.height}, m_position,
                   m_tint);
}

bool DynamicGameObject::isMoving() const
{
    return getLength(m_velocity.x, m_velocity.y) > 0.f;
}

bool DynamicGameObject::isAccelerating() const
{
    return getLength(m_acceleration.x, m_acceleration.y) > 0.f;
}
