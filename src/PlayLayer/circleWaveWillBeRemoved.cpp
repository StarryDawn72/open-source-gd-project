/*
	====== PlayLayer::circleWaveWillBeRemoved ======
	
	Removes the given CCCircleWave instance from the list
	of circle waves in the level.
	
*/

void PlayLayer::circleWaveWillBeRemoved(CCCircleWave *circleWave)
{
    m_circleWaveArray->removeObject(circleWave, true);
}