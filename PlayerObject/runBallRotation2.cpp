/*
	====== PLAYEROBJECT::RUNBALLROTATION2 ======
	
	Alternate version of runBallRotation with slower
	rotation speed and inverted rotation direction. Called
	in the Ball game mode when you flip gravity or perform a
	ring jump.
	
*/
void PlayerObject::runBallRotation2()
{
	if (m_isDashing) return;

	float duration = 1.0f;
	float playerScale = m_vehicleSize;
	float scaleMod = (playerScale == 1.0f) ? 1.0f : 0.8f;

	float playerSpeed = m_playerSpeed;
	if (playerSpeed == 0.7f) {
		duration = 1.2405638;
	}
	else if (playerSpeed == 1.1f) {
		duration = 0.80424345;
	}
	else if (playerSpeed == 1.3f) {
		duration = 0.6657693;
	}
	else if (playerSpeed == 1.6f) {
		duration = 0.5409375;
	}

	m_isBallRotating2 = true;
	m_rotationSpeed = (flipMod() * -340.0f * reverseMod() * m_gravityMod) / (scaleMod * 0.8f * duration);
}