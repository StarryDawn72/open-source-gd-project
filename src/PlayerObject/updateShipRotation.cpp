/*
    Applies to all four flying game modes (Ship, Wave, UFO, Swing),
    not just ship.
*/
void PlayerObject::updateShipRotation(float dt)
{
    if (m_isOnSlope || m_isDashing)
        return;

    // Rename incorrect bindings
    CCPoint& m_lastPlayerPosition = m_shipRotation;
    bool& m_onGround = m_isOnGround2;
    float& m_playerScale = m_vehicleSize;
    bool& m_slopeForceLeft = m_platformerMovingLeft;
    bool& m_slopeForceRight = m_platformerMovingRight;

    CCPoint pos = getPosition();

    bool isFlyingMode = m_isBird || m_isShip || m_isSwing || m_isDart; // wow robtop

    float dx = isFlyingMode && m_isGoingLeft
                ? fabsf(pos.x -  m_lastPlayerPosition.x)
                : pos.x -  m_lastPlayerPosition.x;
    float dy = -(pos.y - m_lastPlayerPosition.y);

    if (m_isSideways) {
        dx = isFlyingMode && m_isGoingLeft
            ? fabsf(pos.y - m_lastPlayerPosition.y)
            : pos.y - m_lastPlayerPosition.y;

        dy = pos.x -  m_lastPlayerPosition.x;
    }

    if (SquareDistance(0, 0, dx, dy) < dt * 1.2f && (!m_isPlatformer || !m_isShip && !m_isBird))
        return;

    float angle = atan2(dy, dx);
    float currentRotation = getRotation();

    if (m_isBird)
        angle *= -0.4f;

    if (m_isCollidingWithSlope && isFlying())
        angle = 0.0f;

    if (isFlyingMode && m_isGoingLeft)
        angle = -angle;

    float radians = CC_DEGREES_TO_RADIANS(currentRotation);
    float speed = 0.0f;

    if (m_isBird) {

        if (m_isGoingLeft == m_isUpsideDown)
            angle = std::max(angle, -0.1f);
        else
            angle = std::min(angle, 0.1f);

        if (m_isPlatformer) {
            speed = 0.07f;

            if (fabs(m_platformerXVelocity) > 0.5f) {
                if (m_onGround)
                    angle = 0.0f;

            }
            else
                angle = 0.0f;
        }
        else speed = 0.07f;
    }
    else if (m_isDart) {
        speed = (m_playerScale != 1.0) ? 0.4f : 0.25f;
    }
    else if (!m_isPlatformer || !m_isShip) {
        speed = 0.15f;
    }
    else if (!m_holdingLeft
        && !m_holdingRight
        && !m_slopeForceLeft
        && !m_slopeForceRight)
    {
        speed = 0.06f;
        angle = 0;
    }
    else {
        // Jetpack rotation (platformer ship)

        float dirMod = (m_isUpsideDown == m_isSideways) ? 1.0f : -1.0f;
        float mod = reverseMod() * dirMod;

        angle = mod * CC_DEGREES_TO_RADIANS(30.0f);

        if (fabsf(mod * CC_DEGREES_TO_RADIANS(30.0f)) - fabsf(radians) < 0.1f)
        {
            angle = mod * CC_DEGREES_TO_RADIANS(45.0f);
            speed = 0.015f;
        }
        else
            speed = 0.07f;
    }

    if (m_isCollidingWithSlope && isFlying())
        speed *= 0.25f;

    dt = std::min(dt, speed * dt);

    setRotation(CC_RADIANS_TO_DEGREES(Slerp2D(radians, angle, dt)));
}