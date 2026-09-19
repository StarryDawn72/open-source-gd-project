void PlayerObject::updateStaticForce(float rotation, float staticForce, bool additive)
{
    // Rename incorrect geode bindings
    bool& m_isVelocityUncapped = m_isAccelerating;

    if (staticForce != 0.0 || additive) {

        CCPoint vector = ccpForAngle(CC_DEGREES_TO_RADIANS(rotation));
        float length = vector.getLength();

        if (length > 0) {
            CCPoint velocity = vector * (staticForce / length);

            if ( m_isSideways )
            {
                float y = velocity.y;
                velocity.y = velocity.x;
                velocity.x = y;
            }

            updatePlayerForce(velocity, additive);
        }
    }
    else {
        m_isVelocityUncapped = false;
        m_yVelocity = 0.0;

        if ( m_isPlatformer ) {
            m_platformerXVelocity = 0.0;
            m_affectedByForces = false;
        }
    }
}