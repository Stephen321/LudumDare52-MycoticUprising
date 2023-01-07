#pragma once
#include <string>

#include "raylib.h"

class GameObject
{
public:
    GameObject();

    virtual ~GameObject()
    {
        GameObject::close();
    }

    virtual void init(const std::string& textureName = "", size_t drawLayer = 0);
    virtual void update(float deltaTime) = 0;
    virtual void draw() const;
    virtual void close();

    size_t getDrawLayer() const { return m_drawLayer; }
    bool getAlive() const { return m_alive; }
    void setPosition(float x, float y);
    void markAsDead() { m_alive = false; }

protected:
    Vector2 m_position;
    float m_scale;

private:
    size_t m_drawLayer;
    bool m_alive;
    Texture2D m_texture;
    float m_rotation;
    Color m_tint;
};
