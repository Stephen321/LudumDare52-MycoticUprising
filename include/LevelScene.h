#pragma once
#include <list>

#include "Scene.h"
#include "LevelState.h"

class Player;
class GameObject;

class LevelScene : public Scene
{
public:
    LevelScene();
    ~LevelScene() override;

    void init() override;
    void checkInput() override;
    void update(float deltaTime) override;
    void draw() const override;
    void close() override;

    LevelState getState();
    std::list<GameObject*>& getGameObjectsRef();

private:
    void resetPlayer();
    void updateState();

    size_t m_level = 0;

    // TODO: should be able to share textures
    std::list<GameObject*> m_gameObjects;
    Player* m_player{};

    LevelState m_state;
};
