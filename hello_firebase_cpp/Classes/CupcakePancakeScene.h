//
// Created by Patrick Martin on 8/31/20.
//

#ifndef PROJ_ANDROID_CUPCAKEPANCAKESCENE_H
#define PROJ_ANDROID_CUPCAKEPANCAKESCENE_H

#include "cocos2d.h"

class CupcakePancakeScene: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(CupcakePancakeScene);
};


#endif //PROJ_ANDROID_CUPCAKEPANCAKESCENE_H
