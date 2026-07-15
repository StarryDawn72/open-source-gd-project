/*
	====== PlayerObject::runBallRotation ======
	
	This function behaves as the standard rotation
	initiator for the Ball game mode. Once invoked,
	the new speed assigned to m_rotationSpeed will be
	picked up by updateRotation and the player will
	start spinning.
	
*/

void PlayerObject::runBallRotation(float speed)
{
	if (m_isDashing || m_isPlatformer) return;

	float duration = 1.0f;
	
	// rename incorrect member variable names
	bool& m_ballRotationMultiplierActive = m_isBallRotating;
	float& m_ballRotationMultiplier = m_rotateSpeed;
	float& m_playerScale = m_vehicleSize;

	m_ballRotationMultiplierActive = speed != 1.0f;
	m_ballRotationMultiplier = speed;

	float scaleMod = (m_playerScale == 1.0f) ? 1.0f : 0.8f;
	float playerSpeed = m_playerSpeed;

	if (playerSpeed == 0.7f) {
		duration = 1.2405638f; // 311.5801 / 251.16
	}
	else if (playerSpeed == 1.1f) {
		duration = 0.80424345f; // 311.5801 / 387.4201
	}
	else if (playerSpeed == 1.3f) {
		duration = 0.6657693f; // 311.5801 / 468.0002
	}
	else if (playerSpeed == 1.6f) {
		duration = 0.5409375f; // 311.5801 / 576.0002
	}

	float finalSpeed = (flipMod() * 120.0f * reverseMod()) / (scaleMod * 0.2 * duration);
	m_rotationSpeed = finalSpeed;
	if (m_isSideways) m_rotationSpeed *= -1.0f;
	m_isRotating = true;
}