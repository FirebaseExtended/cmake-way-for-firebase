//
// Created by Patrick Martin on 9/2/20.
//

#ifndef PROJ_ANDROID_CONFIG_H
#define PROJ_ANDROID_CONFIG_H

#include "cocos2d.h"

namespace Config {
    // the ground tiles are really small, scale them up this much
    constexpr float kGroundTileScale = 5.f;

    // The color of the sky - cornflower blue because I used to use XNA
    const cocos2d::Color3B kCornflowerBlue = cocos2d::Color3B(100, 149, 237);

    // where the ground is on the y axis
    constexpr float kGroundLevel = 0;

    // how many spare tiles over the minimum do you need
    // must be at least +2 (one for rounding errors, one to have one tile of buffer to avoid
    // the last one clipping out. Additional tiles act as a platform for spawned objects)
    constexpr int kGroundSpareTiles = 4;
    static_assert(kGroundSpareTiles >= 2, "Must be at least +2 to avoid visual clipping");

    // when the player jumps, how many units high they go
    constexpr float kJumpHeight = 100;

    // how long until the player reaches the peak of their jump
    constexpr float kJumpTime = .5;

    // how fast does the player go
    constexpr float kPlayerSpeed = 200;

    // how many times can the player jump in the air
    constexpr int kAirJumps = 1;

    // how fast the player rotates on death to "pop"
    constexpr int kPlayerDeathPop = 50;

    // spawn chance of an enemy appearing in its slot
    constexpr float kEnemySpawnChance = .25f;

    // how close together enemies can be (in enemy body lengths)
    constexpr float kEnemySpawnDensity = 1.f;

    // inset the collision box a small bit to make the game more fun
    constexpr float kEnemyCrabHorizontalCollisionScale = .5f;

    constexpr int kPlayerCollisionCategory = 0x01;
    constexpr int kEnemyCollisionCategory = 0x02;

    constexpr const char *kMenuFont = "fonts/Marker Felt.ttf";

    // offset of the distance label from the upper left
    const cocos2d::Vec2 kDistanceLabelOffset = cocos2d::Vec2(16, -16);

    // when drawing the distance, scale it down by some amount
    constexpr float kDistanceScale = .01f;

    // how many enemies are in a group
    static constexpr int kSpawnQueueSize = 3;

    // minimum number of enemies in a group
    static constexpr int kMinEnemiesToSpawn = 1;

    // maximum number of enemies in a group
    static constexpr int kMaxEnemiesToSpawn = 2;

    // physics variables - don't touch
    // based on the jump height and the jump time, figure out gravity and how strong a jump is
    constexpr float kGravity = -2 * kJumpHeight / (kJumpTime * kJumpTime);
    constexpr float kVelocityChangeForJump = 2 * kJumpHeight / kJumpTime;
}

#endif //PROJ_ANDROID_CONFIG_H
