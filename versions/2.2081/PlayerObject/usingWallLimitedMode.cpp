bool PlayerObject::usingWallLimitedMode()
{
    return isFlying() || m_isBall || m_isSpider;
}