void PlayerObject::addToTouchedRings(RingObject* object)
{
    if (!m_touchingRings->containsObject(object))
        m_touchingRings->addObject(object);
	
	m_touchedRings.insert(object->m_uniqueID);
}