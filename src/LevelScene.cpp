#include "LevelScene.h"

#include "AppleTree.h"
#include "Game.h"
#include "GameObject.h"
#include "LevelDifficultyManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "SoundUtilities.h"
#include "StaticGameObject.h"
#include "Utilities.h"


LevelScene::LevelScene()
    : m_targetHarvestedCount(0)
{
}

LevelScene::~LevelScene()
{
    LevelScene::close();
}

void LevelScene::init()
{
    // TODO: get rid of this from settings
    // m_level = getSettings().level;

    // TODO: should all be loaded from level config

    // create background
    m_gameObjects.emplace_back(new StaticGameObject);
    m_gameObjects.back()->init("levels\\0", 0);
    m_gameObjects.back()->setOrigin(0.f, 0.f);

    // create player
    m_gameObjects.emplace_back(new Player);
    m_player = dynamic_cast<Player*>(m_gameObjects.back());
    m_player->init();

    m_level = 0;
    resetLevel(m_level);

    // setup any singleton game objects
    ProjectileManager::get().init();

    m_levelChangeSound = loadSound("levelChange");
    SetSoundVolume(m_levelChangeSound, 0.45f);


    m_music = LoadMusicStream(".\\resources\\music\\game.wav");
    m_music.looping = true;
    PlayMusicStream(m_music);
    SetMusicVolume(m_music, 0.6f);
}

void LevelScene::checkInput()
{
    m_player->checkInput();
}

void LevelScene::update(float deltaTime)
{
    UpdateMusicStream(m_music);
    
    // check game over
    if (m_player->getHealth() == 0)
        Game::get().gameOver({m_level, m_player->getHarvestedCount()});

    if (m_player->getHarvestedCount() == m_targetHarvestedCount)
        resetLevel(m_level++);

    // TODO: check for winning a level


    // remove any dead objects
    m_gameObjects.erase(std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject* go)
    {
        if (!go)
            return true;
        if (!go->isAlive())
        {
            go->close();
            delete go;
            return true;
        }
        return false;
    }), m_gameObjects.end());

    // update
    for (GameObject* gameObject : m_gameObjects)
    {
        if (gameObject)
        {
            gameObject->update(deltaTime);
        }
    }
    // update any singleton game objects
    ProjectileManager::get().update(deltaTime);

    // (state is always a frame late)
    updateState();
}

void LevelScene::draw() const
{
    ClearBackground(DARKGREEN);
    for (size_t layer = 0; layer < DRAW_LAYER_COUNT; layer++)
    {
        for (const GameObject* gameObject : m_gameObjects)
        {
            if (gameObject &&
                gameObject->isVisible() &&
                gameObject->getDrawLayer() == layer)
            {
                gameObject->draw();
            }
        }
    }

    // draw any singleton game objects
    ProjectileManager::get().draw();


    // TODO: HUD class
    DrawText(TextFormat("Health: %d", m_player->getHealth()), getScreenX(0.1f), getScreenY(0.06f), 16.f, WHITE);
    DrawText(TextFormat("Harvested: %d", m_player->getHarvestedCount()), getScreenX(0.75f), getScreenY(0.06f), 16.f,
             WHITE);
    DrawText(TextFormat("Level: %d", m_level + 1), getScreenX(0.43f), getScreenY(0.03f), 18.f,
             WHITE);
}

void LevelScene::close()
{
    // TODO: crashes
    //     UnloadSound(m_levelChangeSound);
    // UnloadMusicStream(m_music);
    
    for (GameObject*& gameObject : m_gameObjects)
    {
        if (gameObject)
            gameObject->close();
        delete gameObject;
    }
    m_gameObjects.clear();

    // close any singleton game objects
    ProjectileManager::get().close();
}

LevelState LevelScene::getState()
{
    return m_state;
}

std::list<GameObject*>& LevelScene::getGameObjectsRef()
{
    return m_gameObjects;
}

Player* LevelScene::getPlayer()
{
    return m_player;
}

void LevelScene::resetPlayer()
{
    if (!m_player)
        return;

    m_player->setPosition((float)getScreenX(0.5f), (float)getScreenY(0.5f));
}

void LevelScene::updateState()
{
    m_state.playerPositionX = m_player->getPosition().x;
    m_state.playerPositionY = m_player->getPosition().y;
}

void LevelScene::placeEnemies()
{
    size_t enemyCount = LevelDifficultyManager::get().getEnemyCount();

    m_targetHarvestedCount = m_player->getHarvestedCount() + enemyCount;

    // TODO: should be smarter than randomly around the outside
    for (size_t i = 0; i < enemyCount; i++)
    {
        m_gameObjects.emplace_back(new AppleTree);
        m_gameObjects.back()->init("appleTreeEnemy");
        float randomX;
        float randomY;


        int side = rand() % 4;
        if (side == 0)
        {
            randomX = (float)GetScreenWidth() * ((float)rand() / (float)RAND_MAX);
            randomY = -25.f;
        }
        else if (side == 1)
        {
            randomX = (float)GetScreenWidth() * ((float)rand() / (float)RAND_MAX);
            randomY = GetScreenHeight() + 25.f;
        }
        if (side == 2)
        {
            randomX = -25.f;
            randomY = (float)GetScreenHeight() * ((float)rand() / (float)RAND_MAX);
        }
        else if (side == 3)
        {
            randomX = GetScreenWidth() + 25.f;
            randomY = (float)GetScreenHeight() * ((float)rand() / (float)RAND_MAX);
        }

        m_gameObjects.back()->setPosition(randomX, randomY);
    }
}

void LevelScene::resetLevel(size_t newLevel)
{
    if (newLevel != 0)
        PlaySound(m_levelChangeSound);
    LevelDifficultyManager::get().setLevel(m_level);
    resetPlayer();
    placeEnemies();
}
