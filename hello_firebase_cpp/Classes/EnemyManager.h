//
// Created by Patrick Martin on 9/2/20.
//

#ifndef PROJ_ANDROID_ENEMYMANAGER_H
#define PROJ_ANDROID_ENEMYMANAGER_H

#include "cocos2d.h"

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
    float computeCameraRightEdge() const;

    void spawnEnemy(const cocos2d::Vec2 &position);

    std::default_random_engine _randomGenerator = std::default_random_engine(
            std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> _randomDistribution = std::uniform_real_distribution<float>(
            0.f, 1.f);
    Config _config;
    float _lastRightEdge;
};


#endif //PROJ_ANDROID_ENEMYMANAGER_H
