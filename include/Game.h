#pragma once
#include "Settings.h"


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

private:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void checkInput();
    void update(float deltaTime);
    void draw();

private:
    // scene
    Scene* m_scenes[SCENE_COUNT];
    size_t m_currentSceneIndex;

    Settings m_settings;
};
