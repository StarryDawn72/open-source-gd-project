void PlayerFireBoostSprite::loopFireAnimation()
{
    stopAllActions();
    
    // m_size is 1.0f by default
    CCSequence* animation = CCSequence::create(
        CCScaleTo::create(0.06f, m_size * 1.2f, m_size),
        CCScaleTo::create(0.06f, m_size * 0.6f, m_size * 1.5f),
        NULL
    );

    runAction(CCRepeatForever::create(animation));
}