/*
	 	
	Cancels vertical velocity, resets grounded state
	and physically prevents the player from jumping.
	
*/
void PlayerObject::pushDown()
{
    setYVelocity(0.0f, 0);
	m_onGround = false;
	m_canJump = false;
}