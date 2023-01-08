#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
    void checkInput() override;
    void draw() const override;
};
