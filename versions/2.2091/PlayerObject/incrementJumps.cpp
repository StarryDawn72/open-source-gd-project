void PlayerObject::incrementJumps()
{
	if (m_isInPlayLayer) {
		PL->incrementJumps();
		m_hasEverJumped = true;
	}
}