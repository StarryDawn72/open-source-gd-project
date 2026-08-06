void PlayerObject::stopStreak2()
{
	m_waveTrail->stopActionByTag(8);
	m_waveTrail->setOpacity(0);
	m_waveTrail->stopStroke();
}