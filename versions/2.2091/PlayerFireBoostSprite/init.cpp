bool PlayerFireBoostSprite::init()
{
    if (!CCSprite::initWithFile("fireBoost_001.png")) {
        return false;
    }

    setAnchorPoint(ccp(0.5f, 1.0f));
    return true;
}