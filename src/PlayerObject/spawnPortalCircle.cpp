#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::spawnPortalCircle(ccColor3B color, float startRadius)
{
	if (
		m_isInPlayLayer &&
		!m_isRespawning &&
		!PL->m_skipArtReload &&
		!GM->m_performanceMode &&
		!m_lastEffectObjectPos.equals(CCPointZero) )
	{
		CCCircleWave* circleEffect = CCCircleWave::create(startRadius, 5.0f, 0.3f, true);
		circleEffect->m_color = color;
		circleEffect->setPosition(m_lastEffectObjectPos);

		if (m_lastEffectObject)
		{
			circleEffect->followObject(m_lastEffectObject, true);
			circleEffect->m_delegate = PL;
			PL->addCircle(circleEffect);
		}
		m_parentLayer->addChild(circleEffect, 0);
	}
}