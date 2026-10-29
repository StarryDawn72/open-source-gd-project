// @version 2.2081
bool PlayerObject::isInBasicMode()
{
	return !isFlying() && !m_isBall && !m_isSpider;
}