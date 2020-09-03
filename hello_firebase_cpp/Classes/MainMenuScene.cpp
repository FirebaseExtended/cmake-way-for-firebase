//
// Created by Patrick Martin on 9/3/20.
//

#include "MainMenuScene.h"
#include "Config.h"
#include "PopsicleScene.h"

USING_NS_CC;

MainMenuScene *MainMenuScene::createScene() {
    return MainMenuScene::create();
}

bool MainMenuScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto startGameLabel = Label::createWithTTF("Start Game", Config::kMenuFont, 24);
    auto startGameButton = MenuItemLabel::create(startGameLabel, [this](Ref *) {
        _director->replaceScene(PopsicleScene::createScene());
    });
    auto mainMenu = Menu::create(startGameButton, NULL);
    addChild(mainMenu);

    return true;
}
