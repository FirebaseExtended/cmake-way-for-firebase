//
// Created by Patrick Martin on 9/2/20.
//

#include "EnemyManager.h"
#include "Config.h"

USING_NS_CC;

EnemyManager *EnemyManager::createWithConfig(const EnemyManager::Config &config) {
    auto *enemyManager = new(std::nothrow) EnemyManager();
    if (enemyManager && enemyManager->initWithConfig(config)) {
        enemyManager->autorelease();
        return enemyManager;
    }
    CC_SAFE_DELETE(enemyManager);
    return nullptr;
}

bool EnemyManager::initWithConfig(const EnemyManager::Config &config) {
    if (!Node::init()) {
        return false;
    }

    _config = config;
    _config.camera->retain();

    // schedule the first update
    scheduleOnce([this](float) {
        float rightEdge = computeCameraRightEdge();
        _lastRightEdge = rightEdge;

        scheduleUpdate();
    }, 0, "first update");
    return true;
}

void EnemyManager::update(float delta) {
    float rightEdge = computeCameraRightEdge();
    float lastEnemyIndex = floorf(_lastRightEdge / _config.spawnDistance);
    float realEnemyIndex = rightEdge / _config.spawnDistance;
    float enemyIndex = floorf(realEnemyIndex);
    if (enemyIndex > lastEnemyIndex) {
        // try to spawn
        float spawnChance = _randomDistribution(_randomGenerator);
        if (spawnChance <= _config.spawnChance) {
            spawnEnemy(Vec2(enemyIndex * _config.spawnDistance, ::Config::kGroundLevel));
        }
    }

    _lastRightEdge = rightEdge;
    Node::update(delta);
}

void EnemyManager::cleanup() {
    if (_config.camera) {
        CC_SAFE_RELEASE(_config.camera);
    }

    Node::cleanup();
}

float EnemyManager::computeCameraRightEdge() const {
    auto camera = _config.camera;
    auto cameraWorld = camera->convertToWorldSpaceAR(Vec2::ZERO);
    return cameraWorld.x + _director->getVisibleSize().width / 2;
}

void EnemyManager::spawnEnemy(const Vec2& position) {
    auto enemy = Sprite::createWithTexture(_config.enemyTexture);
    enemy->setAnchorPoint(Vec2(0.5f, 0));
    enemy->setPosition(position);
    auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
    enemyBody->setCategoryBitmask(::Config::kEnemyCollisionCategory);
    enemyBody->setContactTestBitmask(-1);
    enemy->addComponent(enemyBody);
    addChild(enemy);
}
