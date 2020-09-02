//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsiclePlayer.h"

USING_NS_CC;

static constexpr float kPlayerSpeed = 200;
static constexpr float kPlayerAcceleration = 100;

PopsiclePlayer *PopsiclePlayer::createWithTexture(Texture2D *texture) {
    auto *player = new(std::nothrow) PopsiclePlayer();
    if (player && player->initWithTexture(texture)) {
        player->autorelease();
        return player;
    }

    CC_SAFE_DELETE(player);
    return nullptr;
}

bool PopsiclePlayer::initWithTexture(Texture2D *texture) {
    CCASSERT(texture, "Texture must never be null");

    if (!Sprite::initWithTexture(texture)) {
        return false;
    }

    this->setAnchorPoint(Vec2(.5f, 0.f));

    _physicsBody = PhysicsBody::createBox(getContentSize());
    _physicsBody->retain();
    _physicsBody->setVelocityLimit(kPlayerSpeed);
    addComponent(_physicsBody);

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->retain();
    _touchListener->onTouchBegan = [this](Touch *touch, Event *event) {
        log("Touch Began");
        if (!_jumping && _physicsBody) {
            _physicsBody->applyForce(Vec2(0, 2000 * _physicsBody->getMass()));
            _physicsBody->setGravityEnable(false);
            _jumping = true;
            return true;
        }
        return false;
    };
    _touchListener->onTouchEnded = [this](Touch *touch, Event *event) {
        log("Touch Ended");
        if (_jumping) {
            _jumping = false;
            if (_physicsBody) {
                _physicsBody->setGravityEnable(true);
            }
            return true;
        }
        return false;
    };

    // TODO: refactor this out
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    return true;
}

void PopsiclePlayer::update(float delta) {
    _physicsBody->applyForce(Vec2(kPlayerAcceleration * _physicsBody->getMass(), 0));
    Node::update(delta);
}

void PopsiclePlayer::cleanup() {
    CC_SAFE_RELEASE(_touchListener);
    CC_SAFE_RELEASE(_physicsBody);
    Sprite::cleanup();
}
