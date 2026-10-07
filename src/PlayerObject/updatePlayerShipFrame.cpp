#define kMaxShipFrame 169

void PlayerObject::updatePlayerShipFrame(int frameNumber)
{
    int frame = MIN(MAX(frameNumber, 1), kMaxShipFrame);

    GM->loadIcon(frame, (int)IconType::Ship, m_iconRequestID);

    const char* primaryName   = CCString::createWithFormat("ship_%02d_001.png", frame)->getCString();
    const char* secondaryName = CCString::createWithFormat("ship_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName  = CCString::createWithFormat("ship_%02d_glow_001.png", frame)->getCString();

    m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(primaryName));
    m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(secondaryName));
    m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("ship_%02d_extra_001.png", frame)->getCString());
}
