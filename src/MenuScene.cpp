#include "MenuScene.h"

#include "Game.h"
#include "Utilities.h"

void MenuScene::init()
{
}

void MenuScene::checkInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        Game::get().switchScene(SCENE_INDEX_GAME);
    }
}

void MenuScene::update(float deltaTime)
{
}

void MenuScene::draw()
{
    ClearBackground(BEIGE);
    
    DrawText("Mycotic Uprising", getScreenX(0.1f), getScreenY(0.15f), 34.f, GRAY);

    DrawText(
        "Stop the spread of the sentient fungi. Harestable crops are walking rampant.\n - Use left click for flame attacks\n - Space to roll\n - Right click to harvest.",
        getScreenX(0.14f), getScreenY(0.25f), 22.f, DARKGRAY);

    DrawText("Press Space to start", getScreenX(0.37f), getScreenY(0.7f), 28.f, DARKGRAY);
}

void MenuScene::close()
{
}
