#include "Player.h"

#include "Enemy.h"
#include "Game.h"
#include "ProjectileManager.h"
#include "TextureManager.h"
#include "Utilities.h"

Player::Player()
    : DynamicGameObject(115.f)
      , MaxHealth(100)
      , m_dashTimer(0.f)
      , m_dashing(false)
      , m_dashCooldown(0.f)
      , m_harvestTimer(0.f)
      , m_harvesting(false)
      , m_harvestCooldown(0.f)
      , m_harvestedCount(0)
{
    m_health = MaxHealth;
}

void Player::init(const std::string& textureName, size_t drawLayer)
{
    m_hasDrag = true;
    DynamicGameObject::init("Player", 3);

    // TODO: hack. should be anim system
    m_dashTexture = TextureManager::get().loadTexture("playerDash");
    m_harvestTexture = TextureManager::get().loadTexture("playerSickle");
}

void Player::checkInput()
{
    // TODO: why the 1000.f scale
    const float AccelerationScale = 3000.f;

    // TODO: holding 2 keys then letting go of one keeps in same direction
    m_acceleration = {};
    if (IsKeyDown(KEY_W))
    {
        m_acceleration.y = -AccelerationScale;
    }
    else if (IsKeyDown(KEY_S))
    {
        m_acceleration.y = AccelerationScale;
    }
    if (IsKeyDown(KEY_A))
    {
        m_acceleration.x = -AccelerationScale;
    }
    else if (IsKeyDown(KEY_D))
    {
        m_acceleration.x = AccelerationScale;
    }

    if (IsKeyPressed(KEY_W))
    {
        // m_velocity.x *= 0.7f;
        // m_acceleration.x *= 0.0f;
        // m_acceleration.y = -AccelerationScale;
    }
    else if (IsKeyPressed(KEY_S))
    {
        // m_velocity.x *= 0.7f;
        // m_acceleration.x *= 0.0f;
        // m_acceleration.y = AccelerationScale;
    }
    if (IsKeyPressed(KEY_A))
    {
        // m_velocity.y *= 0.7f;
        // m_acceleration.y *= 0.0f;
        // m_acceleration.x = -AccelerationScale;
    }
    else if (IsKeyPressed(KEY_D))
    {
        // m_velocity.y *= 0.7f;
        // m_acceleration.y *= 0.0f;
        // m_acceleration.x = AccelerationScale;
    }

    if (IsKeyReleased(KEY_W))
    {
        // m_acceleration.y = 0.f;
    }
    else if (IsKeyReleased(KEY_S))
    {
        // m_acceleration.y = 0.f;
    }
    if (IsKeyReleased(KEY_A))
    {
        // m_acceleration.x = 0.f;
    }
    else if (IsKeyReleased(KEY_D))
    {
        // m_acceleration.x = 0.f;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ProjectileProperties properties;
        properties.textureName = "fireWall";
        properties.maxVelocity = 120.f;
        properties.type = ProjectileProperties::Type::FireWave;

        // calculate direction to mouse
        float xDir = GetMouseX() - m_position.x;
        float yDir = GetMouseY() - m_position.y;
        float length = getLength(xDir, yDir);
        xDir /= length;
        yDir /= length;
        properties.startX = m_position.x + (xDir * 24.f);
        properties.startY = m_position.y + (yDir * 24.f);

        const float rotation = toDegrees(atan2f(yDir, xDir));
        if (rotation > 180.f && rotation < 270.f)
            properties.textureName += "Flipped";

        properties.rotation = rotation;
        ProjectileManager::get().addProjectile(properties);

        properties.rotation = rotation + 30;
        ProjectileManager::get().addProjectile(properties);

        properties.rotation = rotation - 30;
        ProjectileManager::get().addProjectile(properties);
    }

    if (!m_harvesting && m_dashCooldown < 0.f && !m_dashing && isMoving())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            m_dashing = true;
            m_velocityBeforeDash = m_velocity;
        }
    }

    if (!m_harvesting && !m_dashing)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            m_harvesting = true;
            harvestEnemies();
        }
    }
}

void Player::update(float deltaTime)
{
    if (m_dashing)
    {
        Vector2 normalizedVelocity{};
        normalize(m_velocity.x, m_velocity.y, normalizedVelocity.x, normalizedVelocity.y);
        m_velocity.x = normalizedVelocity.x * m_maxVelocity * 2.5f;
        m_velocity.y = normalizedVelocity.y * m_maxVelocity * 2.5f;
        m_position.x += m_velocity.x * deltaTime;
        m_position.y += m_velocity.y * deltaTime;

        m_dashTimer += deltaTime;
        if (m_dashTimer > 0.24f)
        {
            m_dashing = false;
            m_dashCooldown = 0.2f;
            m_dashTimer = 0.f;
            m_velocity = m_velocityBeforeDash;
        }
    }
    else
    {
        DynamicGameObject::update(deltaTime);
    }
    m_dashCooldown -= deltaTime;

    if (m_harvesting)
    {
        m_harvestTimer += deltaTime;
        if (m_harvestTimer > 0.3f)
        {
            m_harvesting = false;
            m_harvestCooldown = 0.1f;
            m_harvestTimer = 0.f;
        }
    }


    // wrap around
    float halfWidth = (float)m_texture.width * 0.5f;
    float halfHeight = (float)m_texture.height * 0.5f;

    if (m_position.x < -halfWidth)
    {
        m_position.x = (float)GetScreenWidth() + halfWidth;
    }
    else if (m_position.x > (float)GetScreenWidth() + halfWidth)
    {
        m_position.x = -halfWidth;
    }

    if (m_position.y < -halfHeight)
    {
        m_position.y = (float)GetScreenHeight() + halfHeight;
    }
    else if (m_position.y > (float)GetScreenHeight() + halfHeight)
    {
        m_position.y = -halfHeight;
    }
}

void Player::damage(float amount)
{
    if (m_health > 0)
        m_health -= amount;
    else
    {
        m_health = 0.f;
    }
}

void Player::receivedPickup()
{
    m_health += 10;
    if (m_health > MaxHealth)
        m_health = MaxHealth;
}

void Player::harvestEnemies()
{
    // TODO: ew. collision system needed
    for (GameObject* gameObject : Game::get().getGameObjectsRef())
    {
        Enemy* enemy = dynamic_cast<Enemy*>(gameObject);
        if (enemy)
        {
            if (isColliding(m_position.x, m_position.y, getWidth(),
                            enemy->getPosition().x,
                            enemy->getPosition().y,
                            enemy->getWidth()))
            {
                // TODO: how to determine this amount
                if (enemy->harvest(200.f))
                    m_harvestedCount++;
            }
        }
    }
}

void Player::draw() const
{
    if (!m_dashing && !m_harvesting)
    {
        DynamicGameObject::draw();
        return;
    }

    // TODO: shouldn't need to do all this just to dash
    Rectangle source;
    source.x = 0.f;
    source.y = 0.f;
    source.width = (m_horizontalFlip ? -1.f : 1.f) * (float)m_texture.width;
    source.height = (float)m_texture.height;

    Rectangle destination;
    destination.x = m_position.x;
    destination.y = m_position.y;
    destination.width = (float)m_texture.width;
    destination.height = (float)m_texture.height;

    if (m_dashing)
    {
        DrawTexturePro(m_dashTexture, source, destination, m_origin, m_rotation, m_tint);
    }
    else if (m_harvesting)
    {
        DrawTexturePro(m_harvestTexture, source, destination, m_origin, m_rotation, m_tint);
    }
#ifdef GAME_DEBUG
    if (getWidth() < 400.f)
        DrawCircleLines(m_position.x, m_position.y, getWidth(), RED);
#endif
}
