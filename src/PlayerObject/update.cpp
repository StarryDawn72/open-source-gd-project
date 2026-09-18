/*
    The main physics and VFX update loop for the player.
*/
void PlayerObject::update(float dt)
{
    // rename incorrect geode bindings
    bool& m_isInPlayLayer = m_playEffects;
    int& m_forceTimer = m_stateForce;
    bool& m_slopeForceLeft = m_platformerMovingLeft;
    bool& m_slopeForceRight = m_platformerMovingRight;
    double& m_reverseSyncOffset = m_maybeReverseSpeed;
    double& m_reverseSyncStep = m_maybeReverseAcceleration;
    float& m_playerScale = m_vehicleSize;
    bool& m_onGround = m_isOnGround2;
    bool& m_holdingJump = m_jumpBuffered;
    bool& m_isJumping = m_maybeIsBoosted;
    bool& m_isVelocityUncapped = m_isAccelerating;
    float& m_positionDeltaY = m_yVelocityRelated3;
    double& m_robotBoostCharge = m_accelerationOrSpeed;
    bool& m_robotBoostInvalidated = m_touchedPad;
    bool& m_wasRobotBoostInvalidated = m_wasRobotJump;
    bool& m_didSpecialGroundHit = m_maybeSpriteRelated;

    if (m_flashTime >= 0) {
        double timeSinceFlash = m_totalTime - m_flashTime - m_flashDelay;

        if (timeSinceFlash < m_flashDuration) {
            if (timeSinceFlash > 0) {
                ccColor3B mainFlashProgress = GameToolbox::multipliedColorValue(
                    m_flashMainColor,
                    m_originalMainColor,
                    timeSinceFlash / m_flashDuration);

                setColor(mainFlashProgress);

                ccColor3B secondFlashProgress = GameToolbox::multipliedColorValue(
                    m_flashSecondColor, 
                    m_originalSecondColor,
                    timeSinceFlash / m_flashDuration);

                setSecondColor(secondFlashProgress);                
            }
        }
        else {
            m_flashTime = -1.0;
            setColor(m_originalMainColor);
            setSecondColor(m_originalSecondColor);
        }
    }

    // clamp vertical velocity to ±1000 units
    m_yVelocity = MIN(MAX(m_yVelocity, -1000.0), 1000.0);

    if (m_isPlatformer)
        m_platformerXVelocity = MIN(MAX(m_platformerXVelocity, -1000.0), 1000.0);

    if (!m_isDead) {

        ccpDistance(getLastPosition(), getPosition());
        m_lastPosition = getPosition();

        m_positionDeltaY = 0.0f;

        if (!m_isLocked) {

            float scaledDt = dt * 0.9f;
            updateJump(dt * 0.9f);

            // Force timer lasts for two game ticks
            if (m_forceTimer > 0) {
                float forceBlockMultiplier = 1.0f;

                if (m_isShip)
                    forceBlockMultiplier = 0.47f;
                else if (m_isBird)
                    forceBlockMultiplier = 0.58f;
                else if (m_isSwing)
                    forceBlockMultiplier = 0.4f;
                else if (m_isBall || m_isSpider)
                    forceBlockMultiplier = 0.6f;
                else if (m_isRobot)
                    forceBlockMultiplier = 0.9f;
                
                if (m_playerScale != 1.0f) {
                    if (m_isShip)
                        forceBlockMultiplier = 0.47f * 1.25f;
                    else if (m_isBird)
                        forceBlockMultiplier = 0.58f * 1.25f;
                    else if (m_isSwing)
                        forceBlockMultiplier = 8.0f / 13.0f;
                }

                double forceVel = ((scaledDt * m_stateForceVector.y) * forceBlockMultiplier);
                addToYVelocity(forceVel, 69);

                if (forceVel != 0.0)
                    m_isVelocityUncapped = true;

                bool wasForcedUpward = (!m_isUpsideDown && forceVel > 0) || (m_isUpsideDown && forceVel < 0);

                if (wasForcedUpward)
                    m_robotBoostCharge += forceVel / 12.94f * 1.5;

                if (m_isPlatformer) {
                    float forceX = m_stateForceVector.x;
                    m_platformerXVelocity += (forceX * scaledDt);

                    if (forceX != 0.0)
                        m_affectedByForces = true;

                    if (isInNormalMode() && !m_isRotating && fabsf(m_stateForceVector.x) > 0.1f)
                    {
                        runNormalRotation(true, 1.0);
                    }
                }            
            }

            if (m_isDashing)
                setYVelocity(0.0, 1);

            if (m_isPlatformer)
                updateMove(dt * 0.9f);

            double dx = getCurrentXVelocity() * dt;

            double deltaX = dx;
            double deltaY = m_yVelocity * scaledDt;

            if (m_isDart && !m_isDashing) {
                double holdDir = m_holdingJump ? 1.0 : -1.0;
                deltaY = fabs(dx) * flipMod() * holdDir;

                if (m_playerScale != 1.0f)
                    deltaY += deltaY;
            }
            else if (m_isDashing) {
                if (m_isPlatformer) {
                    deltaX = m_dashX * scaledDt;
                    deltaY = m_dashY * scaledDt;

                    m_platformerXVelocity = m_dashX;
                    m_yVelocity = m_dashY;
                }
                else
                    deltaY = dx * m_dashY;
            }

            m_positionDeltaY = deltaY;

            if (m_isGoingLeft && !m_isPlatformer)
                deltaX = -deltaX;

            float finalDeltaX = deltaX + m_reverseSyncStep;

            if (m_isSideways) {
                double y = deltaY;
                deltaY = finalDeltaX;
                finalDeltaX = y;
            }

            // Set the final player position this tick
            setPosition(getPosition() + ccp(finalDeltaX, deltaY));

            m_reverseSyncStep = 0.0;
            if (m_reverseSyncOffset != 0.0) {

                double step = dx * 0.02f;
                double absReverseOffset = fabs(m_reverseSyncOffset);

                if (absReverseOffset < step)
                    step = absReverseOffset;

                if (m_reverseSyncOffset <= 0.0)
                    step = -step;

                m_reverseSyncStep = step;
                m_reverseSyncOffset -= step;
            }
        }

        if (isFlying()) { // Ship, UFO, Wave, Swing
            if (m_isShip) {
                if (!m_holdingJump || levelFlipping() || m_isHidden) {
                    if (m_hasShipParticles)
                        m_shipClickParticles->stopSystem();
                    m_hasShipParticles = false;
                }
                else {
                    if (!m_hasShipParticles)
                        m_shipClickParticles->resumeSystem();
                    m_hasShipParticles = true;
                }
            }

            bool velocityInThreshold = (!m_isUpsideDown && m_yVelocity > -1.0) ||
                                       (m_isUpsideDown  && m_yVelocity <  1.0);

            bool canShowDragEffect = (
                !m_isLocked
                && !m_isHidden
                && (!m_isPlatformer || m_holdingLeft || m_holdingRight || m_slopeForceLeft || m_slopeForceRight));

            if (!m_isDart && m_onGround && velocityInThreshold && canShowDragEffect)
                m_vehicleGroundParticles->resumeSystem();
            else
                m_vehicleGroundParticles->stopSystem();
        }
        else { // Cube, Ball, Robot, Spider

            int kTagHideParticles = 3; // probably a macro in RobTop's source

            if (!m_onGround || levelFlipping() || m_isLocked || m_isHidden || m_isPlatformer && fabs(m_platformerXVelocity) <= 2.5) {
                if (m_hasGroundParticles && !getActionByTag(kTagHideParticles)) {
                    CCDelayTime* delayAction = CCDelayTime::create(0.06f);
                    CCCallFunc* deactivateCall = CCCallFunc::create(this, callfunc_selector(PlayerObject::deactivateParticle));

                    // hide ground particles after 0.06 seconds
                    CCSequence* hideParticlesAction = CCSequence::create(delayAction, deactivateCall, NULL);
                    hideParticlesAction->setTag(kTagHideParticles);

                    runAction(hideParticlesAction);
                }
            } 
            else {
                if (!m_hasGroundParticles)
                    m_playerGroundParticles->resumeSystem();

                m_hasGroundParticles = true;
                stopActionByTag(kTagHideParticles);
            }
        }

        m_waveTrail->m_pulseSize = ((m_audioScale - 0.1f) * 2.1f) + 0.4f;

        if (m_isInPlayLayer) {
            if (m_isGoingLeft) {
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                float camX = PL->m_gameState.m_cameraPosition2.x;

                m_waveTrail->clearAboveXPos(camX + (winSize.width / PL->m_gameState.m_cameraZoom));
            }
            else
                m_waveTrail->clearBehindXPos(PL->m_gameState.m_cameraPosition2.x);
        }

        if (m_robotFire) {

            int kTagRobotFireOut = 9;

            if (m_isRobot
                && m_holdingJump
                && !m_robotBoostInvalidated
                && m_isJumping
                && m_robotBoostCharge > 0.27f // Min Robot charge for fire animation (probably an expanded macro)
                && m_robotBoostCharge < 1.5)  // Max Robot charge
            {
                // show robot fire boost if we are mid-jump
                if (!m_robotFire->isVisible()) {
                    m_robotFire->stopAllActions();
                    m_robotFire->setScale(0.1f);
                    m_robotFire->setVisible(true);

                    CCScaleTo* scaleAnim1 = CCScaleTo::create(0.05f, 1.44f);
                    CCScaleTo* scaleAnim2 = CCScaleTo::create(0.05f, 0.72f);
                    CCScaleTo* scaleAnim3 = CCScaleTo::create(0.05f, 1.8f);
                    CCScaleTo* scaleAnim4 = CCScaleTo::create(0.05f, 0.9f);
                    CCScaleTo* scaleAnim5 = CCScaleTo::create(0.05f, 1.8f);

                    CCSequence* fireAnimation = CCSequence::create(
                                        scaleAnim1,
                                        scaleAnim2,
                                        scaleAnim3,
                                        scaleAnim4,
                                        scaleAnim5,
                                        NULL);

                    m_robotFire->runAction(fireAnimation);
                    m_robotBurstParticles->resumeSystem();
                }
            }
            else if (m_robotFire->isVisible() && !getActionByTag(kTagRobotFireOut)) {
                m_robotFire->stopAllActions();

                CCScaleTo* exitAnim = CCScaleTo::create(0.15f, 0.05f);
                CCHide* hideAction = CCHide::create();

                CCSequence* exitAndHide = CCSequence::create(exitAnim, hideAction, NULL);

                exitAndHide->setTag(kTagRobotFireOut);
                m_robotFire->runAction(exitAndHide);
                m_robotBurstParticles->stopSystem();
            }
        }

        if (m_isRobot
            && m_holdingJump
            && !m_robotBoostInvalidated
            && m_isJumping
            && m_robotBoostCharge > 0.1f // Min Robot charge for burst particles (probably an expanded macro)
            && m_robotBoostCharge < 1.5  // Max Robot charge
            && !m_isHidden)
        {
            if (!m_robotBurstParticles->isActive())
                m_robotBurstParticles->resumeSystem();
        }
        else if (m_robotBurstParticles->isActive())
            m_robotBurstParticles->stopSystem();

        m_didSpecialGroundHit = false; // Never set to true, dead weight.

        if (m_ghostTrail) {
            float yOffset;
            float headY;
            CCPoint ghostTrailPos = CCPointZero;

            if (m_isRobot) {
                yOffset = 7.0f;
                headY = m_robotSprite->m_headSprite->getPosition().y;
                ghostTrailPos = ccp(0.0, yOffset + (headY * 0.4));
            }
            else if (m_isSpider) {
                yOffset = 2.0f;
                headY = m_spiderSprite->m_headSprite->getPosition().y;
                ghostTrailPos = ccp(0.0, yOffset + (headY * 0.4));
            }

            m_ghostTrail->m_position = ghostTrailPos;                    
        }

        if (m_isDashing)
            updateDashAnimation();

        if (m_isSwing) {
            float firstAngle = m_isGoingLeft ? 90.0f : 0.0f;
            m_swingBurstParticles1->setAngle((45.0f - getRotation()) - 180.0f + firstAngle);

            float secondAngle = m_isGoingLeft ? -90.0f : 0.0f;
            m_swingBurstParticles2->setAngle(((-getRotation() - 45.0f) - 180.0f) + secondAngle);
        }

        updateJumpVariables();
        updateStateVariables();

        if (m_shipStreak) {
            gd::string streakFrameName = getFrameForStreak(m_shipStreakType, m_totalTime);
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(streakFrameName.c_str(), false);
            m_shipStreak->setTexture(texture);
        }

        if (m_isPlatformer && m_isDashing && m_dashRing) {
            float maxDuration = m_dashRing->m_maxDuration;
            if (maxDuration > 0.0 && m_totalTime - m_dashStartTime > maxDuration) {
                stopDashing();
                m_holdingJump = false;
            }
        }
    }
}