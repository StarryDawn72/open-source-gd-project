double PlayerObject::getCurrentXVelocity()
{
	if (m_isPlatformer)
		return m_platformerXVelocity;
	else
		return m_playerSpeed * m_speedMultiplier;
}