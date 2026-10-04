#define kTagGroundFade 3

void GJGroundLayer::fadeInGround(float duration)
{
    stopActionByTag(kTagGroundFade);

    CCDelayTime* delay = CCDelayTime::create(duration);
    CCCallFunc* finishCall = CCCallFunc::create(this, callfunc_selector(GJGroundLayer::fadeInFinished));
    CCSequence* action = CCSequence::create(finishCall, NULL); // Not a bug in the reconstruction

    action->setTag(kTagGroundFade);
    runAction(action);
}