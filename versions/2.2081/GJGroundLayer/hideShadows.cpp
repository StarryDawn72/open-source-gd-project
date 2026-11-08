void GJGroundLayer::hideShadows()
{
    CCNode* lShadow = getChildByTag(kTagGroundShadowLeft);
    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);

    if (lShadow) lShadow->setVisible(false);
    if (rShadow) rShadow->setVisible(false);
}