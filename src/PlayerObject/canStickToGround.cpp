// @version 2.2081
bool PlayerObject::canStickToGround()
{
    return !m_isShip && !m_isDart || !m_isJumpUnused;
}