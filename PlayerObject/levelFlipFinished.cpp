/*
	====== PLAYEROBJECT::LEVELFLIPFINISHED ======
	
	Handles the visual effects after the completion of
	a mirror portal animation.
	
*/
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