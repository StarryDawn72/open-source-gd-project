void GJGroundLayer::updateGroundPos(CCPoint pos)
{
    m_ground1Sprite->setPosition(pos);
    if (m_ground2Sprite) m_ground2Sprite->setPosition(pos);
}