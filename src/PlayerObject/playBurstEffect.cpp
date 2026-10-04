#define kTagBirdParticles 7

void PlayerObject::playBurstEffect()
{
    if (!levelFlipping() && !m_isHidden) {
		m_ufoClickParticles->resumeSystem();
		stopActionByTag(kTagBirdParticles);

		CCDelayTime* delay = CCDelayTime::create(0.12f);
		CCCallFunc* stopCall = CCCallFunc::create(this, callfunc_selector(PlayerObject::stopBurstEffect));
		CCSequence* effectSequence = CCSequence::create(delay, stopCall, nullptr);

		effectSequence->setTag(kTagBirdParticles);
		runAction(effectSequence);
    }
}