#pragma once
#include <list>

#include "GameObject.h"
#include "Projectile.h"


// TODO: necessary? maybe later
class ProjectileManager : public GameObject
{
public:
    static ProjectileManager& get();
    void update(float deltaTime) override {}
    void init(const std::string& textureName = "invalid", size_t drawLayer = 2) override {}
    void addProjectile(const ProjectileProperties& properties);

private:
    ProjectileManager();
    ~ProjectileManager() override;
    ProjectileManager(const ProjectileManager&) = delete;
    ProjectileManager& operator=(const ProjectileManager&) = delete;
};
