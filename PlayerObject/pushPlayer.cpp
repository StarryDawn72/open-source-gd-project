/*
	====== PLAYEROBJECT::PUSHPLAYER ======
	
	This function acts as a wrapper around addToYVelocity.
	It existed before update 2.2, while setYVelocity and
	addToYVelocity did not.
	
*/

void PlayerObject::pushPlayer(float yVelocity)
{
    addToYVelocity(yVelocity, 0);
}