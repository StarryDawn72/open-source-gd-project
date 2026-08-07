#define GM GameManager::sharedState()

void PlayerObject::activateStreak()
{
    if (!levelFlipping() && !GM->m_editorEnabled && !m_isHidden)
    {
        m_regularTrail = m_regularTrail;
        m_fadeOutStreak = true;
        m_regularTrail->resumeStroke();

        if (m_isDart) {
            m_waveTrail->m_currentPoint = getPosition();
            m_waveTrail->stopAllActions();
            m_waveTrail->setOpacity(255);
            m_waveTrail->resumeStroke();
        }
    }
}