#pragma once
#include "StaticGameObject.h"

class ApplePickup : public StaticGameObject
{
public:
    void init(const std::string& textureName, size_t drawLayer) override;
    void update(float deltaTime) override;
};
