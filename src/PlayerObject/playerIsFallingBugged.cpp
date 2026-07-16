/*
	====== PlayerObject::playerIsFallingBugged ======
	
	Determines if the player is falling. Returns true if
	the player's vertical velocity is inferior (or superior if
	upside down) to double the current gravity value (usually around ~1.9).
	This is where to famous pre-2.2 upside-down physics are split,
	although sideways mode, Platformer, and Swing all bypass this
	and force the game to use the new physics.
	
*/
bool playerIsFallingBugged()
{
    if (m_isSideways || m_isPlatformer || m_isSwing || m_fixGravityBug) {
		// Use new physics
        return playerIsFalling(m_gravity + m_gravity);
    }

	// Use legacy physics

	bool& m_isInDualMode = m_unkA99;
    double gravity = m_isInDualMode ? -m_gravity : m_gravity;
	double threshold = gravity + gravity;

	return m_isUpsideDown ? (m_yVelocity > threshold) : (m_yVelocity < threshold);
}