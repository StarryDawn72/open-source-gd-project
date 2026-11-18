void PlayerObject::updateLastGroundObject(GameObject* object)
{
    if (!object)
        return;
    m_lastGroundObject = object;
    if (object->m_isDontBoostY)
        m_boostXTimer = 2;
    if (object->m_isDontBoostX)
        m_boostYTimer = 2;
}