void PlayerObject::deactivateStreak(bool stop)
{
    if (!m_alwaysShowStreak || stop)
        m_regularTrail->stopStroke();

    if (m_fadeOutStreak) {
        m_fadeOutStreak = false;
		float duration = m_isInPlayLayer ? 0.2f : 0.6f;
        this->fadeOutStreak2(duration);
    }
}