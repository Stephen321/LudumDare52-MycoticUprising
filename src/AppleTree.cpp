#include "AppleTree.h"

#include "Utilities.h"

AppleTree::AppleTree()
    : Enemy(40.f)
      , m_fireTimer(0.f)
{
}

void AppleTree::update(float deltaTime)
{
    LevelState levelState = getLevelState();

    // TODO: AI steering behaviour system in here
    // get direction to player
    float xDir = levelState.playerPositionX - m_position.x;
    float yDir = levelState.playerPositionY - m_position.y;
    float length = getLength(xDir, yDir);

    m_velocity.x = MaxVelocity * (xDir / length);
    m_velocity.y = MaxVelocity * (yDir / length);

    // move
    Enemy::update(deltaTime);


    m_fireTimer += deltaTime;
    if (m_fireTimer > 0.5f)
    {
        m_fireTimer = 0.f;
        ProjectileProperties properties;
        properties.type = ProjectileProperties::Type::Point;

        // TODO: debug display radius that projectiles are chosen on
        properties.startX = m_position.x + (m_direction * 20.f);
        properties.startY = m_position.y;
        properties.targetX = levelState.playerPositionX;
        properties.targetY = levelState.playerPositionY;
        properties.textureName = "apple";
        properties.rotation = 0.f;
        properties.maxVelocity = 80.f;

        fire(properties);
    }
}
