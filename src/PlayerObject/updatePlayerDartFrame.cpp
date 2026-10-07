void PlayerObject::updatePlayerDartFrame(int frameNumber)
{
    int frame = MAX(1, MIN(frameNumber, 96));

    GM->loadIcon(frame, (int)IconType::Wave, m_iconRequestID);

    const char* icon1Name    = CCString::createWithFormat("dart_%02d_001.png", frame)->getCString();
    const char* icon2Name    = CCString::createWithFormat("dart_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("dart_%02d_glow_001.png", frame)->getCString();

    m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon1Name));
    m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon2Name));
    m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("dart_%02d_extra_001.png", frame)->getCString());
}