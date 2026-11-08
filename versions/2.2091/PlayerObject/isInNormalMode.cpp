bool PlayerObject::isInNormalMode()
{
	return !isFlying() && !m_isBall && !m_isRobot && !m_isSpider;
}