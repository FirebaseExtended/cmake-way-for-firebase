//
// Created by Patrick Martin on 9/3/20.
//

#ifndef PROJ_ANDROID_GAMEOVERMENU_H
#define PROJ_ANDROID_GAMEOVERMENU_H

#include "cocos2d.h"

class GameOverMenu : public cocos2d::Menu {
public:
    bool init() override;

    CREATE_FUNC(GameOverMenu);
private:
};


#endif //PROJ_ANDROID_GAMEOVERMENU_H
