void PlayerObject::removeAllParticles()
{
	for (int i = 0; i < m_particleSystems->count(); i++)
	{
		CCParticleSystem* particle = static_cast<CCParticleSystem*>(m_particleSystems->objectAtIndex(i));
		particle->resetSystem();
		particle->stopSystem();
		particle->removeFromParentAndCleanup(false);
	}
}