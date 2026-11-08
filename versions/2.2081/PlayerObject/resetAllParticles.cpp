void PlayerObject::resetAllParticles()
{
	for (int i = 0; i < m_particleSystems->count(); i++) {
		CCParticleSystem* particle = (CCParticleSystem*)(m_particleSystems->objectAtIndex(i));
		particle->resetSystem();
		particle->stopSystem();
	}
}