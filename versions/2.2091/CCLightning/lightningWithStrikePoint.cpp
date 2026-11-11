CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration)
{
    CCLightning* ret = new CCLightning();

    if (ret->initWithStrikePoint(strikePoint1, strikePoint2, duration)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return NULL;
    }
}

CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint)
{
    CCLightning* ret = new CCLightning();

    if (ret->initWithStrikePoint(strikePoint)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return NULL;
    }
}