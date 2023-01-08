#include "Enemy.h"

#include "Game.h"
#include "ProjectileManager.h"

Enemy::Enemy(const float maxVelocity)
    : DynamicGameObject(maxVelocity)
      , m_infected(true)
{
}

LevelState Enemy::getLevelState() const
{
    return Game::get().getLevelState();
}

void Enemy::fire(const ProjectileProperties& properties)
{
    ProjectileManager::get().addProjectile(properties);
}
