bool PlayerObject::canStickToGround()
{
	bool m_isJumpUnused = m_stateRingJump; // Rename incorrect binding

    return !m_isShip && !m_isDart || !m_isJumpUnused;
}