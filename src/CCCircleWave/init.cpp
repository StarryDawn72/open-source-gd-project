/*
	====== CCCircleWave::init ======
	
	Initializes the circle wave CCAction with a start radius,
	end radius, and duration. "fadeIn" makes the circle's opacity
	fade from 0 to 255 to 0 instead of 255 to 0. "easeOut" applies
	easing to both the radius tween and the opacity tween with a rate of 2.0.
	
*/
bool CCCircleWave::init(float startRadius, float endRadius, float duration, bool fadeIn, bool easeOut)
{
	baseSetup(startRadius);
	CCAction* waveAction;

	// 1. Fade in and out over duration seconds.
	if (fadeIn) {
		m_opacity = 0.0f;

		auto radiusTween = CCActionTween::create(duration, "radius", m_radius, endRadius);

		auto fadeInTween = CCActionTween::create(duration * 0.5f, "opacity", m_opacity, 255.0f);
		auto fadeOutTween = CCActionTween::create(duration * 0.5f, "opacity", 255.0f, 0.0f);
		auto cleanupAction = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		auto waveSequence = CCSequence::create(fadeInTween, fadeOutTween, cleanupAction, nullptr);
		waveAction = CCSpawn::create(radiusTween, waveSequence, nullptr);
	}
	// 2. Fade out only.
	else {
		m_opacity = 255.0f;

		CCActionInterval* radiusTween = CCActionTween::create(duration, "radius", m_radius, endRadius);
		CCActionInterval* opacityTween = CCActionTween::create(duration, "opacity", m_opacity, 0.0f);

		if (easeOut) {
			// Ease the radius and fade tweens if the "easeOut" parameter is true

			radiusTween = CCEaseOut::create(radiusTween, 2.0f);
			auto fadeOutTween = CCActionTween::create(duration, "opacity", m_opacity, 0.0f);
			opacityTween = CCEaseOut::create(fadeOutTween, 2.0f);
		}

		auto spawnAction = CCSpawn::create(radiusTween, opacityTween, nullptr);
		auto cleanupAction = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		waveAction = CCSequence::create(spawnAction, cleanupAction, nullptr);
	}

	CCDirector::sharedDirector()->getActionManager()->addAction(waveAction, this, false);
	return true;
}