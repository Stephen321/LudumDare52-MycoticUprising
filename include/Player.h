#pragma once
#include "Character.h"

class Player : public Character
{
public:
    Player();
    void init(const std::string& textureName = "", size_t drawLayer = 0) override;
    void checkInput();
    void update(float deltaTime) override;
};
