#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()
/*
	====== PlayerObject::spawnPortalCircle ======
	
	Spawns a circle effect with a given color and start radius.
	Triggered when activating a portal (duh).
	
*/
void PlayerObject::spawnPortalCircle(ccColor3B color, float startRadius)
{
	// rename bindings
	bool& m_isInPlayLayer = m_playEffects;
	bool& m_isRespawning = m_maybeReducedEffects;
	GameObject* m_lastEffectObject = m_lastActivatedPortal;
	CCPoint m_lastEffectObjectPos = m_lastPortalPos;

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