#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()
#define kTagPlayerScaleEffect 6

void PlayerObject::togglePlayerScale(bool enable, bool noEffects)
{
    if (m_playerScale == 1.0f) { // Turning mini
        if (!enable)
            return;

        m_playerScale = 0.6f;

        if (m_defaultMiniIcon) {
            if (m_isBall) {
                updatePlayerRollFrame(0);
            }
            else if (!m_isRobot && !m_isDart) {
                updatePlayerFrame(0);            
            }
        }
    }
    else { // Turning normal size

        if (enable)
            return;

        if (m_isPlatformer)
            m_scaleChangeTimer = 2;

        m_playerScale = 1.0f;
        
        if (m_defaultMiniIcon) {
            if (m_isBall) {
                updatePlayerRollFrame(GM->m_playerBall.value());
            }
            else if (!m_isRobot && !m_isDart) {
                updatePlayerFrame(m_maybeSavedPlayerFrame);   // TODO: rename!          
            }
        }        
    }

    m_spriteWidthScale = m_playerScale;
    m_spriteHeightScale = m_playerScale;

    m_landParticles0->loadScaledDefaults(m_playerScale);
    m_landParticles1->loadScaledDefaults(m_playerScale);
    m_playerGroundParticles->loadScaledDefaults(m_playerScale);
    m_vehicleGroundParticles->loadScaledDefaults(m_playerScale);
    m_trailingParticles->loadScaledDefaults(m_playerScale);
    m_shipClickParticles->loadScaledDefaults(m_playerScale);
    m_ufoClickParticles->loadScaledDefaults(m_playerScale);
    m_robotBurstParticles->loadScaledDefaults(m_playerScale);
    m_dashParticles->loadScaledDefaults(m_playerScale);
    m_swingBurstParticles1->loadScaledDefaults(m_playerScale);
    m_swingBurstParticles2->loadScaledDefaults(m_playerScale);

    float mod = m_isDart ? 0.8f : 1.0f;

    m_regularTrail->setStroke((m_streakStrokeWidth * m_playerScale) * mod);

    if (m_isInPlayLayer || m_isDart)
        m_waveTrail->m_waveSize = m_playerScale;

    if (m_ghostTrail)
        m_ghostTrail->m_playerScale = m_playerScale;

    if (m_shipStreak)
        updateStreakSettings(m_shipStreak, (int)m_shipStreakType, this);

    m_actionManager->stopInternalAction(kTagPlayerScaleEffect);

                      // TODO: this might need a new name ↓
    if (!m_isInPlayLayer || m_isRespawning || PL->m_skipArtReload) {

        // Apply scale instantly if you're in the editor or respawning.
        setScaleX(m_playerScale);
        setScaleY(m_playerScale);
    }
    else {

        CCScaleTo* scaleEffect = CCScaleTo::create(0.5f, m_playerScale, m_playerScale);
        CCEaseElasticOut* elasticScaleEffect = CCEaseElasticOut::create(scaleEffect);

        elasticScaleEffect->setTag(kTagPlayerScaleEffect);
        m_actionManager->runInternalAction(elasticScaleEffect, this);

        ccColor3B color = m_playerScale == 1.0f
            ? ccc3(0, 255, 150)
            : ccc3(255, 0, 150);

        if (!noEffects) {
            PL->lightningFlash(m_lastEffectObjectPos, color);
            spawnPortalCircle(color, 45.0f);
            spawnScaleCircle();
        }
    }

    if (m_isBall && m_isRotating)
        runRotateAction(false, 8);
    
    placeStreakPoint();
    updateRobotAnimationSpeed();
}
