void PlayerObject::storeCollision(PlayerCollisionDirection direction, int id) {
    switch (direction)
    {
        case PlayerCollisionDirection::Top:
            if (id != m_lastCollisionTop) {
                m_lastCollisionTop = id;
                m_collisionLogTop->setObject(m_maybeLastGroundObject, id); // TODO: find more suitable name
            }
            break;
        case PlayerCollisionDirection::Bottom:
            if (id != m_lastCollisionBottom) {
                m_lastCollisionBottom = id;
                m_collisionLogBottom->setObject(m_maybeLastGroundObject, id);
            }
            break;
        case PlayerCollisionDirection::Left:
            if (id != m_lastCollisionLeft) {
                m_lastCollisionLeft = id;
                m_collisionLogLeft->setObject(m_maybeLastGroundObject, id);
            }
            break;
        case PlayerCollisionDirection::Right:
            if (id != m_lastCollisionRight) {
                m_lastCollisionRight = id;
                m_collisionLogRight->setObject(m_maybeLastGroundObject, id);
            }
            break;
    }
}