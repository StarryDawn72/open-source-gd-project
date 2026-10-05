#define kTagGroundShadowRight 1

void GJGroundLayer::updateShadows()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);

    if (rShadow)
        rShadow->setPosition(ccp(winSize.width / getScaleX() + 1.0f, 0.0f));
}