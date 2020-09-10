/*
 * Copyright 2020 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PROJ_ANDROID_ENEMYMANAGER_H
#define PROJ_ANDROID_ENEMYMANAGER_H

#include "cocos2d.h"
#include "Config.h"

class EnemyManager : public cocos2d::Node {
public:
    struct Config {
        cocos2d::Camera *camera;
        cocos2d::Texture2D *enemyTexture;
        float spawnDistance;
        float spawnChance;
    };

    static EnemyManager *createWithConfig(const Config &config);

    virtual bool initWithConfig(const Config &config);

    void update(float delta) override;

    void cleanup() override;

private:
    //! @brief determines where the right edge of the camera is - used for spawning offscreen
    float computeCameraRightEdge() const;

    void spawnEnemy(const cocos2d::Vec2 &position);

    //! @brief the random number engine used for spawning, seeded
    std::default_random_engine _randomGenerator = std::default_random_engine(
            std::chrono::system_clock::now().time_since_epoch().count());

    //! @brief the random distribution for spawning enemies. Configured at compile time
    std::uniform_int_distribution<int> _randomDistribution = std::uniform_int_distribution<int>(
            ::Config::kMinEnemiesToSpawn, ::Config::kMaxEnemiesToSpawn);
    Config _config;
    float _lastRightEdge;

    //! @brief the index in the current spawn queue for enemies
    int _spawnIndex = ::Config::kSpawnQueueSize;

    //! @brief the number of enemies in the current spawn queue
    int _enemiesToSpawn;
};


#endif //PROJ_ANDROID_ENEMYMANAGER_H
