#define PL GameManager::sharedState()->getPlayLayer()
/*
	====== PlayerObject::levelFlipping ======
	
	Returns true if you are playing the level in PlayLayer
	and the mirror portal animation is active.
	
*/
bool PlayerObject::levelFlipping()
{
	bool isInPlayLayer = m_playEffects;
	
	if (isInPlayLayer) {

		float levelFlipProgress = PL->m_gameState.m_levelFlipping;
		return levelFlipProgress != 0.0f &&
				levelFlipProgress != 1.0f;
	}

	return false;
}