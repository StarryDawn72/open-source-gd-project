#define GM GameManager::sharedState()

void PlayerObject::spawnCircle2()
{
	if ( !GM->m_performanceMode ) {

		// Start radius: 5
		// End radius:   50
		// Duration:     0.3s
		// Fade in:      false
		CCCircleWave* circleEffect = CCCircleWave::create(5.0f, 50.0f, 0.3f, false);

		circleEffect->m_color.r = m_playerColor2.r;
		circleEffect->m_color.g = m_playerColor2.g;
		circleEffect->m_color.b = m_playerColor2.b;

		circleEffect->setPosition(getPosition());
		m_parentLayer->addChild(circleEffect, 0);
	}
}