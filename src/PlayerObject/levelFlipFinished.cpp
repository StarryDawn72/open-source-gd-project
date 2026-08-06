void levelFlipFinished()
{
    m_trailingParticles->setLife(m_trailingParticleLife);

    if (!isFlying()) {
        if (m_alwaysShowStreak) {
            resetStreak();
            activateStreak();
        }
    }
    else {
        resetStreak();
        activateStreak();

        if (m_isDart) {
            placeStreakPoint();
        }
    }
}