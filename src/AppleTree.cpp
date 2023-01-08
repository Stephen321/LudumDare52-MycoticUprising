#include "AppleTree.h"

#include "ApplePickup.h"
#include "Game.h"
#include "LevelDifficultyManager.h"
#include "StaticGameObject.h"
#include "TextureManager.h"
#include "Utilities.h"

AppleTree::AppleTree()
    : Enemy(50.f)
      , m_fireTimer(0.f)
{
}

void AppleTree::update(float deltaTime)
{
    if (m_harvested)
        return;

    LevelState levelState = getLevelState();

    // TODO: AI steering behaviour system in here
    // get direction to player
    float xDir = levelState.playerPositionX - m_position.x;
    float yDir = levelState.playerPositionY - m_position.y;
    float length = Utilities::getLength(xDir, yDir);
    if (length > 0.f)
    {
        xDir /= length;
        yDir /= length;
    }
    if (length < 55.f)
    {
        m_velocity = {};
    }
    else
    {
        m_velocity.x = m_maxVelocity * xDir;
        m_velocity.y = m_maxVelocity * yDir;
    }
    // move
    Enemy::update(deltaTime);


    m_fireTimer += deltaTime;
    // TODO: the level difficulty...
    if (m_fireTimer > (0.45f / LevelDifficultyManager::get().getFireRateScale()) && length > 30.f)
    {
        m_fireTimer = 0.f;

        ProjectileProperties properties;
        // TODO: debug display radius that projectiles are chosen on
        properties.startX = m_position.x + (xDir * 20.f);
        properties.startY = m_position.y + (yDir * 20.f);
        properties.targetX = levelState.playerPositionX;
        properties.targetY = levelState.playerPositionY;
        properties.textureName = "apple";
        properties.rotation = 0.f;
        properties.maxVelocity = 105.f;
        properties.type = ProjectileProperties::Type::Point;

        fire(properties);
    }
}

// TODO: where to put this properly..?
void AppleTree::harvested()
{
    TextureManager::get().closeTexture(m_texture);
    m_texture = TextureManager::get().loadTexture("appleTreeHarvested");

    if (rand() % 5 != 0)
        return;

    Game::get().getGameObjectsRef().push_back(new ApplePickup);
    Game::get().getGameObjectsRef().back()->init();

    Vector2 direction;
    float rotation = 360.f * (float)rand() / (float)RAND_MAX;

    direction.x = cosf(Utilities::toRadians(rotation));
    direction.y = sinf(Utilities::toRadians(rotation));


    Vector2 position = m_position;
    position.x += direction.x * 50.f;
    position.y += direction.y * 50.f;
    Game::get().getGameObjectsRef().back()->setPosition(position.x, position.y);
}
