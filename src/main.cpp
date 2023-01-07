#include "Game.h"
#include "raylib.h"
#include "Utilities.h"



int main()
{
    Game& game = Game::get();
    game.init();
    game.run();
    return game.close();
}
