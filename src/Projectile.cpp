#include "Projectile.h"

#include <vector>

#include "Game.h"
#include "Player.h"
#include "Utilities.h"

// TODO: remove this collision code and do better

namespace
{
    void destroyCollidingParticles(float x, float y, float r)
    {
        std::vector<GameObject*> collidingProjectiles;

        for (GameObject* gameObject : Game::get().getGameObjectsRef())
        {
            PointProjectile* projectile = dynamic_cast<PointProjectile*>(gameObject);
            if (projectile)
            {
                if (isColliding(x, y, r,
                                projectile->getPosition().x,
                                projectile->getPosition().y,
                                projectile->getWidth()))
                {
                    projectile->markAsDead();
                }
            }
        }
    }
}

void Projectile::update(float deltaTime)
{
    DynamicGameObject::update(deltaTime);
    if (!isVisible())
    {
        markAsDead();
    }
}

Projectile::Projectile(const ProjectileProperties& properties)
    : DynamicGameObject(properties.maxVelocity)
      , m_properties(properties)
{
    m_position.x = properties.startX;
    m_position.y = properties.startY;
    m_rotation = properties.rotation;
}

PointProjectile::PointProjectile(const ProjectileProperties& properties)
    : Projectile(properties)
{
    float xDir = m_properties.targetX - m_position.x;
    float yDir = m_properties.targetY - m_position.y;
    float length = getLength(xDir, yDir);
    m_velocity.x = MaxVelocity * (xDir / length);
    m_velocity.y = MaxVelocity * (yDir / length);
}

void PointProjectile::update(float deltaTime)
{
    if (!isAlive())
        return;

    Projectile::update(deltaTime);

    // TODO: this collision code shouldnt be here
    Player* player = Game::get().getPlayer();
    if (player)
    {
        if (isColliding(m_position.x, m_position.y - (getHeight() * 0.5f), getWidth(), player->getPosition().x, player->getPosition().y, player->getWidth()))
        {
            player->damage(2.f);
            markAsDead();
        }
    }
}

FireWaveProjectile::FireWaveProjectile(const ProjectileProperties& properties)
    : Projectile(properties)
      , m_timer(0.f)
{
    m_velocity.x = cosf(toRadians(m_rotation)) * MaxVelocity;
    m_velocity.y = sinf(toRadians(m_rotation)) * MaxVelocity;
}

void FireWaveProjectile::update(float deltaTime)
{
    Projectile::update(deltaTime);
    m_timer += deltaTime;
    if (m_timer > 0.35f)
    {
        markAsDead();
        return;
    }

    if (m_timer > 0.25f)
        m_tint.a = 255 - (255 * ((m_timer - 0.25f) / 0.1f));

    destroyCollidingParticles(m_position.x, m_position.y, getWidth());
}

Projectile* createProjectile(const ProjectileProperties& properties)
{
    Projectile* projectile = nullptr;
    switch (properties.type)
    {
    case ProjectileProperties::Type::Point:
        projectile = new PointProjectile(properties);
        break;
    case ProjectileProperties::Type::FireWave:
        projectile = new FireWaveProjectile(properties);
        break;
    default:
        break;
    }

    if (projectile)
        projectile->init(properties.textureName);

    return projectile;
}
