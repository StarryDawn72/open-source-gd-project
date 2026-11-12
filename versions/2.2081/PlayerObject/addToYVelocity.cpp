void PlayerObject::addToYVelocity(double yVelocity, int unused)
{
    setYVelocity(yVelocity + m_yVelocity, unused);
}