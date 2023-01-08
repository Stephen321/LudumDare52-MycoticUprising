#pragma once
#include "GameObject.h"

class DynamicGameObject : public GameObject
{
public:
    explicit DynamicGameObject(const float maxVelocity);

    void update(float deltaTime) override;
    void draw() const override;

protected:
    bool isMoving() const;
    bool isAccelerating() const;
    Vector2 m_acceleration;
    Vector2 m_velocity;
    const float MaxVelocity;
    int m_direction;
    bool m_hasDrag;

private:
};
