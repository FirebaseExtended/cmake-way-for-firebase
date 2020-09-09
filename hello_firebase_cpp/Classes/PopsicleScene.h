/*
 * Copyright 2020 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PROJ_ANDROID_POPSICLESCENE_H
#define PROJ_ANDROID_POPSICLESCENE_H

//#define DEBUG_PHYSICS

#include "cocos2d.h"
#include "PopsiclePlayer.h"

class PopsicleScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init() override;

    void onEnter() override;

    void update(float delta) override;

    void cleanup() override;

    CREATE_FUNC(PopsicleScene);
private:
    void centerCamera(cocos2d::Camera *camera, const cocos2d::Size &visibleSize);

    bool handleCollision(cocos2d::PhysicsContact &contact);

    void gameOver();

    void updateDistanceLabel();

    PopsiclePlayer *_player = nullptr;
    cocos2d::Vec2 _cameraOffset;
    cocos2d::Node *_cameraNode = nullptr;
    cocos2d::EventListenerPhysicsContact *_physicsEventListener = nullptr;
    cocos2d::Label *_distanceLabel = nullptr;
    float _cameraStartDistance;
    float _lastDistance = 0;

    bool _gameOver = false;
};


#endif //PROJ_ANDROID_POPSICLESCENE_H
