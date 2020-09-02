//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsicleScene.h"
#include "GroundManager.h"
#include "Config.h"

USING_NS_CC;

cocos2d::Scene *PopsicleScene::createScene() {
    return PopsicleScene::create();
}

bool PopsicleScene::init() {
    auto physicsCreated = Scene::initWithPhysics();
    if (!physicsCreated) {
        return false;
    }

    // setup physics, I might take this out?
    auto physicsWorld = this->getPhysicsWorld();
#ifdef DEBUG_PHYSICS
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    physicsWorld->setGravity(Vec2(0, Config::kGravity));

    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();

    // load textures
    auto textureCache = director->getTextureCache();
    auto playerTexture = textureCache->addImage("purple.png");
    auto groundTexture = textureCache->addImage("grass-middle.png");

    // create the player
    _player = PopsiclePlayer::createWithTexture(playerTexture);
    _player->setPosition(Vec2(0.f, 0.f));
    this->addChild(_player);


    // configure the camera
    auto camera = this->getDefaultCamera();
    camera->setBackgroundBrush(
            CameraBackgroundBrush::createColorBrush(Color4F(Config::kCornflowerBlue), 1.f));

    // setup the ground
    auto groundManager = GroundManager::createWithCameraAndGroundTexture(camera, groundTexture);
    addChild(groundManager);

    // offset the camera by the ground height
    _cameraOffset = Vec2(0, -groundManager->getGroundHeight());
    centerCamera(camera, visibleSize);

    // start running the level
    scheduleUpdate();
    return true;
}

void PopsicleScene::update(float delta) {
    auto camera = getDefaultCamera();
    auto director = Director::getInstance();

    centerCamera(camera, director->getVisibleSize());

    Node::update(delta);
}

void PopsicleScene::cleanup() {
    CC_SAFE_RELEASE(_player);

    Node::cleanup();
}

void PopsicleScene::centerCamera(Camera *camera, const Size &visibleSize) {
    Vec2 cameraPosition;
    cameraPosition.x += _player->getPositionX() + visibleSize.width / 4;
    cameraPosition.y += visibleSize.height / 2;
    cameraPosition += _cameraOffset;
    camera->setPosition(cameraPosition);
}
