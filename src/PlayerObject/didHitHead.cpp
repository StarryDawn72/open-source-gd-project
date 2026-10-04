void PlayerObject::didHitHead()
{
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