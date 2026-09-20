void PlayerObject::resetTouchedRings(bool removeAll)
{
    if (removeAll)
        m_touchingRings->removeAllObjects();
    else {
        unsigned int i = 0;

        while (i < m_touchingRings->count()) {
            RingObject* ring = (RingObject*)m_touchingRings->objectAtIndex(i);

            if (m_touchedRings.count(ring->m_uniqueID))
                i++;
            else
                m_touchingRings->removeObjectAtIndex(i, true);
        }
    }
    m_touchedRings.clear();
}
