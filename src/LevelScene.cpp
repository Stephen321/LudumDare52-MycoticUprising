#include "LevelScene.h"

#include "AppleTree.h"
#include "GameObject.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "StaticGameObject.h"
#include "Utilities.h"


LevelScene::LevelScene()
= default;

LevelScene::~LevelScene()
{
    LevelScene::close();
}

void LevelScene::init()
{
    m_level = getSettings().level;

    // TODO: should all be loaded from level config

    // create background
    m_gameObjects.emplace_back(new StaticGameObject);
    m_gameObjects.back()->init("levels\\0", 0);
    m_gameObjects.back()->setOrigin(0.f, 0.f);

    // create player
    m_gameObjects.emplace_back(new Player);
    m_player = dynamic_cast<Player*>(m_gameObjects.back());
    m_player->init();
    resetPlayer();

    // add enemies
    // TODO: texturemanager to share textures
    m_gameObjects.emplace_back(new AppleTree);
    m_gameObjects.back()->init("appleTreeEnemy");
    m_gameObjects.back()->setPosition(getScreenX(0.2f), getScreenY(0.2f));

    // setup any singleton game objects
    ProjectileManager::get().init();
}

void LevelScene::checkInput()
{
    m_player->checkInput();
}

void LevelScene::update(float deltaTime)
{
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
