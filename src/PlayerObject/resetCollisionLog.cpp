void PlayerObject::resetCollisionLog(bool full)
{
    m_collisionLogTop->removeAllObjects();
    m_collisionLogBottom->removeAllObjects();
    m_collisionLogLeft->removeAllObjects();
    m_collisionLogRight->removeAllObjects();

    if (full)
    {
        // Probably something like m_prevLastCollisionBottom/Top
        m_unk50C = -1;
        m_unk510 = -1;
    } else {
        m_unk50C = m_lastCollisionBottom;
        m_unk510 = m_lastCollisionTop;
    }
    m_lastCollisionBottom = -1;
    m_lastCollisionTop = -1;
    m_lastCollisionLeft = -1;
    m_lastCollisionRight = -1;
}