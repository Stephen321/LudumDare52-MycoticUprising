#pragma once
#include "DynamicGameObject.h"
#include "LevelState.h"
#include "Projectile.h"

class Enemy : public DynamicGameObject
{
public:
    Enemy(const float maxVelocity);

protected:
    LevelState getLevelState() const;
    void fire(const ProjectileProperties& properties);
    
    bool m_infected;
};
