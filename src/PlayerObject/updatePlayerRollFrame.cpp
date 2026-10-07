void PlayerObject::updatePlayerRollFrame(int frameNumber)
{
    int frame = 0;
    if (frameNumber >= 0) {
        frame = MIN(frameNumber, 118);
        m_maybeSavedPlayerFrame = frame;
    }

    GM->loadIcon(frame, (int)IconType::Ball, m_iconRequestID);

    const char* icon1Name    = CCString::createWithFormat("player_ball_%02d_001.png", frame)->getCString();
    const char* icon2Name    = CCString::createWithFormat("player_ball_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("player_ball_%02d_glow_001.png", frame)->getCString();

    m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon1Name));
    m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon2Name));
    m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("player_ball_%02d_extra_001.png", frame)->getCString());
}