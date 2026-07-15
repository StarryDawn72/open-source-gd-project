/*
	====== PlayerObject::playerIsFallingBugged ======
	
	Determines if the player is falling. Returns true if the player's vertical 
	velocity exceeds the double the current gravity value (usually around ~1.9).
	
*/
bool playerIsFallingBugged()
{
    if (m_isSideways || m_isPlatformer || m_isSwing || m_fixGravityBug) {
        return playerIsFalling(m_gravity * 2.0);
    }

	bool& m_isInDualMode = m_unkA99;
    double gravity = m_isInDualMode ? -m_gravity : m_gravity;
	double threshold = gravity * 2.0;

	return m_isUpsideDown ? threshold < m_yVelocity : threshold > m_yVelocity;
}