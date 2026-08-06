void levelWillFlip()
{
    m_trailingParticles->setLife(m_trailingParticleLife * 0.3f);
    deactivateStreak(true);
}