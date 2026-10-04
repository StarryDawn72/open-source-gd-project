void PlayerObject::doReversePlayer(bool reverse)
{
    bool directionChanged = m_isGoingLeft != reverse;
    m_isGoingLeft = reverse;

    if (directionChanged)
        m_reverseTimer = 2; // Reversed flag lasts two game ticks

    float sidewaysMod = m_isSideways ? -1.0f : 1.0f;
    float reverseMod = this->reverseMod();

    if (directionChanged && m_isDart)
        createFadeOutDartStreak();

    m_vehicleGroundParticles = m_vehicleGroundParticles;
    m_waveTrail->m_isFlipped = reverse;

    m_vehicleGroundParticles->setScaleX(reverseMod * sidewaysMod);

    updatePlayerGlow();
    updatePlayerArt();

    if (m_fadeOutStreak && m_isDart && directionChanged) {
        m_waveTrail->reset();
        placeStreakPoint();
    }
    
    if (m_isBall)
        runRotateAction(true, 1);
}