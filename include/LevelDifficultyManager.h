#pragma once
#include <vector>

struct LevelDifficulty
{
    size_t enemyCount;
    float fireRateScale;
    float speedScale;
};

// TODO: everything to do with this should be removed
class LevelDifficultyManager
{
public:
    static LevelDifficultyManager& get();

    size_t getEnemyCount() { return m_levels[m_level].enemyCount; }
    float getFireRateScale() { return m_levels[m_level].fireRateScale; }
    float getSpeedScale() { return m_levels[m_level].speedScale; }

    size_t getMaxLevel() { return m_levels.size(); }
    void setLevel(size_t level) { m_level = level; }

private:
    LevelDifficultyManager();
    ~LevelDifficultyManager() {}
    LevelDifficultyManager(const LevelDifficultyManager&) = delete;
    LevelDifficultyManager& operator=(const LevelDifficultyManager&) = delete;

    size_t m_level;
    std::vector<LevelDifficulty> m_levels;
};
