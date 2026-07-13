/*
	====== PLAYEROBJECT::PLAYSPAWNEFFECT ======
	
	This function handles the player blink and ripple
	effects when respawning.
	
*/
void PlayerObject::playSpawnEffect()
{

	if (m_isBeingSpawnedByDualPortal) return;
	stopActionByTag(11);

	float blinkDuration = 0.4f;
	unsigned int blinks = 4;

	CCBlink*    blinkAction = CCBlink::create(blinkDuration, blinks);
	CCShow*     showAction = CCShow::create();
	CCSequence* blinkSequence = CCSequence::create((CCFiniteTimeAction *)blinkAction, showAction, 0);
	blinkSequence->setTag(11);
	runAction(blinkSequence);

	if (!GM->m_performanceMode) {

		for (int i = 0; i < 4; i++) {
			float rippleInterval = 0.1f;

			CCCallFunc*  circleSpawnAction = CCCallFunc::create(this, callfunc_selector(PlayerObject::spawnCircle));
			CCDelayTime* delayAction = CCDelayTime::create(i * rippleInterval);
			CCSequence*  rippleSequence = CCSequence::create((CCFiniteTimeAction *)delayAction,circleSpawnAction,0);

			runAction(rippleSequence);	
		}
	}
}