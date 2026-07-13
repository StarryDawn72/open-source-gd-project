/*
	====== PLAYEROBJECT::BOOSTPLAYER ======
	
	Applies a boost to the player by setting upward velocity and handling
	rotation, animation, and grounded state changes.

*/
void PlayerObject::boostPlayer(float yVelocity)
{
	// rename incorrect bindings
	bool& isJumping = m_maybeIsBoosted;
	bool& onGround = m_isOnGround2;
	bool& canJump = m_isOnGround;
	bool& isVelocityUncapped = m_isAccelerating;
	bool& ballRotationMultiplierActive = m_isBallRotating;
	float& playerScale = m_vehicleSize;
    
    isJumping = true;
    onGround = false;
    canJump = false;
    m_shouldTryPlacingCheckpoint = true;
    isVelocityUncapped = true;

    setYVelocity(yVelocity, 0);

    if (!m_isDashing) {
        if (!isFlying() && !m_isBall && !m_isRobot && !m_isSpider) {
			stopRotation(false, 0);
			float duration = (playerScale == 1.0f) ? (40.0f / 60.0f) : (52.0f / 60.0f);

			m_rotationSpeed = flipMod() * -180.0f / duration;
			m_isRotating = true;
        }
        else if (m_isSpider) {
			m_spiderSprite->tweenToAnimation("fall_loop", 0.1f);		
		}
    }
    
	m_lastGroundedPos = getPosition();
}