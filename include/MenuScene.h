#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
    ~MenuScene()
    {
        close();
    }
    void init();
    void checkInput();
    void update(float deltaTime);
    void draw() const;
    void close();
};
