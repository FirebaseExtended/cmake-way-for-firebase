//
// Created by Patrick Martin on 9/1/20.
//

#ifndef PROJ_ANDROID_GROUNDMANAGER_H
#define PROJ_ANDROID_GROUNDMANAGER_H

#include "cocos2d.h"

class GroundManager : public cocos2d::Node {
public:
    static GroundManager* createWithCameraAndGroundTexture(cocos2d::Camera* camera, cocos2d::Texture2D* texture);

    virtual bool initWithCameraAndGroundTexture(cocos2d::Camera* camera, cocos2d::Texture2D* texture);

    void updateGroundTiles();

    void update(float delta) override;

    virtual void cleanup() override;

private:
    cocos2d::Sprite *createGroundTile();

    cocos2d::Camera* _camera;
    cocos2d::Texture2D* _groundTexture;

    std::vector<cocos2d::Sprite*> _groundSprites;

    float _screenWidth;
    int _tileWidth;
    int _tileCount;
};


#endif //PROJ_ANDROID_GROUNDMANAGER_H
