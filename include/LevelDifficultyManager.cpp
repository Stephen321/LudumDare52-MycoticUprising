#include "LevelDifficultyManager.h"

LevelDifficultyManager& LevelDifficultyManager::get()
{
    static LevelDifficultyManager levelDifficultyManager;
    return levelDifficultyManager;
}

LevelDifficultyManager::LevelDifficultyManager()
    : m_level(0)
{
    m_levels.push_back({1, 0.8f, 0.8f});
    m_levels.push_back({2, 0.8f, 0.8f});
    m_levels.push_back({4, 0.85f, 0.85f});
    m_levels.push_back({5, 0.9f, 0.9f});
    m_levels.push_back({5, 0.9f, 0.9f});
    m_levels.push_back({6, 0.95f, 0.95f});
    m_levels.push_back({6, 1.05f, 1.05f});
    m_levels.push_back({6, 1.05f, 1.05f});
    m_levels.push_back({8, 1.05f, 1.05f});
    m_levels.push_back({8, 1.05f, 1.05f});
    m_levels.push_back({8, 1.05f, 1.05f});
    m_levels.push_back({10, 1.05f, 1.05f});
    m_levels.push_back({10, 1.15f, 1.15f});
    m_levels.push_back({12, 1.2f, 1.2f});
    m_levels.push_back({12, 1.25f, 1.25f});
    m_levels.push_back({14, 1.25f, 1.25f});
    m_levels.push_back({14, 1.25f, 1.25f});

    // TODO: for jam to stop level crash on max level
    LevelDifficulty difficulty = {12, 1.25f, 1.25f};
    for (size_t i = 0; i < 50; i++)
    {
        difficulty.speedScale *= 1.001f;
        difficulty.fireRateScale *= 1.001f;
        m_levels.push_back(difficulty);
    }
}
