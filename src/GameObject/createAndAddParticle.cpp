#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()
/*
	Creates a new particle system with the given parameters,
	adds it to the game layer, and returns it.
	
*/
CCParticleSystemQuad* GameObject::createAndAddParticle(int objectType, const char *plistName, int tag, tCCPositionType positionType)
{
	if ( !PL || this->m_hasNoParticles )
		return nullptr;

	auto particle = PL->createParticle(objectType, plistName, tag, positionType);
	this->m_particleString = GM->getGameLayer()->getParticleKey(objectType, plistName, tag, positionType);

	this->m_hasParticles = true;
	return particle;
}