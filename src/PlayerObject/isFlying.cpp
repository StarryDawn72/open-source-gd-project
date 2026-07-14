/*
	====== PlayerObject::isFlying ======
	
	Returns true if the player is in one of the flying game modes
	(Ship, Bird, Dart, or Swing).
	
*/
bool PlayerObject::isFlying()
{
	return m_isShip || m_isBird || m_isDart || m_isSwing;
}