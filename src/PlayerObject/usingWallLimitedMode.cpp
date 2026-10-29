// @version 2.2081
bool PlayerObject::usingWallLimitedMode()
{
    return isFlying() || m_isBall || m_isSpider;
}