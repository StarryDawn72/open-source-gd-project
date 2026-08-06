void PlayerObject::exitPlatformerAnimateJump()
{
	if (m_iconSprite->getActionByTag(13)) {
		m_iconSprite->stopActionByTag(13);
		m_iconSprite->stopActionByTag(14);

		CCScaleTo* scaleAction = CCScaleTo::create(0.1f, 1.0f);
		CCEaseInOut* exitAnim = CCEaseInOut::create(scaleAction, 2.0f);

		exitAnim->setTag(14);
		m_iconSprite->runAction(exitAnim);

		m_iconGlow->stopActionByTag(13);
		m_iconGlow->stopActionByTag(14);

		CCScaleTo* scaleAction2 = CCScaleTo::create(0.1f, 1.0f);
		CCEaseInOut* exitAnim2 = CCEaseInOut::create(scaleAction2, 2.0f);

		exitAnim2->setTag(14);
		m_iconGlow->runAction(exitAnim2);
	}
}