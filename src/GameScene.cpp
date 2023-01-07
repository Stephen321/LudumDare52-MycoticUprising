#include "GameScene.h"

#include "GameObject.h"
#include "Player.h"
#include "Utilities.h"


void GameScene::init()
{
    m_level = getSettings().level;

    // TODO: should all be loaded from level config
    
    // create player
    m_gameObjects.push_back(new Player);
    m_player = dynamic_cast<Player*>(m_gameObjects.back());
    m_player->init();

    resetPlayer();
}

void GameScene::checkInput()
{
    m_player->checkInput();
}

void GameScene::update(float deltaTime)
{
    // remove any dead objects
    m_gameObjects.erase(std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [](const GameObject* go)
    {
        return !go || !go->getAlive();
    }), m_gameObjects.end());

    // update
    for (GameObject* gameObject : m_gameObjects)
    {
        gameObject->update(deltaTime);
    }
}

void GameScene::draw() const
{
    ClearBackground(DARKGREEN);
    for (size_t layer = 0; layer < DRAW_LAYER_COUNT; layer++)
    {
        for (const GameObject* gameObject : m_gameObjects)
        {
            if (gameObject->getDrawLayer() == layer)
                gameObject->draw();
        }
    }
}

void GameScene::close()
{
    for (const GameObject* gameObject : m_gameObjects)
    {
        delete gameObject;
    }
    m_gameObjects.clear();
}

void GameScene::resetPlayer()
{
    if (!m_player)
        return;

    m_player->setPosition((float)getScreenX(0.5f), (float)getScreenY(0.5f));
}
