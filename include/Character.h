#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
    explicit Character(const float maxVelocity);

    void update(float deltaTime) override;

protected:
    bool isMoving() const;
    bool isAccelerating() const;
    Vector2 m_acceleration;
    Vector2 m_velocity;

private:
    const float MaxVelocity;
};
