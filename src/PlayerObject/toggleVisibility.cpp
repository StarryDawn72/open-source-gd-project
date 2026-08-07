void PlayerObject::toggleVisibility(bool visible)
{
    if (m_isHidden == visible) {
        if (!visible)
            stopActionByTag(11);
		
        m_isHidden = !visible;
        setVisible(visible);

        if (visible) {
            if (isFlying()) {
                resetStreak();
                activateStreak();
                m_trailingParticles->resetSystem();

                if (m_isDart) placeStreakPoint();
                else if (m_isShip && !m_isPlatformer) {
                    if (m_shipStreak)
                        m_shipStreak->setVisible(true);
                }
            }
            else if (m_alwaysShowStreak) {
                resetStreak();
                activateStreak();
            }
        }
        else {
            deactivateStreak(true);

            if (m_shipStreak)
                m_shipStreak->setVisible(false);

            resetAllParticles();
        }
    }
}