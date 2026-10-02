#define GM (GameManager::sharedState())

void PlayerObject::toggleSwingMode(bool enable, bool noEffects)
{
    bool& m_canJump = m_isOnGround;
    bool& m_onGround = m_isOnGround2;

    if (m_isSwing == enable)
        return;

    m_isSwing = enable;
    m_gameModeChangedTime = m_totalTime;

    if (enable)
        switchedToMode(GameObjectType::SwingPortal);

    stopRotation(false, 9);
    setRotation(0);

    m_yVelocity *= 0.5;

    m_onGround = false;
    m_canJump = false;

    m_shouldTryPlacingCheckpoint = false;

    removePendingCheckpoint();

    if (m_isSwing)
    {
        updatePlayerSwingFrame(GM->m_playerSwing.value());

        if (!noEffects)
            spawnPortalCircle(ccc3(255, 200, 0), 50.0f);

        if (!m_isHidden)
        {
            m_trailingParticles->resetSystem();
            m_shipClickParticles->resetSystem();
        }

        m_shipClickParticles->stopSystem();
        m_hasShipParticles = false;

        deactivateParticle();
        activateStreak();

        m_swingFireMiddle->setVisible(true);
        m_swingFireMiddle->loopFireAnimation();
        m_swingFireBottom->setScale(0.01f);
        m_swingFireTop->setScale(0.01f);
        m_swingFireBottom->setVisible(true);
        m_swingFireTop->setVisible(true);

        m_swingBurstParticles1->resetSystem();
        m_swingBurstParticles2->resetSystem();
        m_swingBurstParticles1->stopSystem();
        m_swingBurstParticles2->stopSystem();

        updateSwingFire();
    } else {
        resetPlayerIcon();
        updatePlayerFrame(m_maybeSavedPlayerFrame);
        setRotation(m_isUpsideDown ? 180.0f : 0.0f);
        disableSwingFire();
    }

    if (enable)
        modeDidChange();
}