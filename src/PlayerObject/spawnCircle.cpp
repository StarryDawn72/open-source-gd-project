#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::spawnCircle()
{
	if (!GM->m_performanceMode)
	{
		// Start radius: 70
		// End radius:   2
		// Duration:     0.3s
		// Fade in:      true
		CCCircleWave* circleEffect = CCCircleWave::create(70.0f, 2.0f, 0.3f, true);

		circleEffect->m_color.r = m_playerColor1.r;
		circleEffect->m_color.g = m_playerColor1.g;
		circleEffect->m_color.b = m_playerColor1.b;
		
		setPosition(getPosition());
		m_parentLayer->addChild(circleEffect, 0);

		circleEffect->followObject(this, true);
		circleEffect->m_delegate = PL;

		PL->addCircle(circleEffect);
		circleEffect->m_circleMode = CircleMode::Outline;
	}
}