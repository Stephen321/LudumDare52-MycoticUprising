#include "Character.h"
#include "Utilities.h"

Character::Character(const float maxVelocity)
    : m_acceleration{}
      , m_velocity{}
      , MaxVelocity(maxVelocity)
{
}

void Character::update(float deltaTime)
{
    Vector2 newVelocity{};
    newVelocity.x = m_velocity.x + (m_acceleration.x * 1000.f) * deltaTime;
    newVelocity.y = m_velocity.y + (m_acceleration.y * 1000.f) * deltaTime;
    if (!isAccelerating() && isMoving())
    {
        // drag
        newVelocity.x *= 0.60f;
        newVelocity.y *= 0.60f;
    }

    const float newVelocityLength = getLength(newVelocity.x, newVelocity.y);
    if (newVelocityLength < MaxVelocity)
    {
        m_velocity = newVelocity;
        if (newVelocityLength < 0.25f)
            m_velocity = {};
    }

    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}

bool Character::isMoving() const
{
    return getLength(m_velocity.x, m_velocity.y) > 0.f;
}

bool Character::isAccelerating() const
{
    return getLength(m_acceleration.x, m_acceleration.y) > 0.f;
}
