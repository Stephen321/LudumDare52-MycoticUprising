#pragma once
#include <list>

#include "DynamicGameObject.h"


// TODO: each "Projectile" class could create more or have unique behaviour to reach target

struct ProjectileProperties
{
    float startX = 0.f;
    float startY = 0.f;
    float targetX = 0.f;
    float targetY = 0.f;
    float maxVelocity = 0.f;
    float rotation = 0.f;
    std::string textureName = "invalid";

    enum class Type
    {
        Point
    } type = Type::Point;
};

class Projectile : public DynamicGameObject
{
public:
    Projectile(const ProjectileProperties& properties);

protected:
    ProjectileProperties m_properties;
};

class PointProjectile : public Projectile
{
public:
    explicit PointProjectile(const ProjectileProperties& properties);
};

extern Projectile* createProjectile(const ProjectileProperties& properties);