//
// Created by Patrick Martin on 9/1/20.
//

#ifndef PROJ_ANDROID_POPSICLESCENE_H
#define PROJ_ANDROID_POPSICLESCENE_H

#include "cocos2d.h"

class PopsicleScene: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(PopsicleScene);
private:
};


#endif //PROJ_ANDROID_POPSICLESCENE_H
