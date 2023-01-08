#pragma once
#include <list>

#include "LevelState.h"
#include "Settings.h"


class Player;
class GameObject;
class Scene;

struct PlayerStats
{
    size_t level;
    size_t harvestedCount;
};


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
    Player* getPlayer();
    void gameOver(const PlayerStats& playerStats);
    PlayerStats getPlayerStats() { return m_playerStats; }

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

    PlayerStats m_playerStats;
};
