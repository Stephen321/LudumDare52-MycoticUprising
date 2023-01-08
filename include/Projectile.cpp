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
}

PointProjectile::PointProjectile(const ProjectileProperties& properties)
    : Projectile(properties)
{
    m_position.x = properties.startX;
    m_position.y = properties.startY;
    m_rotation = properties.rotation;

    float xDir = m_properties.targetX - m_position.x;
    float yDir = m_properties.targetY - m_position.y;
    float length = getLength(xDir, yDir);
    m_velocity.x = MaxVelocity * (xDir / length);
    m_velocity.y = MaxVelocity * (yDir / length);
}

Projectile* createProjectile(const ProjectileProperties& properties)
{
    Projectile* projectile = nullptr;
    switch (properties.type)
    {
    case ProjectileProperties::Type::Point:
        projectile = new PointProjectile(properties);
    }

    if (projectile)
        projectile->init(properties.textureName);

    return projectile;
}
