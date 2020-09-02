//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsicleScene.h"
#include "GroundManager.h"

USING_NS_CC;

static const auto kCornflowerBlue = Color3B(100, 149, 237);
static const float kGravity = -200;

cocos2d::Scene *PopsicleScene::createScene() {
    return PopsicleScene::create();
}

bool PopsicleScene::init() {
    auto physicsCreated = Scene::initWithPhysics();
    if (!physicsCreated) {
        return false;
    }

    auto physicsWorld = this->getPhysicsWorld();
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    physicsWorld->setGravity(Vec2(0, kGravity));

    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();

    auto textureCache = director->getTextureCache();
    auto playerTexture = textureCache->addImage("purple.png");

    _player = PopsiclePlayer::createWithTexture(playerTexture);
    _player->setPosition(Vec2(0.f, 0.f));
    this->addChild(_player);

    auto groundTexture = textureCache->addImage("grass-middle.png");
    float groundHeight = groundTexture->getContentSize().height *
                         5;// TODO: grab this from ground manager groundTile->getScale();

    auto camera = this->getDefaultCamera();
    _cameraOffset = Vec2(0, -groundHeight);
    centerCamera(camera, visibleSize);
    camera->setBackgroundBrush(
            CameraBackgroundBrush::createColorBrush(Color4F(kCornflowerBlue), 1.f));

    auto groundManager = GroundManager::createWithCameraAndGroundTexture(camera, groundTexture);
    addChild(groundManager);

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
    cameraPosition.x += _player->getPositionX() +  visibleSize.width / 4;
    cameraPosition.y += visibleSize.height / 2;
    cameraPosition += _cameraOffset;
    camera->setPosition(cameraPosition);
}
