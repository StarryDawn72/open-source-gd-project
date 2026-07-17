#define GM GameManager::sharedState()
/*
	====== PlayerObject::playSpawnEffect ======
	
	This function handles the player blink and ripple
	effects when respawning.
	
*/
void PlayerObject::playSpawnEffect()
{

	if (m_isBeingSpawnedByDualPortal) return;
	stopActionByTag(11);

	float blinkDuration = 0.4f;
	unsigned int blinks = 4;

	auto blinkAction = CCBlink::create(blinkDuration, blinks);
	auto showAction = CCShow::create();
	auto blinkSequence = CCSequence::create((CCFiniteTimeAction *)blinkAction, showAction, nullptr);
	blinkSequence->setTag(11);
	runAction(blinkSequence);

	if (!GM->m_performanceMode) {

		for (int i = 0; i < 4; i++) {
			float rippleInterval = 0.1f;

			auto circleSpawnAction = CCCallFunc::create(this, callfunc_selector(PlayerObject::spawnCircle));
			auto delayAction = CCDelayTime::create(i * rippleInterval);
			auto rippleSequence = CCSequence::create((CCFiniteTimeAction *)delayAction,circleSpawnAction, nullptr);

			runAction(rippleSequence);	
		}
	}
}
