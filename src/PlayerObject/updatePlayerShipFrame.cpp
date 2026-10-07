void PlayerObject::updatePlayerShipFrame(int frameNumber)
{
    int frame = MAX(1, MIN(frameNumber, 169));

    GM->loadIcon(frame, (int)IconType::Ship, m_iconRequestID);

    const char* icon1Name    = CCString::createWithFormat("ship_%02d_001.png", frame)->getCString();
    const char* icon2Name    = CCString::createWithFormat("ship_%02d_2_001.png", frame)->getCString();
    const char* iconGlowName = CCString::createWithFormat("ship_%02d_glow_001.png", frame)->getCString();

    m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon1Name));
    m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon2Name));
    m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iconGlowName));

    m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->getContentSize() * 0.5f);

    updatePlayerSpriteExtra(CCString::createWithFormat("ship_%02d_extra_001.png", frame)->getCString());
}