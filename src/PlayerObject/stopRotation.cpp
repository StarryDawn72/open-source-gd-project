/*
	====== PlayerObject::stopRotation ======
	
	Resets all rotation flags and freezes the player spin
	instantly.
	
*/
void PlayerObject::stopRotation(bool ground, int type)
{
	// rename incorrect binding
	bool& m_ballRotationMultiplierActive = m_isBallRotating;

	m_isRotating = false;
	m_isBallRotating2 = false;
	m_ballRotationMultiplierActive = false;
	m_rotationSpeed = 0;
}