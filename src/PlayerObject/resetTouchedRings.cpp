void PlayerObject::resetTouchedRings(bool removeAll)
{
    if (removeAll)
        m_touchingRings->removeAllObjects();
    else
    {
        for (int i = 0; i < m_touchingRings->count();)
        {
            GameObject* ring = (GameObject*)m_touchingRings->objectAtIndex(i);

            if (!m_touchedRings.count(ring->m_uniqueID))
                m_touchingRings->removeObjectAtIndex(i, 1);
            else
                i++;
        }
    }

    m_touchedRings.clear();
}