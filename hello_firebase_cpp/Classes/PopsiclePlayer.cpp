//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsiclePlayer.h"
#include "Config.h"

USING_NS_CC;

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
    _physicsBody->setDynamic(false);
    addComponent(_physicsBody);

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->retain();

    _touchListener->onTouchBegan = [this](Touch *touch, Event *event) {
        log("Touch Began");
        if (_jumps > 0) {
            _jumps--;
            _velocity.y = Config::kVelocityChangeForJump;
            return true;
        }
        return false;
    };

    // TODO: refactor this out
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    _velocity.x = Config::kPlayerSpeed;
    resetJumps();

    return true;
}

void PopsiclePlayer::update(float delta) {
    Vec2 acceleration;

    // first move by velocity
    setPosition(getPosition() + _velocity * delta);

    // now compute acceleration (from x')
    // apply gravity
    if (getPositionY() > 0) {
        acceleration.y += Config::kGravity;
    }

    // apply acceleration
    _velocity += acceleration * delta;

    if (getPositionY() < Config::kGroundLevel) {
        setPositionY(Config::kGroundLevel);
        resetJumps();
        _velocity.y = 0;
    }

    Node::update(delta);
}

void PopsiclePlayer::cleanup() {
    CC_SAFE_RELEASE(_touchListener);
    CC_SAFE_RELEASE(_physicsBody);
    Sprite::cleanup();
}

void PopsiclePlayer::resetJumps() {
    _jumps = Config::kAirJumps + 1;
}
