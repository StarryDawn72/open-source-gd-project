void PlayerObject::updateCollideTop(float y, GameObject* object)
{
    int uniqueId = 0;
    if (object)
        uniqueId = object->m_uniqueID;

    if (m_collidedTopMinY == 0)
        m_collidedTopMinY = y;
    else {
        if (m_isUpsideDown)
            m_collidedTopMinY = std::max(m_collidedTopMinY, (double)y);
        else
            m_collidedTopMinY = std::min(m_collidedTopMinY, (double)y);
    }

    if (uniqueId)
        storeCollision(PlayerCollisionDirection::Top, uniqueId);
}