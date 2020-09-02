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

    constexpr int kPlayerCollisionCategory = 0x01;
    constexpr int kEnemyCollisionCategory = 0x02;

    // physics variables - don't touch
    // based on the jump height and the jump time, figure out gravity and how strong a jump is
    constexpr float kGravity = -2 * kJumpHeight / (kJumpTime * kJumpTime);
    constexpr float kVelocityChangeForJump = 2 * kJumpHeight / kJumpTime;
}

#endif //PROJ_ANDROID_CONFIG_H
