void PlayerObject::toggleDartMode(bool enable, bool noEffects) {
    bool& m_canJump = m_isOnGround;
    bool& m_onGround = m_isOnGround2;

    if (m_isDart == enable)
        return;

    m_isDart = enable;
    m_gameModeChangedTime = m_totalTime;

    if (enable)
        switchedToMode(GameObjectType::WavePortal);

    stopRotation(false, 10);

    m_yVelocity *= 0.5;
    setRotation(0.0f);
    m_onGround = false;
    m_canJump = false;
    m_shouldTryPlacingCheckpoint = false;
    removePendingCheckpoint();

    if (m_isDart)
    {
        m_width = 10.0f;
        m_height = 10.0f;
        m_unkAngle1 = 20.0f;
        
        updatePlayerDartFrame(GameManager::sharedState()->m_playerDart.value());

        if (!noEffects)
            spawnPortalCircle({255, 200, 0}, 50.0f);

        activateStreak();
        updatePlayerScale();
        deactivateParticle();

        if (m_maybeIsVehicleGlowing)
            m_regularTrail->setColor(ccBLACK);
        else
            m_regularTrail->setColor(ccWHITE);

        m_waveTrail->reset();
        placeStreakPoint();

        if (
            m_playEffects &&
            !m_maybeReducedEffects &&
            !GameManager::get()->m_playLayer->m_skipArtReload &&
            !noEffects
        ) {
            auto circleWave = CCCircleWave::create(10.0f, 60.0f, 0.4f, false);
            circleWave->m_color = m_playerColor1;
            circleWave->setPosition(m_lastPortalPos);
            circleWave->m_circleMode = CircleMode::Outline;
            circleWave->m_lineWidth = 4;
            m_parentLayer->addChild(circleWave, 0);
        }
    } else {
        if (m_vehicleSize != 1.0 && m_defaultMiniIcon)
            updatePlayerFrame(0);
        else
            updatePlayerFrame(m_maybeSavedPlayerFrame);
        resetPlayerIcon();
    }

    m_regularTrail->setStroke(m_streakStrokeWidth * m_vehicleSize * (m_isDart ? 0.8f : 1.0f));
    if (enable)
        modeDidChange();
}