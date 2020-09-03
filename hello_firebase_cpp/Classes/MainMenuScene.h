//
// Created by Patrick Martin on 9/3/20.
//

#ifndef PROJ_ANDROID_MAINMENUSCENE_H
#define PROJ_ANDROID_MAINMENUSCENE_H

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
    static MainMenuScene* createScene();

    bool init() override;

    CREATE_FUNC(MainMenuScene);
private:
};


#endif //PROJ_ANDROID_MAINMENUSCENE_H
