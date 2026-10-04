void PlayerObject::addToYVelocity(double yVelocity, int type)
{
    setYVelocity(yVelocity + m_yVelocity, type);
}