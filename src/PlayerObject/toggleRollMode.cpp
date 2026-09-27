void PlayerObject::toggleRollMode(bool enable, bool noEffects) {
    if (m_isBall == enable)
        return;

    m_isBall = enable;
    m_gameModeChangedTime = m_totalTime;
    if (enable)
    {
        switchedToMode(GameObjectType::BallPortal);
        if (m_isBall)
        {
            if (m_vehicleSize != 1.0 && m_defaultMiniIcon)
                updatePlayerRollFrame(0);
            else
                updatePlayerRollFrame(GameManager::sharedState()->m_playerBall.value());

            if (!noEffects)
                spawnPortalCircle({255, 50, 50}, 50.0f);

            stopRotation(true, 11);
        }
    } else {
        if (m_vehicleSize != 1.0 && m_defaultMiniIcon)
            updatePlayerFrame(0);
        else
            updatePlayerFrame(m_maybeSavedPlayerFrame);

        setRotation(m_isUpsideDown ? 180.0f : 0.0f);
        stopRotation(true, 11);
    }

    if (enable)
        modeDidChange();
}