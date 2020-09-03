//
// Created by Patrick Martin on 9/1/20.
//

#include "GroundManager.h"
#include "Config.h"

USING_NS_CC;

GroundManager *GroundManager::createWithCameraAndGroundTexture(cocos2d::Camera *camera,
                                                               cocos2d::Texture2D *texture) {
    auto *groundManager = new(std::nothrow) GroundManager();
    if (groundManager && groundManager->initWithCameraAndGroundTexture(camera, texture)) {
        return groundManager;
    }

    CC_SAFE_DELETE(groundManager);
    return nullptr;
}

bool GroundManager::initWithCameraAndGroundTexture(cocos2d::Camera *camera,
                                                   cocos2d::Texture2D *texture) {
    CCASSERT(camera, "GroundManager must be initialized with a camera");
    CCASSERT(texture, "GroundManager must be initialized with a ground texture");

    _camera = camera;
    _camera->retain();

    _groundTexture = texture;
    _groundTexture->retain();

    auto visibleSize = _director->getVisibleSize();
    _screenWidth = visibleSize.width;
    _tileWidth = int(_groundTexture->getContentSize().width * Config::kGroundTileScale);
    _tileCount = (int(_screenWidth) / _tileWidth) + Config::kGroundSpareTiles;

    _groundSprites.reserve(_tileCount);
    for (int i = 0; i < _tileCount; i++) {
        auto sprite = createGroundTile();
        sprite->retain();
        addChild(sprite);
        _groundSprites.push_back(sprite);
    }

    updateGroundTiles();

    scheduleUpdate();
    return true;
}

/*
 * Reusing the available tiles, this function places them on screen in such a way that it mimics an
 * infinite scrolling plane even though it's recycling a number of fixed tiles.
 */
void GroundManager::updateGroundTiles() {
    // cocos doesn't appear to cache the world transform, so this is a redundant calculation
    auto worldPosition = _camera->convertToWorldSpaceAR(Vec2::ZERO);
    float startPosition = worldPosition.x - (_screenWidth / 2);
    startPosition += _tileWidth / 2;

    // find the start tile
    int tile = int(startPosition) / _tileCount;

    // find the start offset
    int offset = int(startPosition) % _tileWidth;
    if (offset < 0) {
        offset += _tileWidth;
    }
    float tilePosition = startPosition - float(offset);

    // this can be faster without the mod
    for (int i = 0;
         i < _tileCount; i++, tile = (tile + 1) % _tileCount, tilePosition += _tileWidth) {
        _groundSprites[i]->setPosition(Vec2(tilePosition, 0));
    }
}

void GroundManager::update(float delta) {
    updateGroundTiles();
    Node::update(delta);
}

float GroundManager::getGroundHeight() const {
    return _groundTexture->getContentSize().height * Config::kGroundTileScale;
}

void GroundManager::cleanup() {
    CC_SAFE_RELEASE(_camera);
    CC_SAFE_RELEASE(_groundTexture);

    for (Sprite *groundSprite : _groundSprites) {
        CC_SAFE_RELEASE(groundSprite);
    }
    _groundSprites.clear();
    Node::cleanup();
}

Sprite *GroundManager::createGroundTile() {
    auto groundTile = Sprite::createWithTexture(_groundTexture);
    groundTile->setAnchorPoint(Vec2(.5f, 1.f));
    groundTile->setPosition(Vec2(0, 0));
    groundTile->setScale(5.f);

    auto groundPhysics = PhysicsBody::createBox(groundTile->getContentSize());
    groundPhysics->setDynamic(false);
    groundTile->addComponent(groundPhysics);
    return groundTile;
}
