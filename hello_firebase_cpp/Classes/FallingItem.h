//
// Created by Patrick Martin on 8/31/20.
//

#ifndef PROJ_ANDROID_FALLINGITEM_H
#define PROJ_ANDROID_FALLINGITEM_H

#include "cocos2d.h"

class FallingItem : public cocos2d::Sprite {
public:
    virtual bool init() override;

    CREATE_FUNC(FallingItem);
};


#endif //PROJ_ANDROID_FALLINGITEM_H
