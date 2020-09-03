/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LoginScene.h"

#include "Config.h"
#include "PopsicleScene.h"

USING_NS_CC;

Scene *LoginScene::createScene() {
    return LoginScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoginScene::init() {
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Signing In...", Config::kMenuFont, 24);
    if (label == nullptr) {
        problemLoading(Config::kMenuFont);
    } else {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "LoginScene" splash screen"
    auto sprite = Sprite::create("sparky.png");
    if (sprite == nullptr) {
        problemLoading("'sparky.png'");
    } else {
        // position the sprite on the center of the screen
        sprite->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    auto app = firebase::App::GetInstance();
    auto auth = firebase::auth::Auth::GetAuth(app);
    auth->SignInAnonymously().OnCompletion(
            [label](const firebase::Future<firebase::auth::User *> &result) {
                std::stringstream message;
                auto error = result.error_message();
                if (strlen(error)) {
                    message << "Failed to sign in because " << error;
                } else {
                    firebase::auth::User *pUser = *result.result();
                    message << "Signed in as " << pUser->uid();
                }
                std::string messageStr = message.str();
                Director::getInstance()->getScheduler()->performFunctionInCocosThread(
                        [label, messageStr]() {
                            label->setString(messageStr);
                        });
            });

    auto continueButton = ui::Button::create("button.png", "button_pressed.png",
                                             "button_disabled.png");
    continueButton->setTitleFontName(Config::kMenuFont);
    continueButton->setTitleText("Continue");
    continueButton->setAnchorPoint(Vec2(.5f, 0.f));
    continueButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y));
    continueButton->addClickEventListener(CC_CALLBACK_0(LoginScene::continueClicked, this));
    this->addChild(continueButton, 0);

    return true;
}

void LoginScene::continueClicked() {
    _director->pushScene(PopsicleScene::createScene());
}
