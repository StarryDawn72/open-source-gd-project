bool PlayerObject::canStickToGround()
{
    return !m_isShip && !m_isDart || !m_isJumpUnused;
}