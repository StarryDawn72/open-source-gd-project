void PlayerObject::incrementJumps()
{
	bool m_isInPlayLayer = m_playEffects;
	if (m_isInPlayLayer) {
		PL->incrementJumps();
		m_hasEverJumped = true;
	}
}