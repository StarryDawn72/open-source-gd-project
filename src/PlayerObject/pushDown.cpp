/*
	====== PlayerObject::pushDown ======
	
	Cancels vertical velocity, resets grounded state
	and physically prevents the player from jumping.
	
*/
void PlayerObject::pushDown()
{
    setYVelocity(0.0f, 0);

	// rename misnamed member variables
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;

	m_onGround = false;
	m_canJump = false;
}