void PlayerObject::updatePlayerSwingFrame(int frameNumber)
{
    int frame = MAX(1, MIN(frameNumber, 43));

    GM->loadIcon(frame, (int)IconType::Swing, m_iconRequestID);

    const char* icon1Name    = CCString::createWithFormat("swing_%02d_001.png", frame)->getCString();
    const char* icon2Name    = CCString::createWithFormat("swing_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("swing_%02d_glow_001.png", frame)->getCString();

    // So much boilerplate lol
    m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon1Name));
    m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon2Name));
    m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("swing_%02d_extra_001.png", frame)->getCString());
}