/*
    Used to make the wave trail fade out when reversing or
    changing gameplay orientation.
*/
void PlayerObject::createFadeOutDartStreak()
{
    HardStreak* fadeOutStreak = m_waveTrail->createDuplicate();
    m_waveTrail->getParent()->addChild(fadeOutStreak, m_waveTrail->getZOrder());

    fadeOutStreak->setPosition(m_waveTrail->getPosition());
    fadeOutStreak->resumeStroke();
    fadeOutStreak->scheduleAutoUpdate();

    CCFadeTo* fade = CCFadeTo::create(0.5f, 0);
    CCCallFunc* remove = CCCallFunc::create(fadeOutStreak, callfunc_selector(CCNode::removeMeAndCleanup));
    CCSequence* fadeSequence = CCSequence::create(fade, remove, NULL);

    fadeOutStreak->runAction(fadeSequence);
}