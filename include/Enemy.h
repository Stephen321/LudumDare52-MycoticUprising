#pragma once
#include "DynamicGameObject.h"
#include "LevelState.h"
#include "Projectile.h"

class Enemy : public DynamicGameObject
{
public:
    Enemy(const float maxVelocity);

    bool harvest(float amount);

    virtual void harvested() = 0;

protected:
    LevelState getLevelState() const;
    void fire(const ProjectileProperties& properties);
    
    bool m_harvested;

    float m_health;
};
