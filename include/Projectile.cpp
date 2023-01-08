#include "Projectile.h"

#include "Utilities.h"

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

FireWaveProjectile::FireWaveProjectile(const ProjectileProperties& properties)
    : Projectile(properties)
      , m_timer(0.f)
{
    m_velocity.x = cosf(toRadians(m_rotation)) * MaxVelocity;
    m_velocity.y = sinf(toRadians(m_rotation)) * MaxVelocity;
    m_horizontalFlip = m_velocity.x < 0.f;
}

void FireWaveProjectile::update(float deltaTime)
{
    Projectile::update(deltaTime);
    m_timer += deltaTime;
    if (m_timer > 0.8f)
    {
        markAsDead();
        m_tint.a = 0;
    }
    else if (m_timer > 0.65f)
        m_tint.a = 255 - (255 * ((m_timer - 0.6f) / 0.2f));
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
