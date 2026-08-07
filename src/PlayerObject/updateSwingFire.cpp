void PlayerObject::updateSwingFire()
{
    CCParticleSystemQuad* burstParticles1 = m_swingBurstParticles1;
    CCParticleSystemQuad* burstParticles2 = m_swingBurstParticles2;
    PlayerFireBoostSprite* fireBottom = m_swingFireBottom;
    PlayerFireBoostSprite* fireTop = m_swingFireTop;

    if (m_isSideways != m_isUpsideDown) {
        fireTop = m_swingFireBottom;
        fireBottom = m_swingFireTop;
        burstParticles1 = m_swingBurstParticles2;
        burstParticles2 = m_swingBurstParticles1;
    }

    fireTop->animateFireIn();
    burstParticles2->resumeSystem();
    fireBottom->animateFireOut();
    burstParticles1->stopSystem();
}