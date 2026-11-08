void PlayerObject::resetPlayerIcon()
{
    stopPlatformerJumpAnimation();
    m_width = 30.0f;
    m_height = 30.0f;
    m_unkAngle1 = 30.0f; // TODO: rename!!!
    
    runRotateAction(false, 5);

    m_iconSprite->setScale(1.0f);
    m_iconSprite->setPosition(CCPointZero);
    m_vehicleSprite->setVisible(false);
    m_birdVehicle->setVisible(false);

    updatePlayerGlow();

    m_trailingParticles->stopSystem();
    m_shipClickParticles->stopSystem();
    m_vehicleGroundParticles->stopSystem();

    m_trailingParticles->setStartColor(ccc4f(1.0f, 0.39215687f, 0.0f, 1.0f));
    m_trailingParticles->setEndColor(ccc4f(1.0f, 0.0f, 0.0f, 1.0f));

    if (m_disableStreakTint)
        m_regularTrail->setColor(ccWHITE);
    else
        m_regularTrail->setColor(m_playerColor2);

    deactivateStreak(false);
    if (m_shipStreak)
        m_shipStreak->setVisible(false);

    updatePlayerScale();
}
