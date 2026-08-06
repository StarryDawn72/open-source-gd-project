#define PL GameManager::sharedState()->getPlayLayer()

bool PlayerObject::levelFlipping()
{
	bool& m_isInPlayLayer = m_playEffects;
	
	if (m_isInPlayLayer) {

		float levelFlipProgress = PL->m_gameState.m_levelFlipping;
		return levelFlipProgress != 0.0f &&
				levelFlipProgress != 1.0f;
	}

	return false;
}