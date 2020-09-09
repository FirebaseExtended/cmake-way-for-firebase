// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
