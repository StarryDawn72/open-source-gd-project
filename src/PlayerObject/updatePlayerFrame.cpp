#define kMaxPlayerFrame 485

void PlayerObject::updatePlayerFrame(int frameNumber)
{
    int frame = 0;
    if (frameNumber >= 0) {
        frame = MIN(frameNumber, kMaxPlayerFrame);
        m_maybeSavedPlayerFrame = frame; // TODO: find name
    }

    GM->loadIcon(frame, (int)IconType::Cube, m_iconRequestID);

    const char* primaryName    = CCString::createWithFormat("player_%02d_001.png", frame)->getCString();
    const char* secondaryName    = CCString::createWithFormat("player_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("player_%02d_glow_001.png", frame)->getCString();

    m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(primaryName));
    m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(secondaryName));
    m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("player_%02d_extra_001.png", frame)->getCString());
}
