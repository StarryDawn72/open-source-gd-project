#pragma once

#include "cocos2d.h"

class GravityEffectSprite : public cocos2d::CCSprite {
public:
    virtual void draw();
    CREATE_FUNC(GravityEffectSprite)
    void updateSpritesColor(cocos2d::ccColor3B color);
    virtual bool init();
};