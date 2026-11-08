void PlayerObject::updateLastGroundObject(GameObject* object)
{
    if (!object)
        return;
    m_lastGroundObject = object;
    if (object->m_isDontBoostY)
        m_stateBoostX = 2;
    if (object->m_isDontBoostX)
        m_stateBoostY = 2;
}