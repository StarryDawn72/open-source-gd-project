void PlayerObject::lockPlayer()
{
	bool& m_onGround = m_isOnGround2; // Rename binding

	if (m_isDart)
		placeStreakPoint();

	m_isLocked = true;

	stopRotation(true, 100);
	releaseButton(PlayerButton::Jump);
	deactivateParticle();

	m_onGround = false;

	if (m_isDart)
		fadeOutStreak2(0.4f);
}