#include "DynamicGameObject.h"
#include "Utilities.h"

DynamicGameObject::DynamicGameObject(const float maxVelocity)
    : m_acceleration{}
      , m_velocity{}
      , m_maxVelocity(maxVelocity)
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
    if (newVelocityLength < m_maxVelocity)
    {
        m_velocity = newVelocity;
        if (newVelocityLength < 0.01f)
            m_velocity = {};
    }
    else
    {
        Vector2 normalizedVelocity{};
        normalize(newVelocity.x, newVelocity.y, normalizedVelocity.x, normalizedVelocity.y);
        m_velocity.x = normalizedVelocity.x * m_maxVelocity;
        m_velocity.y = normalizedVelocity.y * m_maxVelocity;
    }

    // direction
    if (m_acceleration.x > 0.f)
        m_horizontalFlip = false;
    else if (m_acceleration.x < 0.f)
        m_horizontalFlip = true;

    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}

bool DynamicGameObject::isMoving() const
{
    return getLength(m_velocity.x, m_velocity.y) > 0.f;
}

bool DynamicGameObject::isAccelerating() const
{
    return getLength(m_acceleration.x, m_acceleration.y) > 0.f;
}
