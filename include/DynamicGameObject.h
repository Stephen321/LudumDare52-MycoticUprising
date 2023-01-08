#pragma once
#include "GameObject.h"

class DynamicGameObject : public GameObject
{
public:
    explicit DynamicGameObject(const float maxVelocity);

    void update(float deltaTime) override;

protected:
    bool isMoving() const;
    bool isAccelerating() const;
    Vector2 m_acceleration;
    Vector2 m_velocity;
    float m_maxVelocity;
    bool m_hasDrag;

private:
};
