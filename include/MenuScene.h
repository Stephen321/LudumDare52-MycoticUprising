#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
    void checkInput();
    void draw() const;
};
