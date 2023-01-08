#pragma once
#include "DynamicGameObject.h"

class Player : public DynamicGameObject
{
public:
    Player();
    void init(const std::string& textureName = "invalid", size_t drawLayer = 1) override;
    void checkInput();
    void update(float deltaTime) override;
};
