/*
	====== PLAYEROBJECT::STOPROTATION ======
	
	Resets all rotation flags and freezes the player spin
	instantly.
	
*/
void PlayerObject::stopRotation(bool ground, int type)
{
	m_isRotating = false;
	m_isBallRotating2 = false;
	m_isBallRotating = false;
	m_rotationSpeed = 0.0f;
}