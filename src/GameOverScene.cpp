#include "GameOverScene.h"

#include "Game.h"
#include "Utilities.h"

void GameOverScene::checkInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        Game::get().switchScene(SCENE_INDEX_LEVEL);
    }
}

void GameOverScene::draw() const
{
    ClearBackground(BEIGE);

    DrawText("Game Over", getScreenX(0.36f), getScreenY(0.12f), 34.f, GRAY);


    PlayerStats stats = Game::get().getPlayerStats();
    DrawText(
        TextFormat("You lost but you managed to get:\n All the way to level %d with a total harvest count of %d!", stats.level, stats.harvestedCount),
        getScreenX(0.15f), getScreenY(0.41f), 18.f, DARKGRAY);
    
    DrawText("Press Space to return to the main menu", getScreenX(0.15f), getScreenY(0.81f), 22.f, DARKGRAY);
}
