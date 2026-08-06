GameObjectType PlayerObject::getActiveMode()
{
    if (isFlying())
        return GameObjectType::ShipPortal;
    if (m_isBall)
        return GameObjectType::BallPortal;
    if (m_isSpider)
        return GameObjectType::SpiderPortal;
    return GameObjectType::CubePortal;
}