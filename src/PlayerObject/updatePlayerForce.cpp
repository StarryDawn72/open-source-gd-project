<<<<<<< HEAD
void PlayerObject::updatePlayerForce(cocos2d::CCPoint velocity, bool additive)
{
    m_isAccelerating = true;

    double yVelocity = velocity.y;
    if (additive)
        yVelocity += m_yVelocity;
    m_yVelocity = yVelocity;
=======
void PlayerObject::updatePlayerForce(CCPoint velocity, bool additive)
{
    m_isVelocityUncapped = true;

    double vel = velocity.y;
    
    if (additive)
        vel += m_yVelocity;
    
    m_yVelocity = vel;
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342

    if (m_isPlatformer)
    {
        double xVelocity = velocity.x;
<<<<<<< HEAD
        if (additive)
            xVelocity += m_platformerXVelocity;
        m_platformerXVelocity = xVelocity;
        m_affectedByForces = true;
    }
}
=======
        
        if (additive)
            xVelocity += m_platformerXVelocity;
        
        m_platformerXVelocity = xVelocity;
        m_affectedByForces = true;
    }
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
