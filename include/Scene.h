#pragma once

#include "raylib.h"

class Scene
{
public:
    virtual ~Scene() {}
    
    virtual void init() {}
    virtual void checkInput() = 0;
    virtual void update(float deltaTime) {}
    virtual void draw() const = 0;
    virtual void close() {}
};
