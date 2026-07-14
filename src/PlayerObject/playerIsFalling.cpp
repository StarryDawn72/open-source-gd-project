/*
	====== PlayerObject::playerIsFalling ======
	
	Returns true if the player is falling past a given threshold.
	
*/
bool PlayerObject::playerIsFalling(float yVelocity)
{
	return m_isUpsideDown ? -yVelocity < m_yVelocity : m_yVelocity < yVelocity;
}