// @version 2.2081
void levelWillFlip()
{
    m_trailingParticles->setLife(m_trailingParticleLife * 0.3f);
    deactivateStreak(true);
}