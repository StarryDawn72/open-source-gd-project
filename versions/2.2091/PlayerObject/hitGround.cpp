void PlayerObject::hitGround(GameObject* object, bool noParticle)
{
    m_groundObjectMaterial = object ? object->m_objectMaterial : 0;
    m_isOnIce = false;

    double relativeYVelocity = m_yVelocity * flipMod();

    if (m_gameLayer && !m_isDart) {

        // trigger game events based on landing force

        if      (playerIsFalling(-14.0f)) gameEventTriggered((int)GJGameEvent::HardLanding, m_groundObjectMaterial);
        else if (playerIsFalling(-8.0f))  gameEventTriggered((int)GJGameEvent::NormalLanding, m_groundObjectMaterial);
        else if (playerIsFalling(-4.0f))  gameEventTriggered((int)GJGameEvent::SoftLanding, m_groundObjectMaterial);
        else if (playerIsFalling(-1.0f)) {
            GJGameEvent event = m_onGround ? GJGameEvent::TinyLanding : GJGameEvent::FeatherLanding;
            gameEventTriggered(int(event), m_groundObjectMaterial);
        }

        if (m_fallStartY != 0.0f) {
            
            float fallDistance = fabsf(m_fallStartY - getPosition().y);
            if (fallDistance > 0.0f) {

                if      (fallDistance > 450.0f) gameEventTriggered((int)GJGameEvent::FallVHigh, m_groundObjectMaterial);
                else if (fallDistance > 300.0f) gameEventTriggered((int)GJGameEvent::FallHigh, m_groundObjectMaterial);
                else if (fallDistance > 150.0f) gameEventTriggered((int)GJGameEvent::FallMed, m_groundObjectMaterial);
                else if (fallDistance > 7.5f)   gameEventTriggered((int)GJGameEvent::FallLow, m_groundObjectMaterial);
            }
            m_fallStartY = 0.0f;
        }     
          
    }

    setYVelocity(0.0f, 43);
    m_applySlideBoost = false;

    if (!m_onGround && !noParticle && !levelFlipping() && !m_isHidden) {
        CCParticleSystemQuad* landParticles = m_useLandParticles0 ? m_landParticles0 : m_landParticles1;

        m_useLandParticles0 = !m_useLandParticles0;

        if (landParticles->getParticleCount() <= 2) {

            landParticles->setAngle(m_landParticlesAngle * flipMod());

            landParticles->setGravity(ccp(
                m_landParticles0->getGravity().x,
                m_landParticlesInitialGravityY * flipMod())
            );

            CCPoint offset = ccp(0.0f, (-15 * flipMod()) * m_vehicleSize);

            if (m_isSideways) {
                CC_SWAP(offset.x, offset.y, float)
                landParticles->setRotation(90.0f);
            }
            else {
                landParticles->setRotation(0.0f);
            }

            if (object && object->getType() == GameObjectType::Slope) {
                float angle = !m_isSideways ? 0.0f : 90.0f;
                landParticles->setRotation(angle + CC_RADIANS_TO_DEGREES(m_slopeRotation));
            }

            landParticles->setPosition(getPosition() + offset);
            landParticles->resetSystem();
        }
    }

    if (!m_justPlacedStreak) {
        placeStreakPoint();
        m_justPlacedStreak = true;
    }

    if (!m_onGround && !m_isDashing) {
        if      (m_isRobot)  m_robotSprite->runAnimation(m_currentRobotAnimation);
        else if (m_isSpider) playDynamicSpiderRun();
    }

    m_onGround = true;
    m_hasLandedSinceGravityFlip = !noParticle;

    if (relativeYVelocity <= 5.0f) {
        m_isOnGround = true;
        m_lastLandTime = m_totalTime;
    }

    m_isGroundedSinceLastFlip = true;
    m_groundHitTimer = 2;

    if (!m_isBall && (m_isRotating || m_wasOnSlope))
        stopRotation(true, 17);

    if (m_isBall && m_isBallRotating && !m_isOnSlope)
        stopRotation(true, 16);

    if (m_isBall && m_isBallRotating2)
        stopRotation(false, 18);

    if (m_isBall && !m_isRotating)
        runRotateAction(false, 6);

    if (!m_isBall
      && !isFlying()
      && !m_isOnSlope
      && !m_wasOnSlope
      && (int)getRotation() % 90) {
        stopRotation(true, 19);
    }

    m_lastGroundedPos = getPosition();

    if (!isFlying() && m_shouldTryPlacingCheckpoint) {
        deactivateStreak(false);
        m_canPlaceCheckpoint = true;
    }

    m_shouldTryPlacingCheckpoint = false;
}