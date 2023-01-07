#include "Player.h"

Player::Player()
    : Character(100.f)
{
}

void Player::init(const std::string& textureName, size_t drawLayer)
{
    Character::init("Player", 0);
}

void Player::checkInput()
{
    // TODO: holding 2 keys then letting go of one keeps in same direction
    if (IsKeyPressed(KEY_W))
    {
        m_velocity.x = 0.f;
        m_acceleration.x *= 0.0f;
        m_acceleration.y = -1.f;
    }
    else if (IsKeyPressed(KEY_S))
    {
        m_velocity.x = 0.f;
        m_acceleration.x *= 0.0f;
        m_acceleration.y = 1.f;
    }
    if (IsKeyPressed(KEY_A))
    {
        m_velocity.y = 0.f;
        m_acceleration.y *= 0.0f;
        m_acceleration.x = -1.f;
    }
    else if (IsKeyPressed(KEY_D))
    {
        m_velocity.y = 0.f;
        m_acceleration.y *= 0.0f;
        m_acceleration.x = 1.f;
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
    Character::update(deltaTime);
}
