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

    // schedule the first update, this avoids a redundant branch every frame
    scheduleOnce([this](float) {
        // only start spawning objects off screen, so wait for the first frame for the camera to be
        // ready and cache that value
        float rightEdge = computeCameraRightEdge();
        _lastRightEdge = rightEdge;

        // start normal updates
        scheduleUpdate();
    }, 0, "first update");
    return true;
}

/*!
 * Enemies are spawned during the update. Some quick notes on the algorithm.
 *
 * Enemies are spawned in a logical queue. First space is divided up into enemy slots. When a slot
 * becomes visible, an enemy object is spawned into it if the current queue dictates that it should
 * contain an enemy.
 *
 * The queue is of a fixed size and is front-loaded with enemies. That is if the size is 4 enemies
 * and 2 enemies in this queue are rolled, the first two slots will have enemies and the second two
 * will not.
 *
 * This means that if the queue size, index in the queue, and enemies in the queue are known, we can
 * decide at any given point if an enemy needs to be spawned. That is what the math below is doing,
 * and it is entirely configurable in @file Config.h
 */
void EnemyManager::update(float delta) {
    if (_spawnIndex >= ::Config::kSpawnQueueSize) {
        _enemiesToSpawn = _randomDistribution(_randomGenerator);
        _spawnIndex = 0;
        log("Will spawn %d enemies", _enemiesToSpawn);
    }
    float rightEdge = computeCameraRightEdge();
    float lastEnemyIndex = floorf(_lastRightEdge / _config.spawnDistance);
    float realEnemyIndex = rightEdge / _config.spawnDistance;
    float enemyIndex = floorf(realEnemyIndex);
    if (enemyIndex > lastEnemyIndex) {
        log("Checking to spawn... index: %d -- of %d", _spawnIndex, _enemiesToSpawn);
        if (_spawnIndex++ < _enemiesToSpawn) {
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
    enemy->setAnchorPoint(Vec2(0, 0));
    enemy->setPosition(position);
    Size collisionVolume = enemy->getContentSize();
    collisionVolume.width *= ::Config::kEnemyCrabHorizontalCollisionScale;
    auto enemyBody = PhysicsBody::createBox(collisionVolume);
    enemyBody->setCategoryBitmask(::Config::kEnemyCollisionCategory);
    enemyBody->setContactTestBitmask(-1);
    enemy->addComponent(enemyBody);
    addChild(enemy);
}
