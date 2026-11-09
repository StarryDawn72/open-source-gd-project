void PlayerFireBoostSprite::animateFireOut()
{
    stopAllActions();
    runAction(CCScaleTo::create(0.4f, 0.01f, 0.01f));
}