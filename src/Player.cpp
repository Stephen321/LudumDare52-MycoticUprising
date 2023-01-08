#include "Player.h"

Player::Player()
    : DynamicGameObject(100.f)
{
}

void Player::init(const std::string& textureName, size_t drawLayer)
{
    m_hasDrag = true;
    DynamicGameObject::init("Player", 1);
}

void Player::checkInput()
{
    // TODO: why the 1000.f scale
    const float AccelerationScale = 1000.f;

    // TODO: holding 2 keys then letting go of one keeps in same direction
    if (IsKeyPressed(KEY_W))
    {
        m_velocity.x *= 0.7f;
        m_acceleration.x *= 0.0f;
        m_acceleration.y = -AccelerationScale;
    }
    else if (IsKeyPressed(KEY_S))
    {
        m_velocity.x *= 0.7f;
        m_acceleration.x *= 0.0f;
        m_acceleration.y = AccelerationScale;
    }
    if (IsKeyPressed(KEY_A))
    {
        m_velocity.y *= 0.7f;
        m_acceleration.y *= 0.0f;
        m_acceleration.x = -AccelerationScale;
    }
    else if (IsKeyPressed(KEY_D))
    {
        m_velocity.y *= 0.7f;
        m_acceleration.y *= 0.0f;
        m_acceleration.x = AccelerationScale;
    }

    if (IsKeyReleased(KEY_W))
    {
        m_acceleration.y = 0.f;
    }
    else if (IsKeyReleased(KEY_S))
    {
        m_acceleration.y = 0.f;
    }
    if (IsKeyReleased(KEY_A))
    {
        m_acceleration.x = 0.f;
    }
    else if (IsKeyReleased(KEY_D))
    {
        m_acceleration.x = 0.f;
    }
}

void Player::update(float deltaTime)
{
    DynamicGameObject::update(deltaTime);
}
