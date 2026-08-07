void PlayerObject::playBurstEffect()
{
    if (!levelFlipping() && !m_isHidden) {
		m_ufoClickParticles->resumeSystem();
		stopActionByTag(7);

		CCDelayTime* delay = CCDelayTime::create(0.12f);
		CCCallFunc* stopCall = CCCallFunc::create(this, callfunc_selector(PlayerObject::stopBurstEffect));
		CCSequence* effectSequence = CCSequence::create(delay, stopCall, nullptr);

		effectSequence->setTag(7);
		runAction(effectSequence);
    }
}