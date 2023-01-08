#include <ctime>

#include "Game.h"
#include "raylib.h"
#include "Utilities.h"



int main()
{
    srand(time(0));
    Game& game = Game::get();
    game.init();
    game.run();
    return game.close();
}
