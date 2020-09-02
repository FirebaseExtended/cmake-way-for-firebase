//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsiclePlayer.h"

USING_NS_CC;

static constexpr float kGroundLevel = 0;
static constexpr float kJumpHeight = 100;
static constexpr float kJumpTime = .5;
static constexpr float kGravity = -2 * kJumpHeight / (kJumpTime * kJumpTime);
static constexpr float kVelocityChangeForJump = 2 * kJumpHeight / kJumpTime;
static constexpr float kPlayerSpeed = 200;
static constexpr int kAirJumps = 1;

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
            _velocity.y = kVelocityChangeForJump;
            return true;
        }
        return false;
    };

    // TODO: refactor this out
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    _velocity.x = kPlayerSpeed;
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
        acceleration.y += kGravity;
    }

    // apply acceleration
    _velocity += acceleration * delta;

    if (getPositionY() < kGroundLevel) {
        setPositionY(kGroundLevel);
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
    _jumps = kAirJumps + 1;
}
