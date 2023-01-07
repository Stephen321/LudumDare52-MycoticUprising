#include "Game.h"

#include "Constants.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "raylib.h"
#include "Scene.h"
#include "Utilities.h"

Game::Game()
    : m_currentSceneIndex(0)
{
}

Game::~Game()
{
}

Game& Game::get()
{
    static Game game;
    return game;
}

Settings& Game::getSettings()
{
    return m_settings;
}

void Game::init()
{
    m_settings.config = getConfig();

    // init window
    InitWindow(m_settings.config.screenWidth, m_settings.config.screenHeight, WINDOW_TITLE);
    SetTargetFPS(60);

    // init audio
    InitAudioDevice();

    // init m_scenes
    m_scenes[SCENE_INDEX_MENU] = new MenuScene;
    m_scenes[SCENE_INDEX_GAME] = new GameScene;
    switchScene(SCENE_INDEX_MENU);
}

void Game::run()
{
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // input
        m_scenes[m_currentSceneIndex]->checkInput();

        // update
        const float deltaTime = GetFrameTime();
        m_scenes[m_currentSceneIndex]->update(deltaTime);

        // draw
        BeginDrawing();
        m_scenes[m_currentSceneIndex]->draw();
        EndDrawing();
    }
}

int Game::close()
{
    m_scenes[m_currentSceneIndex]->close();
    for (Scene*& scene : m_scenes)
        delete scene;

    // unload resources

    // close audio
    CloseAudioDevice();

    // close window
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void Game::switchScene(size_t sceneIndex)
{
    m_scenes[m_currentSceneIndex]->close();
    m_currentSceneIndex = sceneIndex;
    m_scenes[m_currentSceneIndex]->init();
}