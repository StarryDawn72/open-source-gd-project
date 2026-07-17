#define PL GameManager::sharedState()->getPlayLayer()
/*
	====== PlayerObject::playBumpEffect ======
	
	Spawns the expanding circle effect upon touching
	a jump pad.
	
*/
void PlayerObject::playBumpEffect(int objectType, GameObject *player)
{
	// rename geode bindings
	float& m_playerScale = m_vehicleSize;
	GameObject* m_lastEffectObject = m_lastActivatedPortal;
	CCPoint m_lastEffectObjectPos = m_lastPortalPos;
	bool& m_isInPlayLayer = m_playEffects;

	if (GM->m_performanceMode || !m_isInPlayLayer)
		return;


	GameObjectType type = static_cast<GameObjectType>(objectType);
	ccColor3B effectColor;

	float startRadius = (m_playerScale >= 1.0f && type == GameObjectType::RedJumpPad)
						? 12.0f
						: 10.0f;

	CCCircleWave* bumpEffect = CCCircleWave::create(startRadius, 40.0f, 0.25f, false);

	if      (type == GameObjectType::SpiderPad)   effectColor = ccc3(255, 50, 255); // pink
	else if (type == GameObjectType::PinkJumpPad) effectColor = ccc3(255, 0, 255);  // magenta
	else if (type == GameObjectType::GravityPad)  effectColor = ccc3(0, 255, 255);  // cyan
	else                                          effectColor = ccc3(255, 200, 0);  // yellow

	bumpEffect->m_color = effectColor;
	bumpEffect->setPosition(m_lastEffectObjectPos);

	if (m_lastEffectObject) {
		bumpEffect->followObject(m_lastEffectObject, true);
		bumpEffect->m_delegate = PL;
		PL->addCircle(bumpEffect);
	}

	m_parentLayer->addChild(bumpEffect, 0);
}