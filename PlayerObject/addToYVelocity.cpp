/*
	====== PLAYEROBJECT::ADDTOYVELOCITY ======

	A simple helper to incremen/decrement the Y velocity by
	an amount. The parameter gets fed into setYVelocity
	which does rounding as usual.
	
*/
void PlayerObject::addToYVelocity(double yVelocity, int type)
{
    setYVelocity(yVelocity + m_yVelocity, type);
}