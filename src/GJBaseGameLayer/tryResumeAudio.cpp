void GJBaseGameLayer::tryResumeAudio()
{
    if (m_resumeTimer <= 0 && m_audioPaused) {
        resumeAudio();
        m_audioPaused = false;
    }
}