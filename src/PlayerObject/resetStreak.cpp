void PlayerObject::resetStreak()
{
	if (!levelFlipping())
	{
		m_regularTrail->reset();
		m_regularTrail->setPosition(getPosition() + ccp(-5.0f, 0.0f));

		m_waveTrail->reset();
		m_waveTrail->setOpacity(255);
		m_waveTrail->stopAllActions();
		m_waveTrail->setPosition(getPosition());
	}
}