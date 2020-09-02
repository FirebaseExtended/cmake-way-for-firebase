//
// Created by Patrick Martin on 9/1/20.
//

#ifndef PROJ_ANDROID_POPSICLESCENE_H
#define PROJ_ANDROID_POPSICLESCENE_H

//#define DEBUG_PHYSICS

#include "cocos2d.h"
#include "PopsiclePlayer.h"

class PopsicleScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init() override;

    void update(float delta) override;

    void cleanup() override;

    CREATE_FUNC(PopsicleScene);
private:
    void centerCamera(cocos2d::Camera *camera, const cocos2d::Size &visibleSize);

    PopsiclePlayer *_player = nullptr;
    cocos2d::Vec2 _cameraOffset;
    cocos2d::Node *_cameraNode = nullptr;
};


#endif //PROJ_ANDROID_POPSICLESCENE_H
