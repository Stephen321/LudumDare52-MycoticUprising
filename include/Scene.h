#pragma once

#include "raylib.h"

class Scene
{
public:
    virtual ~Scene() {}
    
    virtual void init() = 0;
    virtual void checkInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw() const = 0;
    virtual void close() = 0;
};
