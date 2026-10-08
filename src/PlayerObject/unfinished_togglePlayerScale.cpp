#define GM GameManager::sharedState()

#define kPlayerScaleNormal 1.0f
#define kPlayerScaleMini 0.6f

// UNFINISHED
void PlayerObject::togglePlayerScale(bool enable, bool noEffects)
{
    if (m_playerScale == kPlayerScaleNormal) {
        if (!enable) return;
        m_playerScale = kPlayerScaleMini;

        if (m_defaultMiniIcon) {
            if (m_isBall)
                updatePlayerRollFrame(0);
            else if (!m_isRobot && !m_isDart)
                updatePlayerFrame(0);
        }
    } else {
        if (enable) return;
        m_playerScale = kPlayerScaleNormal;

        if (m_isPlatformer)
            m_stateScale = 2;

        if (m_defaultMiniIcon) {
            if (m_isBall)
                updatePlayerRollFrame(GM->m_playerBall.value());
            else if (!m_isRobot && !m_isDart)
                updatePlayerFrame(m_maybeSavedPlayerFrame);
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

    m_regularTrail->setStroke(
        m_streakStrokeWidth *
        m_playerScale *
        (m_isDart ? 0.8f : 1.0f)
    );

    if (m_playEffects || m_isDart)
        m_waveTrail->m_waveSize = m_playerScale;

    // This line will give an error if you have the macro renamed bindings
    if (m_ghostTrail) m_ghostTrail->m_playerScale = m_playerScale;

    // Whoops, it turns out there is a wierd private function here that
    // I don't have the time to RE right now...
    // I'm gonna skip this function
}