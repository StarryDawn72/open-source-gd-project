void PlayerObject::deactivateParticle()
{
    if (m_hasGroundParticles)
        m_playerGroundParticles->stopSystem();
		
    m_hasGroundParticles = false;
}