void PlayerObject::didHitHead()
{
	if (m_flipBlockTimer > 0)
	{
		hardFlipGravity();
		m_isJumping = true;
		m_onGround = false;

		if (m_noAutoJumpTimer > 0)
		{
			m_canJump = false;
			m_isJumpUnused = false;
			m_holdingJump = false;
		}
	}
}