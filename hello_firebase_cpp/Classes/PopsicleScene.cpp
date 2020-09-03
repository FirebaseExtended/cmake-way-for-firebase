//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsicleScene.h"
#include "GroundManager.h"
#include "Config.h"
#include "EnemyManager.h"
#include "GameOverMenu.h"

USING_NS_CC;

cocos2d::Scene *PopsicleScene::createScene() {
    return PopsicleScene::create();
}

bool PopsicleScene::init() {
    auto physicsCreated = Scene::initWithPhysics();
    if (!physicsCreated) {
        return false;
    }

    // setup physics
    auto physicsWorld = this->getPhysicsWorld();
#ifdef DEBUG_PHYSICS
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    physicsWorld->setGravity(Vec2(0, Config::kGravity));

    auto visibleSize = _director->getVisibleSize();

    // load textures
    auto textureCache = _director->getTextureCache();
    auto playerTexture = textureCache->addImage("purple.png");
    auto groundTexture = textureCache->addImage("grass-middle.png");
    auto sunTexture = textureCache->addImage("sun.png");
    auto crabTexture = textureCache->addImage("crab.png");

    // create the player
    _player = PopsiclePlayer::createWithTexture(playerTexture);
    _player->retain();
    _player->setPosition(Vec2(0.f, 0.f));
    this->addChild(_player);


    // configure the camera
    auto camera = this->getDefaultCamera();
    camera->setBackgroundBrush(
            CameraBackgroundBrush::createColorBrush(Color4F(Config::kCornflowerBlue), 1.f));
    _cameraNode = Node::create();
    _cameraNode->retain();
    addChild(_cameraNode);
    camera->setParent(_cameraNode);
    camera->setPosition(Vec2(0, 0));

    // add a happy little sun
    auto sunSprite = Sprite::createWithTexture(sunTexture);
    sunSprite->setAnchorPoint(Vec2(1, 1));
    sunSprite->setPosition(visibleSize / 2);
    _cameraNode->addChild(sunSprite);

    // setup the ground
    auto groundManager = GroundManager::createWithCameraAndGroundTexture(camera, groundTexture);
    addChild(groundManager);

    // offset the camera by the ground height
    _cameraOffset = Vec2(0, -groundManager->getGroundHeight());
    centerCamera(camera, visibleSize);

    // setup enemy spawning
    EnemyManager::Config enemyManagerConfig = {
            .enemyTexture = crabTexture,
            .spawnChance = Config::kEnemySpawnChance,
            .spawnDistance = Config::kEnemySpawnDensity * crabTexture->getContentSize().width,
            .camera = camera
    };
    auto enemyManager = EnemyManager::createWithConfig(enemyManagerConfig);
    addChild(enemyManager);

    // setup collision handling
    auto eventDispatcher = _director->getEventDispatcher();
    _physicsEventListener = EventListenerPhysicsContact::create();
    _physicsEventListener->retain();
    _physicsEventListener->onContactBegin = CC_CALLBACK_1(PopsicleScene::handleCollision, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(_physicsEventListener, this);

    // start running the level
    scheduleUpdate();
    return true;
}

void PopsicleScene::update(float delta) {
    auto camera = getDefaultCamera();
    auto director = Director::getInstance();

    centerCamera(camera, director->getVisibleSize());

    if (!_gameOver && _player->didCollideWithEnemy()) {
        auto gameOverMenu = GameOverMenu::create();
        _cameraNode->addChild(gameOverMenu);
        gameOverMenu->setPosition(Vec2::ZERO);
        _gameOver = true;
    }

    Node::update(delta);
}

void PopsicleScene::cleanup() {
    CC_SAFE_RELEASE(_player);
    CC_SAFE_RELEASE(_cameraNode);

    if (_physicsEventListener) {
        auto eventDispatcher = _director->getEventDispatcher();
        eventDispatcher->removeEventListener(_physicsEventListener);
        _physicsEventListener->release();
        _physicsEventListener = nullptr;
    }

    Scene::cleanup();
}

void PopsicleScene::centerCamera(Camera *camera, const Size &visibleSize) {
    Vec2 cameraPosition;
    cameraPosition.x += _player->getPositionX() + visibleSize.width / 4;
    cameraPosition.y += visibleSize.height / 2;
    cameraPosition += _cameraOffset;
    _cameraNode->setPosition(cameraPosition);
}

// cocos uses a signed in, so disable related warnings
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
bool PopsicleScene::handleCollision(PhysicsContact &contact) {
    int collisionCombined = contact.getShapeA()->getCategoryBitmask() | contact.getShapeB()->getCategoryBitmask();
    if (collisionCombined == (Config::kPlayerCollisionCategory | Config::kEnemyCollisionCategory)) {
        // something tagged as the player collided with something tagged as an enemy
        _player->collidedWithEnemy();
    }
    return true;
}
#pragma clang diagnostic pop
