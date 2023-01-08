#include "Enemy.h"

#include "Game.h"
#include "ProjectileManager.h"

Enemy::Enemy(const float maxVelocity)
    : DynamicGameObject(maxVelocity)
      , m_harvested(false)
    , m_health(100.f)
{
}

bool Enemy::harvest(float amount)
{
    if (m_harvested)
        return false;
    
    m_health -= amount;
    if (m_health < 0.f)
    {
        m_health = 0.f;
        m_harvested = true;
        harvested();
        return true;
    }
    return false;
}

LevelState Enemy::getLevelState() const
{
    return Game::get().getLevelState();
}

void Enemy::fire(const ProjectileProperties& properties)
{
    ProjectileManager::get().addProjectile(properties);
}
