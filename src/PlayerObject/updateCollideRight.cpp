void PlayerObject::updateCollideRight(float x, GameObject* object)
{
    int uniqueId = 0;
    if (object)
        uniqueId = object->m_uniqueID;

    if (m_collidedRightMinX == 0.0 || x < m_collidedRightMinX)
        m_collidedRightMinX = x;

    if (uniqueId)
    {
        storeCollision(PlayerCollisionDirection::Right, uniqueId);
        m_collidingWithRight = object;
        m_collidingWithLeft = nullptr;
    }
}