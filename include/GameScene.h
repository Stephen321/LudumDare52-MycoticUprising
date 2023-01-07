#pragma once
#include <list>

#include "Scene.h"

class Player;
class GameObject;

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
    void draw() const;
    void close();

private:
    void resetPlayer();
    
    size_t m_level = 0;

    std::list<GameObject*> m_gameObjects;
    Player* m_player;
};
