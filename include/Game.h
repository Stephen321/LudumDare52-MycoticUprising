#pragma once
#include <list>

#include "LevelState.h"
#include "Settings.h"


class GameObject;
class Scene;

class Game
{
public:
    void init();
    void run();
    int close();

    // singleton interface
    static Game& get();
    Settings& getSettings();
    void switchScene(size_t sceneIndex);
    LevelState getLevelState();
    std::list<GameObject*>& getGameObjectsRef();

private:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void checkInput();
    void update(float deltaTime);
    void draw() const;

private:
    // scene
    Scene* m_scenes[SCENE_COUNT];
    size_t m_currentSceneIndex;

    Settings m_settings;
};
