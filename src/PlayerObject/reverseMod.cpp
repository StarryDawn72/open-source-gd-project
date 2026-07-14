/*
	====== PlayerObject::reverseMod ======
	
	Returns the movement direction as an integer.
	Does not account for external forces in Platformer mode.
	
*/
int PlayerObject::reverseMod()
{
	return m_isGoingLeft ? -1 : 1;
}