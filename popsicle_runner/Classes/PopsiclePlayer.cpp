// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "PopsiclePlayer.h"
#include "Config.h"

USING_NS_CC;

PopsiclePlayer *PopsiclePlayer::createWithTextureAndGameOverListener(cocos2d::Texture2D *texture,
                                                                     const std::function<void()> &onGameOver) {
    auto *player = new(std::nothrow) PopsiclePlayer();
    if (player && player->initWithTextureAndGameOverListener(texture, onGameOver)) {
        player->autorelease();
        return player;
    }

    CC_SAFE_DELETE(player);
    return nullptr;
}

bool PopsiclePlayer::initWithTextureAndGameOverListener(Texture2D *texture,
                                                        const std::function<void()> &onGameOver) {
    CCASSERT(texture, "Texture must never be null");

    if (!Sprite::initWithTexture(texture)) {
        return false;
    }

    _onGameOver = onGameOver;

    this->setAnchorPoint(Vec2(.5f, 0.f));

    // setup physics - we'll only use this for collision detection until we "ragdoll" at the end
    _physicsBody = PhysicsBody::createBox(getContentSize());
    _physicsBody->retain();
    _physicsBody->setDynamic(false);
    _physicsBody->setCategoryBitmask(Config::kPlayerCollisionCategory);
    _physicsBody->setContactTestBitmask(-1);
    addComponent(_physicsBody);

    // Listen for a player tapping on the screen
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->retain();
    _touchListener->onTouchBegan = [this](Touch *touch, Event *event) {
        if (_jumps > 0) {
            _jumps--;
            _velocity.y = Config::kVelocityChangeForJump;
            return true;
        }
        return false;
    };
    auto eventDispatcher = _director->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    // start running!
    _velocity.x = Config::kPlayerSpeed;
    resetJumps();

    return true;
}

void PopsiclePlayer::update(float delta) {
    // WARNING!!! this won't run after we collide with an enemy

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

void PopsiclePlayer::collidedWithEnemy() {
    if (!_collidedWithEnemy) {
        _collidedWithEnemy = true;
        unscheduleUpdate(); // stop running player logic
        _onGameOver();

        // we can't set dynamic to false mid physics step. So schedule it for later
        scheduleOnce([this](float) {
            _physicsBody->setDynamic(true);
            _physicsBody->setVelocity(_velocity);
            _physicsBody->setAngularVelocity(Config::kPlayerDeathPop);
        }, 0, "remove physics");
    }
}

void PopsiclePlayer::cleanup() {
    CC_SAFE_RELEASE(_touchListener);
    CC_SAFE_RELEASE(_physicsBody);
    Sprite::cleanup();
}

void PopsiclePlayer::resetJumps() {
    _jumps = Config::kAirJumps + 1;
}
