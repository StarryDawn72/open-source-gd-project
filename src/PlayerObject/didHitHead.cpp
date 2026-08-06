void PlayerObject::didHitHead()
{
	// Rename incorrect bindings
	bool& m_isJumpUnused = m_stateRingJump;
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	bool& m_holdingJump = m_jumpBuffered;

	if (m_stateFlipGravity > 0)
	{
		hardFlipGravity();
		m_isJumping = true;
		m_onGround = false;

		if (m_stateNoAutoJump > 0)
		{
			m_canJump = false;
			m_isJumpUnused = false;
			m_holdingJump = false;
		}
	}
}