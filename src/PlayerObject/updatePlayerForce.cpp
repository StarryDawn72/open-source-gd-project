void PlayerObject::updatePlayerForce(cocos2d::CCPoint velocity, bool additive)
{
    m_isAccelerating = true;

    double yVelocity = velocity.y;
    if (additive)
        yVelocity += m_yVelocity;
    m_yVelocity = yVelocity;

    if (m_isPlatformer)
    {
        double xVelocity = velocity.x;
        if (additive)
            xVelocity += m_platformerXVelocity;
        m_platformerXVelocity = xVelocity;
        m_affectedByForces = true;
    }
}