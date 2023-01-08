#include "ApplePickup.h"

#include "Game.h"
#include "Player.h"
#include "SoundUtilities.h"
#include "Utilities.h"

class Player;

void ApplePickup::init(const std::string& textureName, size_t drawLayer)
{
    StaticGameObject::init("applePickup", 1);
    m_sound = loadSound("pickup");
}

void ApplePickup::update(float deltaTime)
{
    StaticGameObject::update(deltaTime);
    // TODO: this collision code shouldnt be here
    Player* player = Game::get().getPlayer();
    if (player)
    {
        if (Utilities::isColliding(m_position.x, m_position.y - (getHeight() * 0.5f), getWidth(), player->getPosition().x,
                        player->getPosition().y, player->getWidth()))
        {
            player->receivedPickup();
            PlaySound(m_sound);
            markAsDead();
        }
    }
}

void ApplePickup::close()
{
    StaticGameObject::close();

    UnloadSound(m_sound);
}
