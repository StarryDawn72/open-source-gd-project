// @version 2.2081
bool PlayerObject::destroyFromHitHead()
{
    if (isFlying() || m_isBall || m_isSpider)
        return false;
	
    return m_stateHitHead <= 0;
}