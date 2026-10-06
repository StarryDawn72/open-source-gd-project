void PlayerObject::updatePlayerForce(CCPoint velocity, bool additive)
{
    m_isVelocityUncapped = true;

    double vel = velocity.y;
    
    if (additive)
        vel += m_yVelocity;
    
    m_yVelocity = vel;

    if (m_isPlatformer)
    {
        double xVelocity = velocity.x;
        
        if (additive)
            xVelocity += m_platformerXVelocity;
        
        m_platformerXVelocity = xVelocity;
        m_affectedByForces = true;
    }
}
