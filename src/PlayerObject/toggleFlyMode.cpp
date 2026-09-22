void PlayerObject::toggleFlyMode(bool enable, bool noEffects)
{
    bool& m_canJump = m_isOnGround;
    bool& m_onGround = m_isOnGround2;

    if (m_isShip == enable)
        return;

    m_isShip = enable;
    m_gameModeChangedTime = m_totalTime;
    
    if (enable)
        switchedToMode(GameObjectType::ShipPortal);
    
    stopRotation(false, 7);
    m_yVelocity *= 0.5;
    setRotation(0.0);
    m_onGround = false;
    m_canJump = false;
    m_shouldTryPlacingCheckpoint = false;
    removePendingCheckpoint();

    if (m_isShip)
    {
        stopPlatformerJumpAnimation();

        float vehicleSpriteY;
        if (m_isPlatformer)
        {
            updatePlayerJetpackFrame(GameManager::sharedState()->m_playerJetpack.value());
            m_iconSprite->setScale(0.6f);
            m_iconSprite->setPosition(ccp(6.0f, 4.0f));
            vehicleSpriteY = 0.0f;
        } else {
            updatePlayerShipFrame(GameManager::sharedState()->m_playerShip.value());
            m_iconSprite->setScale(0.55f);
            m_iconSprite->setPosition(ccp(0.0f, 5.0f));
            vehicleSpriteY = -5.0f;
        }

        m_vehicleSprite->setPosition(ccp(0.0f, vehicleSpriteY));
        m_vehicleSprite->setVisible(true);
        updatePlayerGlow();

        if (!m_isHidden)
        {
            m_trailingParticles->resetSystem();
            m_shipClickParticles->resetSystem();
        }
        m_shipClickParticles->stopSystem();
        m_hasShipParticles = false;
        
        deactivateParticle();

        if (!noEffects)
            spawnPortalCircle(ccc3(255, 0, 255), 50.0f);

        activateStreak();
        updatePlayerScale();
        
        if (m_shipStreak && !m_isPlatformer && !m_isHidden)
            m_shipStreak->setVisible(true);
    } else {
        resetPlayerIcon();
    }

    if (enable)
        modeDidChange();
}
