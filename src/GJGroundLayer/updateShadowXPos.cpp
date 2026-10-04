#define kTagGroundShadowLeft 0
#define kTagGroundShadowRight 1

void GJGroundLayer::updateShadowXPos(float leftX, float rightX)
{

    float scaleX = getScaleX(); // Presumably a leftover from the source code,
                                // result is unused

    CCNode* lShadow = getChildByTag(kTagGroundShadowLeft);
    if (lShadow)
        lShadow->setPosition(ccp(leftX - 1.0f, 0.0f));

    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);
    if (rShadow)
        rShadow->setPosition(ccp(rightX + 1.0f, 0.0f));
}