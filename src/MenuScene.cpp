#include "MenuScene.h"

#include "Game.h"
#include "Utilities.h"

void MenuScene::checkInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        Game::get().switchScene(SCENE_INDEX_LEVEL);
    }
}

void MenuScene::draw() const
{
    ClearBackground(BEIGE);
    
    DrawText("Mycotic Uprising", getScreenX(0.1f), getScreenY(0.12f), 32.f, GRAY);

    DrawText(
        "Stop the spread of the sentient fungi. Harvestable\n trees are walking rampant.\n - Use left click for flame attacks (destroys projectiles)\n - Space to dash\n - Right click to harvest (when in close).",
        getScreenX(0.07f), getScreenY(0.25f), 20.f, DARKGRAY);

    DrawText("Press Space to start", getScreenX(0.3f), getScreenY(0.7f), 26.f, DARKGRAY);
}
