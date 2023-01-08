#include <ctime>
#include "Game.h"

// TODO:
//  - all sound needs to be implemented properly
//  - see other todos


int main()
{
    srand(time(0));
    Game& game = Game::get();
    game.init();
    game.run();
    return game.close();
}
