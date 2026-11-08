void PlayerObject::updateCollideBottom(float y, GameObject* object)
{
    int uniqueId = 0;
    if (object)
        uniqueId = object->m_uniqueID;

    if (m_collidedBottomMaxY == 0)
        m_collidedBottomMaxY = y;
    else {
        if (m_isUpsideDown)
            m_collidedBottomMaxY = std::min(m_collidedBottomMaxY, (double)y);
        else
            m_collidedBottomMaxY = std::max(m_collidedBottomMaxY, (double)y);
    }

    if (uniqueId)
        storeCollision(PlayerCollisionDirection::Bottom, uniqueId);
}