#define kMaxSwingFrame 43

void PlayerObject::updatePlayerSwingFrame(int frameNumber)
{
    int frame = MIN(MAX(frameNumber, 1), kMaxSwingFrame);

    GM->loadIcon(frame, (int)IconType::Swing, m_iconRequestID);

    const char* primaryName   = CCString::createWithFormat("swing_%02d_001.png", frame)->getCString();
    const char* secondaryName = CCString::createWithFormat("swing_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName  = CCString::createWithFormat("swing_%02d_glow_001.png", frame)->getCString();

    m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(primaryName));
    m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(secondaryName));
    m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("swing_%02d_extra_001.png", frame)->getCString());
}
