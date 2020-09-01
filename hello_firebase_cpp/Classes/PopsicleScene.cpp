//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsicleScene.h"

USING_NS_CC;

static const Color3B kCornflowerBlue = Color3B(100, 149, 237);

cocos2d::Scene *PopsicleScene::createScene() {
    return PopsicleScene::create();
}

bool PopsicleScene::init() {
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();

    auto textureCache = director->getTextureCache();
    auto playerTexture = textureCache->addImage("purple.png");

    auto popsicle = Sprite::createWithTexture(playerTexture);
    popsicle->setAnchorPoint(Vec2(.5f, 0.f));
    popsicle->setPosition(Vec2(0.f, 0.f));
    this->addChild(popsicle);

    auto groundTexture = textureCache->addImage("grass-middle.png");

    auto groundTile = Sprite::createWithTexture(groundTexture);
    groundTile->setAnchorPoint(Vec2(.5f, 1.f));
    groundTile->setPosition(Vec2(0, 0));
    groundTile->setScale(5.f);
    this->addChild(groundTile);

    float groundHeight = groundTile->getContentSize().height * groundTile->getScale();

    auto camera = this->getDefaultCamera();
    Vec2 cameraPosition = popsicle->getPosition();
    cameraPosition.x += visibleSize.width / 4;
    cameraPosition.y += visibleSize.height / 2 - groundHeight;
    camera->setPosition(cameraPosition);
    camera->setBackgroundBrush(CameraBackgroundBrush::createColorBrush(Color4F(kCornflowerBlue), 1.f));

    return true;
}
