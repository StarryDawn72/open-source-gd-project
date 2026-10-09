void PlayerObject::rotateGameplay(int moveDirection, int groundDirection, bool editVelocity, float velocityModX, float velocityModY, bool overrideVelocity, bool dontSlide)
{
    bool wasUpsideDown = m_isUpsideDown;
    bool wasSideways   = m_isSideways;
    bool wasGoingLeft  = m_isGoingLeft;

    m_isSideways = moveDirection >= 3 && moveDirection <= 4;
    flipGravity(moveDirection == 4 || moveDirection == 1, true);

    if (m_isPlatformer)
        doReversePlayer(m_isGoingLeft);
    else
        doReversePlayer(groundDirection >= 2 && groundDirection <= 3);

    updatePlayerArt();

    if (m_isSideways != wasSideways) {
        if (m_isGoingLeft == wasGoingLeft && m_isDart) {
            createFadeOutDartStreak();
            if (m_fadeOutStreak) {
                m_waveTrail->reset();
                placeStreakPoint();
            }
        }

        if (m_vehicleGroundParticles->isActive())
            m_vehicleGroundParticles->resetSystem();
        
        resetCollisionLog(true);
        
        CCPoint velocity = ccp(getCurrentXVelocity(), m_yVelocity);

        if (editVelocity) {
            if (!overrideVelocity) {
                velocityModX *= velocity.x;
                velocityModY *= velocity.y;
            }
            velocity.x = velocityModX;
            velocity.y = velocityModY;
        } else
            CC_SWAP(velocity.x, velocity.y, float);

        updatePlayerForce(velocity, false);
        m_maybeIsBoosted = true;
        playerTeleported();

        if (dontSlide)
            handlePlayerCommand(kPlayerCommandStopSlide);

        if (isInNormalMode() && !m_isRotating)
            runRotateAction(false, 4);

        if (m_isDashing)
            CC_SWAP(m_dashX, m_dashY, float);
    }

    if (m_isDashing && (m_isUpsideDown != wasUpsideDown || m_isSideways != wasSideways || m_isGoingLeft != wasGoingLeft)) {
        if (m_isGoingLeft != wasGoingLeft) {
            if (m_isSideways != wasSideways)
                m_dashAngle += 180.0f;

            if (m_dashAngle <= 0.0f)
                m_dashAngle = -180.0f - m_dashAngle;
            else
                m_dashAngle = 180.0f - m_dashAngle;
        }

        if (m_dashAngle > 180.0f)
            m_dashAngle -= 360.0f;
        else if (m_dashAngle < -180.0f)
            m_dashAngle += 360.0f;

        updateDashArt();
    }
}