#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
    ~GameScene()
    {
        close();
    }

    void init();
    void checkInput();
    void update(float deltaTime);
    void draw();
    void close();

private:
    size_t m_level = 0;
};
