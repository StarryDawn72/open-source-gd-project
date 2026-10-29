// @version 2.2081
bool PlayerObject::isFlying()
{
	return m_isShip || m_isBird || m_isDart || m_isSwing;
}