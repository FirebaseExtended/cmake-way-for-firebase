//
// Created by Patrick Martin on 8/31/20.
//

#include "CupcakePancakeScene.h"

USING_NS_CC;

Scene *CupcakePancakeScene::createScene() {
    return CupcakePancakeScene::create();
}

bool CupcakePancakeScene::init() {
    auto physicsCreated = Scene::initWithPhysics();
    assert(physicsCreated);
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto pDirector = Director::getInstance();
    auto origin = pDirector->getVisibleOrigin();
    auto size = pDirector->getVisibleSize();

    auto testSprite = Sprite::create("cupcake.png");
    testSprite->setAnchorPoint(Vec2(.5f, .5f));

    testSprite->setPosition(Vec2(origin.x + size.width / 2, origin.y + size.height / 2));

    auto physicsBody = PhysicsBody::createBox(testSprite->getContentSize());
    testSprite->addComponent(physicsBody);

    this->addChild(testSprite);

    return true;
}
