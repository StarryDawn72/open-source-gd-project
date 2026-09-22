void PlayerObject::toggleBirdMode(bool enable, bool noEffects)
{
    bool& m_canJump = m_isOnGround;
    bool& m_onGround = m_isOnGround2;

    if (m_isBird == enable)
        return;

    m_isBird = enable;
    m_gameModeChangedTime = m_totalTime;
    if (enable)
        switchedToMode(GameObjectType::UfoPortal);

    stopRotation(false, 8);
    m_yVelocity *= 0.5;
    setRotation(0);
    m_onGround = false;
    m_canJump = false;
    m_shouldTryPlacingCheckpoint = false;
    removePendingCheckpoint();

    if (m_isBird)
    {
        updatePlayerBirdFrame(GameManager::sharedState()->m_playerBird.value());
        stopPlatformerJumpAnimation();
        
        m_iconSprite->setScale(0.55f);
        m_iconSprite->setPosition(ccp(0.0f, 5.0f));

        m_vehicleSprite->setVisible(true);
        m_vehicleSprite->setPosition(ccp(0.0f, -7.0f));

        updatePlayerGlow();
        
        ccColor4F color = ccc4FFromccc3B(m_playerColor2);
        m_trailingParticles->setStartColor(color);
        m_trailingParticles->setEndColor(color);

        if (!m_isHidden)
            m_trailingParticles->resetSystem();
        deactivateParticle();

        if (!noEffects)
            spawnPortalCircle(ccc3(255, 200, 0), 50.0f);

        activateStreak();
        updatePlayerScale();
        m_birdVehicle->setVisible(true);
    } else {
        resetPlayerIcon();
    }

    if (enable)
        modeDidChange();
}
