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

    virtual void init(const std::string& textureName = "invalid", size_t drawLayer = 2);
    virtual void update(float deltaTime) = 0;
    virtual void draw() const;
    virtual void close();

    size_t getDrawLayer() const { return m_drawLayer; }
    bool isAlive() const { return m_alive; }
    void setPosition(float x, float y);
    Vector2 getPosition() const { return m_position; }
    void setOrigin(float x, float y);
    void markAsDead() { m_alive = false; m_tint.a = 0; }
    bool isVisible() const;
    float getWidth() const { return (float)m_texture.width; }
    float getHeight() const { return (float)m_texture.height; }

protected:
    Vector2 m_position;
    Vector2 m_origin;
    float m_scale;
    float m_rotation;
    Texture2D m_texture;
    Color m_tint;
    bool m_horizontalFlip;

private:
    size_t m_drawLayer;
    bool m_alive;
};
