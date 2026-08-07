/*
	Use spherical lerp to smoothly face the target angle.
*/
void PlayerObject::updateRotation(float dt, float rotation)
{
    if (m_isDashing)
        return;

	// Rename bindings
	bool m_onGround = m_isOnGround2;
	int m_reverseTimer = m_reverseRelated
	
    float rotationRad = CC_DEGREES_TO_RADIANS(getRotation());
    float speed = m_playerSpeed * 0.175f;

    if (m_isShip)
        speed *= 0.5f;
    else if (!isFlying() && !m_isBall && m_onGround && !m_isOnSlope && !m_wasOnSlope)
        speed *= 3.0f;

	float t = std::min(dt, dt * speed);

	if (m_isPlatformer && isFlying() && m_isOnSlope && m_reverseTimer > 0)
		setRotation(rotation);
		// Instantly snap rotation when reversing direction on a slope
		// in Platformer UFO/Jetpack mode to prevent the vehicle from spinning
		// to face the other way. Pretty cool
	else
		setRotation(CC_RADIANS_TO_DEGREES(Slerp2D(rotationRad, CC_DEGREES_TO_RADIANS(rotation), t)));
}

/*
	Per-tick rotation update loop for the player, handles all game modes.
*/
void PlayerObject::updateRotation(float dt)
{
    if (m_isLocked || m_isDashing)
        return;

	// Rename bindings
	bool m_onGround = m_isOnGround2;
	float m_ballRotationMultiplier = m_rotateSpeed;

    if (!m_isBall) {

        if (m_isOnSlope)
            updateSlopeRotation(dt);

        else if (isFlying())
            updateShipRotation(dt);

        else if ( 
		    !m_isBall
          && m_onGround
          && !playerIsFalling(-0.25f)
          && !m_isOnSlope
          && !m_wasOnSlope)
        {
            if (!m_isPlatformer || !m_isRotating) {
				stopRotation(false, 2);
				updateRotation(dt, convertToClosestRotation(0.0f));			
			}
        }

        else if ((m_isRobot || m_isSpider) && !m_isOnSlope && !m_wasOnSlope) {
            updateRotation(dt * 0.5f, 0.0f);
        }
    }
	
    if (m_rotationSpeed != 0.0f) {
		float multiplier = (m_isBallRotating && m_isBall)
			? m_ballRotationMultiplier
			: 1.0f;

        setRotation(getRotation() + (((dt / 60.0f) * m_rotationSpeed) * multiplier));
    }
}