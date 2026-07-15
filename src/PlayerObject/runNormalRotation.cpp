/*
	====== PlayerObject::runNormalRotation ======
	
	This function is what begins the continuous visual spin of
	the cube and ball game modes. It takes "speed" as a final modifier,
	as well as player scale, gravity direction, movement direction, and
	gravity scale.
	
*/
void PlayerObject::runNormalRotation(bool notNormalMode, float speed)
{
	// rename bindings
    float& m_playerScale = m_vehicleSize;
	bool& m_slopeForceLeft = m_platformerMovingLeft;
	bool& m_slopeForceRight = m_platformerMovingRight;
    
    if (notNormalMode || (!isFlying() && !m_isRobot && !m_isSpider && !m_isDashing &&
		(!m_isPlatformer || m_holdingLeft || m_holdingRight || m_slopeForceLeft || m_slopeForceRight))) {

		m_isRotating = true;

		float rotationDuration = (m_playerScale != 1.0f) ? (20.0f / 60.0f) : (26.0f / 60.0f);
		int rotatedMod = m_isSideways ? -1 : 1;

        m_rotationSpeed = (180.0f * flipMod() * reverseMod() * rotatedMod * m_gravityMod * speed) / rotationDuration;
    }
}
/*
	Function overload with default parameters.
*/
void PlayerObject::runNormalRotation()
{
    runNormalRotation(false, 1.0f);
}