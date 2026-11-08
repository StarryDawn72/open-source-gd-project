void PlayerObject::updateCollideLeft(float x, GameObject* object)
{
    int uniqueId = 0;
    if (object)
        uniqueId = object->m_uniqueID;

    if (m_collidedLeftMaxX == 0.0 || x > m_collidedLeftMaxX)
        m_collidedLeftMaxX = x;

    if (uniqueId)
    {
        storeCollision(PlayerCollisionDirection::Left, uniqueId);
        m_collidingWithLeft = object;
        m_collidingWithRight = nullptr;
    }
}