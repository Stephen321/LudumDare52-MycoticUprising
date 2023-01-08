#pragma once
#include "GameObject.h"

class StaticGameObject : public GameObject
{
public:
    void init(const std::string& textureName, size_t drawLayer) override;
    void update(float deltaTime) override {}
};
