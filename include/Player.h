#pragma once
#include "DynamicGameObject.h"

class Player : public DynamicGameObject
{
public:
    Player();
    void init(const std::string& textureName = "invalid", size_t drawLayer = 1) override;
    void checkInput();
    void update(float deltaTime) override;

    // TODO: redo collision code
    void damage(float amount);

    int getHealth() const { return m_health; }
    size_t getHarvestedCount() const { return m_harvestedCount; }
    void receivedPickup();

private:
    void harvestEnemies();

    int m_health;
    const int MaxHealth;

    size_t m_harvestedCount;

    // TODO: state machine
    float m_dashTimer;
    bool m_dashing;
    float m_dashCooldown;

    bool m_harvesting;
    float m_harvestTimer;
    float m_harvestCooldown;

public:
    void draw() const override;

private:
    Vector2 m_velocityBeforeDash;
    Texture2D m_dashTexture;
    Texture2D m_harvestTexture;
};
