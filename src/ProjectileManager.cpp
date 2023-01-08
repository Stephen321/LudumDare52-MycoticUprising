#include "ProjectileManager.h"

#include <utility>

#include "Game.h"
#include "Projectile.h"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
    ProjectileManager::close();
}

ProjectileManager& ProjectileManager::get()
{
    static ProjectileManager projectileManager;
    return projectileManager;
}

void ProjectileManager::addProjectile(const ProjectileProperties& properties)
{
    Game::get().getGameObjectsRef().push_back(createProjectile(std::move(properties)));
}