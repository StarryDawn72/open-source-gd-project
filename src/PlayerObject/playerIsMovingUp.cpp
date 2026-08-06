bool PlayerObject::playerIsMovingUp()
{
    if (m_isUpsideDown)
        return m_yVelocity < 0;
    else
        return m_yVelocity > 0;
}