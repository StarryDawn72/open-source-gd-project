/*
	====== PlayerObject::boostPlayer ======
	
	Applies a boost to the player by setting upward velocity and handling
	rotation, animation, and grounded state changes.

*/
void PlayerObject::boostPlayer(float yVelocity)
{
	// rename incorrect bindings
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	bool& m_isVelocityUncapped = m_isAccelerating;
	float& m_playerScale = m_vehicleSize;
    
    m_isJumping = true;
    m_onGround = false;
    m_canJump = false;
    m_shouldTryPlacingCheckpoint = true;
    m_isVelocityUncapped = true;

    setYVelocity(yVelocity, 0);

    if (!m_isDashing) {
        if (isInNormalMode()) { // Cube
			stopRotation(false, 0);
			float duration = (m_playerScale == 1.0f) ? (40.0f / 60.0f) : (52.0f / 60.0f);

			m_rotationSpeed = flipMod() * -180.0f / duration;
			m_isRotating = true;
        }
        else if (m_isSpider) {
			m_spiderSprite->tweenToAnimation("fall_loop", 0.1f);		
		}
    }
    
	m_lastGroundedPos = getPosition();
}