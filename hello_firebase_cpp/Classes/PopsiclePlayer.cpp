//
// Created by Patrick Martin on 9/1/20.
//

#include "PopsiclePlayer.h"

USING_NS_CC;

PopsiclePlayer *PopsiclePlayer::createWithTexture(Texture2D *texture) {
    auto *player = new (std::nothrow) PopsiclePlayer();
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

    auto physicsBody = PhysicsBody::createBox(getContentSize());
    addComponent(physicsBody);

    return true;
}
