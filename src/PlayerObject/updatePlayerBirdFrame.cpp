#define kMaxBirdFrame 149
#define GM GameManager::sharedState()

void PlayerObject::updatePlayerBirdFrame(int frameNumber)
{
    int frame = MIN(MAX(frameNumber, 1), kMaxBirdFrame);

    GM->loadIcon(frame, (int)IconType::Ufo, m_iconRequestID);

    const char* primaryName   = CCString::createWithFormat("bird_%02d_001.png", frame)->getCString();
    const char* secondaryName = CCString::createWithFormat("bird_%02d_2_001.png", frame)->getCString();
    const char* tertiaryName  = CCString::createWithFormat("bird_%02d_3_001.png", frame)->getCString();
    const char* iconGlowName  = CCString::createWithFormat("bird_%02d_glow_001.png", frame)->getCString();

    m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(primaryName));
    m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(secondaryName));
    m_birdVehicle->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tertiaryName));
    m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("bird_%02d_extra_001.png", frame)->getCString());
}
