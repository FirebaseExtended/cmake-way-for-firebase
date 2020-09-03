//
// Created by Patrick Martin on 9/3/20.
//

#include "GameOverMenu.h"
#include "Config.h"
#include "PopsicleScene.h"

USING_NS_CC;

bool GameOverMenu::init() {
    auto label = Label::createWithTTF("Retry", Config::kMenuFont, 24);
    auto retryButton = MenuItemLabel::create(label, [this](Ref* sender){
        auto popsicleScene = PopsicleScene::create();
        _director->replaceScene(popsicleScene);
    });

    Vector<MenuItem*> menuItems = {retryButton};
    return Menu::initWithArray(menuItems);
}
