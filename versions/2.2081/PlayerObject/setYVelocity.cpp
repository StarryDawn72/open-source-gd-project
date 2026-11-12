/*
	 	
	This function sets the current player's vertical velocity
	with a rounding to the third decimal place. The second parameter is
	unused. This function was added in update 2.2.
	
*/
void PlayerObject::setYVelocity(double velocity, int unused)
{
    double truncated = (int)velocity;

    if (velocity != truncated)
        velocity = truncated + round((velocity - truncated) * 1000.0f) / 1000.0f;

    m_yVelocity = velocity;
}