/*
	====== PlayerObject::redirectDash ======
	
	This feature is part of the "Redirect Dash" option in the
	Edit Special menu for teleport portals. In platformer mode,
	enabling this setting will cause the angle of the player to
	adapt to the second teleport portal's rotation if dashing into it,
	as well as reversing the player's direction if needed.
	
*/
void PlayerObject::redirectDash(float rotation)
{
	if (!m_isDashing) return;

	CCPoint dashPos = ccp(m_dashX, m_dashY);
    float originalAngle = atan2f(dashPos.y, dashPos.x);
    float direction = convertToClosestDirection(CC_DEGREES_TO_RADIANS(rotation) - originalAngle, M_PI);

    if (direction != 0.0f) {
        float cosDir = cosf(direction);
        float sinDir = sinf(direction);
        dashPos = ccp(cosDir * dashPos.x - sinDir * dashPos.y, sinDir * dashPos.x + cosDir * dashPos.y);
    }

	float dashAngle = atan2f(dashPos.y, dashPos.x);
	int newAngle = -CC_RADIANS_TO_DEGREES(dashAngle);

	newAngle = (newAngle + m_isSideways ? -90.0f : 0.0f) % 360;
	if (newAngle < 0) newAngle += 360;
	if (m_isSideways) CC_SWAP(dashPos.x, dashPos.y, float);

	m_dashAngle = -newAngle;
	m_dashX = dashPos.x;
	m_dashY = dashPos.y;

	if (m_dashX < 0.0) {
		doReversePlayer(!m_isSideways);
	}
	else if (m_dashX > 0.0) {
		doReversePlayer(m_isSideways);
	}

    updateDashArt();
}