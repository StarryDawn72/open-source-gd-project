void PlayerObject::updatePlayerBirdFrame(int frameNumber)
{
    int frame = MAX(1, MIN(frameNumber, 149));

    GM->loadIcon(frame, (int)IconType::Ufo, m_iconRequestID);

    const char* icon1Name    = CCString::createWithFormat("bird_%02d_001.png", frame)->getCString();
    const char* icon2Name    = CCString::createWithFormat("bird_%02d_2_001.png", frame)->getCString();
    const char* icon3Name    = CCString::createWithFormat("bird_%02d_3_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("bird_%02d_glow_001.png", frame)->getCString();

    m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon1Name));
    m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon2Name));
    m_birdVehicle->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon3Name));
    m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("bird_%02d_extra_001.png", frame)->getCString());
}