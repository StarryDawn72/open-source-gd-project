#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::spawnDualCircle()
{
	bool m_isRespawning = m_maybeReducedEffects;

	if (!m_isRespawning && !PL->m_skipArtReload) {
		if (!GM->m_performanceMode) {

			// Start radius: 50
			// End radius:   2
			// Duration:     0.25
			// Fade in:      true
			CCCircleWave* circleEffect = CCCircleWave::create(50.0f, 2.0f, 0.25f, true);

			circleEffect->m_color.r = m_playerColor1.r;
			circleEffect->m_color.g = m_playerColor1.g;
			circleEffect->m_color.b = m_playerColor1.b;
			
			circleEffect->setPosition(getPosition());
			m_parentLayer->addChild(circleEffect, 0);

			circleEffect->followObject(this, true);
			circleEffect->m_delegate = PL;

			PL->addCircle(circleEffect);
		}
	}
}