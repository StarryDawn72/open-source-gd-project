void PlayerObject::playerDestroyed(bool noEffects)
{
    if (m_isDart)
        fadeOutStreak2(0.2f);

    stopDashing();

    m_isDead = true;

    stopRotation(1, 5);
    stopParticles();

    m_lastPosition = getPosition();

    if (m_robotFire) {
        m_robotFire->stopAllActions();
        m_robotFire->setVisible(0);
    }
	
    toggleGhostEffect(GhostType::Disabled);
    disableSwingFire();

    if (!m_playEffects || noEffects || m_isHidden)
        setOpacity(0);
    else
        playDeathEffect();
}