//
// Created by Patrick Martin on 9/1/20.
//

#ifndef PROJ_ANDROID_POPSICLEPLAYER_H
#define PROJ_ANDROID_POPSICLEPLAYER_H

#include "cocos2d.h"

class PopsiclePlayer : public cocos2d::Sprite {
public:
    static PopsiclePlayer *createWithTexture(cocos2d::Texture2D *texture);

    virtual bool initWithTexture(cocos2d::Texture2D *texture) override;

    void update(float delta) override;

    virtual void cleanup() override;

private:
    cocos2d::EventListenerTouchOneByOne* _touchListener = nullptr;
    cocos2d::PhysicsBody* _physicsBody = nullptr;

    bool _jumping = false;
    cocos2d::Vec2 _velocity;
};


#endif //PROJ_ANDROID_POPSICLEPLAYER_H
