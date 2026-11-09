void PlayerFireBoostSprite::animateFireIn()
{
    stopAllActions();

    CCSequence* animateSequence = CCSequence::create(
        CCScaleTo::create(0.06f, m_size * 0.6f, m_size * 1.5f),
        CCCallFunc::create(this, callfunc_selector(PlayerFireBoostSprite::loopFireAnimation)),
        NULL
    );

    runAction(animateSequence);
}