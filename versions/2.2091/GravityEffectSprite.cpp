#include "GravityEffectSprite.h"

USING_NS_CC;

#define kTagGravityEffectBatch 1

void GravityEffectSprite::draw()
{
}

void GravityEffectSprite::updateSpritesColor(ccColor3B color)
{
    CCNode* batchNode = getChildByTag(kTagGravityEffectBatch);

    if (batchNode) {
        CCArray* sprites = batchNode->getChildren();

        for (int i = 0; i < sprites->count(); i++) {
            ((CCSprite*)sprites->objectAtIndex(i))->setColor(color);
        }
    }
}

bool GravityEffectSprite::init()
{
    if (!CCSprite::init()) {
        return false;
    }

    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("gravityLine_001.png", 22);

    batch->setTag(kTagGravityEffectBatch);
    addChild(batch);
    batch->setBlendFunc({GL_SRC_ALPHA, GL_ONE});

    float contentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
    float baseScaleX = (contentScaleFactor * 480.0f) / CCDirector::sharedDirector()->getScreenRight();
    float spacing = (CCDirector::sharedDirector()->getScreenRight() - 60.0f) / 22.0f;

    for (int i = 0; i < 22; i++) {
        CCSprite* line = CCSprite::create("gravityLine_001.png");
        batch->addChild(line);

        float x = (30.0f - (CCDirector::sharedDirector()->getScreenRight() * 0.5f)) + (i * spacing) + (CCRANDOM_0_1() * spacing);
        float y = (CCRANDOM_0_1() + CCRANDOM_0_1() - 1.0f) * 10.0f;     // Y pos range [-10, 10]

        line->setPosition(ccp(x, y));
        line->setScaleX(((CCRANDOM_0_1() * 4.0f) + 2.0f) * baseScaleX); // random range [2, 6]
        line->setScaleY((CCRANDOM_0_1() + 2.0f) * contentScaleFactor);  // random range [2, 3]
        line->setOpacity((CCRANDOM_0_1() * 130.0f) + 50.0f);            // opacity range [50, 180]
    }

    return true;
}