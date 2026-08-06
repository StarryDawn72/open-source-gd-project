#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::spawnScaleCircle()
{
	bool m_isRespawning = m_maybeReducedEffects;

	if (!m_isRespawning && !PL->m_skipArtReload ) {
		if (!GM->m_performanceMode) {

			// Mini
			float startRadius = 50.0f;
			float endRadius = 2.0f;
			float duration = 0.25f;
			GLubyte r = 255;
			GLubyte g = 0;
			bool fadeIn = true;

			// Regular size
			if (m_vehicleSize == 1.0) {
				startRadius = 10.0f;
				endRadius = 40.0f;
				duration = 0.3f;
				r = 0;
				g = 255;
				fadeIn = false;
			}

			CCCircleWave* circleEffect = CCCircleWave::create(startRadius, endRadius, duration, fadeIn);
			
			circleEffect->m_color.r = r;
			circleEffect->m_color.g = g;
			circleEffect->m_color.b = 150;

			circleEffect->setPosition(getPosition());
			m_parentLayer->addChild(circleEffect, 0);

			circleEffect->followObject(this, true);
			circleEffect->m_delegate = PL;

			PL->addCircle(circleEffect);
		}
	}
}