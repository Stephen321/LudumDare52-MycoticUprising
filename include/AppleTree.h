#pragma once
#include <vector>

#include "Enemy.h"

class AppleTree : public Enemy
{
public:
    AppleTree();
    void update(float deltaTime) override;
    void harvested() override;

private:
    // TODO: add a TimerManager to handle all these repeated setups
    // it has one timer and triggers its added timers when needed
    float m_fireTimer;
};
