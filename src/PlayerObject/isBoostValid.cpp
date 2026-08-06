bool PlayerObject::isBoostValid(float yVelocity)
{
	bool m_isGoingDownSlope = m_slopeFlipGravityRelated;

	if (m_isUpsideDown) {
		if (m_isCurrentSlopeTop || !m_isGoingDownSlope)
			return m_yVelocity > yVelocity;
	}
	else if (m_isCurrentSlopeTop && m_isGoingDownSlope)
		return m_yVelocity > yVelocity;
	
	return m_yVelocity < yVelocity;
}