/*
	====== PLAYEROBJECT::PUSHDOWN ======
	
	Cancels vertical velocity, resets grounded state
	and physically prevents the player from jumping.
	
*/
void PlayerObject::pushDown()
{
    setYVelocity(0.0f, 0);
	bool onGround = &m_isOnGround2;
	bool canJump = &m_isOnGround;

	onGround = false;
	canJump = false;
}